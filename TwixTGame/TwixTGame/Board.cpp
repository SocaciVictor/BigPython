#include "Board.h"


const bool& Board::isNotIntersection(const Point& p1, const Point& p2)
{
	//calculam directiile
	int16_t dx = p1.x - p2.x;
	int16_t dy = p1.y - p2.y;
	//verificam daca distantele calculate sunt egale cu 3 (daca e 3 inseamna ca e forma de L);
	if (abs(dx) + abs(dy) != 3) return false;

	//verificam daca podul care vrem sa il cream nu exista deja;
	if (m_bridges.find({ p1,p2 }) != m_bridges.end()) return false;

	//initializam erorile distantelor cu +;
	int16_t erorY = 1;
	int16_t erorX = 1;

	//verificam in ce cadran ne aflam;
	if (dy < 0) erorY = -1;
	if (dx < 0) erorX = -1;

	//vectori pentru cazul dx>dy cadran 1;
	int16_t X1[9]{ -1,0,-2,1,-1,-1,-2,-2,-1 }; // x pt P1;
	int16_t Y1[9]{ 1,-1,0,-1,-1,0,1,-2,-1 }; // y pt P1;
	int16_t X2[9]{ 2,0,1,1,-1,2,1,1,2 }; // x pt P2;
	int16_t Y2[9]{ 0,1,-1,1,1,-1,0,1,2 }; // y pt P2;

	//verificam care directie e mai mare;
	if (abs(dx) < abs(dy)) {
		std::swap(X1, Y1);
		std::swap(X2, Y2);
	}

	//parcurgem cele 9 cazuri posibile de poduri care se pot intersecta cu podul nou creat;
	for (int i = 0; i < 9; i++) {
		Point new_p1{ uint16_t(p1.x + X1[i] * erorX),uint16_t(p1.y + Y1[i] * erorY) };
		Point new_p2{ uint16_t(p2.x + X2[i] * erorX),uint16_t(p2.y + Y2[i] * erorY) };
		//verificam daca exista un pod care nu ne lasa sa cream podul curent;
		if (m_bridges.find({ new_p1,new_p2 }) != m_bridges.end()) return false;
	}
	return true;
}

//Constructor Board;
Board::Board(const std::uint16_t& rows, const  std::uint16_t& columns) :
	 m_rows{ rows }, m_columns{ columns }
{
	//Creare Tabla de joc;
	m_date.resize(m_rows);
	for (std::uint16_t i = 0; i < m_rows; i++) {
		m_date[i].resize(m_columns);
		for (std::uint16_t j = 0; j < m_columns; j++) {
			//verificare sa nu se creeze si in colturile tablei;
			if ((j == 0 || j == m_columns - 1) && (i == 0 || i == m_rows - 1)) continue;
			m_date[i][j] = std::make_unique<Base>(Point{ i,j });
		}
	}
}

const std::vector<std::vector<std::unique_ptr<Base>>>& Board::getData() const noexcept
{
	return m_date;
}

const uint16_t& Board::getRows() const noexcept
{
	return m_rows;
}

const uint16_t& Board::getColumns() const noexcept
{
	return m_columns;
}

const std::unordered_map<TwoPoint, Bridge, TwoPointHash>& Board::getBridges() const noexcept
{
	return m_bridges;
}

const bool& Board::isInBoard(const Point& point)
{
	if (point.x < 0 || point.y < 0 || point.x >= m_columns || point.y >= m_rows) return false;
	if ((point.x == 0 || point.x == m_columns - 1) && (point.y == 0 || point.y == m_rows - 1)) return false;
	return true;
}

const bool& Board::addPillar(const Point& point, const PieceColor& color)
{
	//verificare daca punctul se afla in board;
	if (!isInBoard(point)) return false;
	//verificare ca playerul sa nu poata adauga pillar in bazele inamice;
	if (color == PieceColor::Red &&
		(point.x == 0 || point.x == m_columns - 1)) return false;
	if (color == PieceColor::Black &&
		(point.y == 0 || point.y == m_rows - 1)) return false;
	//verificare daca pe punctul ales nu este deja pillar;
	if (m_date[point.y][point.x]->getColor() != PieceColor::None) return false;
	//daca verificarile sunt bune se va adauga pillarul;
	m_date[point.y][point.x] =
		std::make_unique<Pillar>(point, color);
	return true;
}

const bool& Board::addBridges(const Point& point1, const Point& point2, const PieceColor& color)
{
	if (!isInBoard(point1) || !isInBoard(point2)) return false;
	//verificare daca pillari sunt de aceiasi culoare cu playerul current
	if (m_date[point1.y][point1.x]->getColor() != color ||
		m_date[point2.y][point2.x]->getColor() != color) return false;
	//verificare daca podul creat nu se intersecteaza cu alte poduri;
	if (!isNotIntersection(point1, point2)) return false;
	//creare Bridge;
	m_bridges[TwoPoint{ point1, point2 }] = Bridge(point1, point2, color);
	//adaug conexiunile dintre cei doi noi vecini;
	static_cast<Pillar*>(m_date[point1.y][point1.x].get())->addNeighbor(point2);
	static_cast<Pillar*>(m_date[point2.y][point2.x].get())->addNeighbor(point1);
	return true;
}

const bool& Board::removeBridge(const Point& point1, const Point& point2, const PieceColor& color)
{
	//verificam daca podul pe care vrem sa il stergem exista;
	if (m_bridges.find({ point1,point2 }) == m_bridges.end()) return false;
	//verificarea daca podul este de aceiasi culoare cu playerul;
	if (m_bridges[TwoPoint{ point1, point2 }].getColor() != color) return false;
	//stergerea podului;
	m_bridges.erase({ point1,point2 });
	//stergerea conexiuni de vecinatate dintre cei doi pillari;
	static_cast<Pillar*>(m_date[point1.y][point1.x].get())->removeNeighbor(point2);
	static_cast<Pillar*>(m_date[point2.y][point2.x].get())->removeNeighbor(point1);
	return true;
}

const bool& Board::gameIsEnded(const Point& point1, const Point& point2, const PieceColor& color)
{
	//Algoritmul Dijkstra
	//creare comparator pentru prioritate in functie de culoarea playerului;
	auto comparator = [this,color](const Point& p1, const Point& p2) {
		if (color == PieceColor::Red) {
			return std::min(abs(p1.y - m_rows - 1), abs(p1.y - 0)) >
				std::min(abs(p2.y - m_rows - 1), abs(p2.y - 0));
		}
		if (color == PieceColor::Black) {
			return std::min(abs(p1.x - m_columns - 1), abs(p1.x - 0)) >
				std::min(abs(p2.x - m_columns - 1), abs(p2.x - 0));
		}
	};
	//initializare coada de prioritate;
	std::priority_queue<Point, std::vector<Point>, decltype(comparator)> pqueue(comparator);
	//initializare matrice de locuri vizitate;
	std::vector<std::vector<bool>> matrice_vizitate;
	matrice_vizitate.resize(m_rows);
	for (auto& rows : matrice_vizitate)
		rows.resize(m_columns);
	//initiaizare a 2 tipuri bool care vor retine daca se ajunge la una dintre baze;
	bool base1{ false }, base2{ false };
	//incepere algoritm 
	pqueue.push(point1);
	matrice_vizitate[point1.y][point1.x] = true;
	pqueue.push(point2);
	matrice_vizitate[point2.y][point2.x] = true;
	//parcurgere elementelor din priority queue;
	while (pqueue.size() != 0) {
		//extragerea elementului cu prioritate maxima din coada;
		Point loc_current = pqueue.top();
		pqueue.pop();
		//verificare daca se ajunge la una din baze;
		if ((loc_current.y == 0 && color == PieceColor::Red) ||
			(loc_current.x == 0 && color == PieceColor::Black))
		{
			base1 = true;
		}
		if ((loc_current.y == m_rows - 1 && color == PieceColor::Red) ||
			(loc_current.x == m_columns - 1 && color == PieceColor::Black))
		{
			base2 = true;
		}
		//verificare daca sa ajuns la ambele baze;
		if (base1 && base2) {
			return true;
		}
		//parcurgere toti vecini;
		for (auto neighbor : static_cast<Pillar*>(m_date[loc_current.y][loc_current.x].get())->getNeighbors()) {
			//daca vecinul este deja vizitat se trece mai departe;
			if (matrice_vizitate[neighbor.y][neighbor.x]) continue;
			//se adauga locatia vecinului in coada de prioritate;
			pqueue.push(neighbor);
			matrice_vizitate[neighbor.y][neighbor.x] = true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& output, const Board& board)
{
	output << board.getRows() << " " << board.getColumns() << std::endl;
	for (const auto& [i, row] : std::views::enumerate(board.getData()))
	{
		for (const auto& [j, element] : std::views::enumerate(row)) {
			if (element == nullptr) {
				output << 'N';
			}
			else
			if (element->getColor() != PieceColor::None) {
				output << pieceColorToChar(element->getColor());
			}
			else {
				output << '.';
			}
			if (j < board.getColumns() - 1)
				output << " ";
		}	
		output<< std::endl;
	}
	output << board.getBridges().size();
	for (const auto& bridge : board.getBridges()) {
		output << std::endl << pieceColorToChar(bridge.second.getColor()) << ' '
			<< bridge.first.point1.x << ' ' << bridge.first.point1.y << ' '
			<< bridge.first.point2.x << ' ' << bridge.first.point2.y;
	}
	return output;
}

std::istream& operator>>(std::istream& input, Board& board)
{
	//citire bases
	uint16_t rows, columns;
	char base;
	input >> rows >> columns;
	board.m_bases.resize(rows);
	for (uint16_t i = 0; i < rows; i++) {
		board.m_bases[i].resize(columns);
		for (uint16_t j = 0; j < columns; j++) {
			input >> base;
			if (base == 'N') {
				board.m_bases[i][j] = nullptr;
				continue;
			}
			if (base == '.') {
				board.m_bases[i][j] = std::make_unique<Base>(Point{ j,i });
				continue;
			}
			if (base == 'R' || base == 'B') {
				board.m_bases[i][j] = std::make_unique<Pillar>(Point{ j,i }, charToPieceColor(base));
			}
		}
	}
}
