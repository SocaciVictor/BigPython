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

void Board::initBoard()
{
	//Creare Tabla de joc;
	m_bases.resize(m_rows);
	for (std::uint16_t i = 0; i < m_rows; i++) {
		m_bases[i].resize(m_columns);
		for (std::uint16_t j = 0; j < m_columns; j++) {
			//verificare sa nu se creeze si in colturile tablei;
			if ((j == 0 || j == m_columns - 1) && (i == 0 || i == m_rows - 1)) continue;
			m_bases[i][j] = std::make_unique<Base>(Point{ j,i });
		}
	}
}

//Constructor Board;
Board::Board(const std::uint16_t& rows, const  std::uint16_t& columns) :
	 m_rows{ rows }, m_columns{ columns }
{
	initBoard();
}

const std::vector<std::vector<std::unique_ptr<Base>>>& Board::getData() const noexcept
{
	return m_bases;
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

std::string Board::getHashWithMove(Move* move)
{
	std::string hash = "";
	std::set<Point> bridgesPozitions;

	std::unordered_map<Point, PieceType, PointHash> type; //stands for each bridge point type and for checking pillar points
	PieceType t;

	//set all the bridge poz in order
	for (const auto& bridge : m_bridges) {
		bridgesPozitions.insert(bridge.first.point1);
		bridgesPozitions.insert(bridge.first.point2);
		if (bridge.second.getColor() == PieceColor::Blue)
			t = PieceType::BlueBridge;
		else  //PieceColor == Red
			t = PieceType::RedBridge;
		type[bridge.first.point1] = t;
		type[bridge.first.point2] = t;
	}
	//hash contains all the bridges position in order first
	for (const auto& point : bridgesPozitions) {
		hash += std::to_string(point.x) + std::to_string(point.y) + std::to_string(static_cast<int>(type[point]));
	}
	//then hash contains all the pillars coord and color
	for (const auto& line : m_bases) {
		for (const auto& base : line) {
			//check if base is pillar
			if (dynamic_cast<Pillar*>(base.get()) == nullptr)
				continue;
			//if a base is a pillar pozition and not a bridge position
			if (type.find(base->getCoordinates()) == type.end()) {
				if (base->getColor() == PieceColor::Blue)
					t = PieceType::BluePillar;
				else //PieceType == Red
					t = PieceType::RedPillar;
				hash += std::to_string(base->getCoordinates().x) + std::to_string(base->getCoordinates().y)
					+ std::to_string(static_cast<int>(t));
			}
		}
	}
	//lastly hash contains the move
	if (dynamic_cast<MovePillar*>(move) != nullptr) {
		hash += std::to_string(static_cast<MovePillar*>(move)->pozition.x) + std::to_string(static_cast<MovePillar*>(move)->pozition.y);
	}
	else { //MoveBridge
		//if move is a Next move(it placed or removed all the bridges)
		if (static_cast<MoveBridge*>(move)->moveType == MoveType::Next)
			hash += std::to_string((int)MoveType::Next);
		else {
			hash += std::to_string(static_cast<MoveBridge*>(move)->startPozition.x) + std::to_string(static_cast<MoveBridge*>(move)->startPozition.y) +
				std::to_string(static_cast<MoveBridge*>(move)->endPozition.x) + std::to_string(static_cast<MoveBridge*>(move)->endPozition.y) +
				std::to_string(static_cast<int>(static_cast<MoveBridge*>(move)->moveType)); //0 delete bridge, 1 add bridge
		}
	}
	return hash;
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
	if (color == PieceColor::Blue &&
		(point.x == 0 || point.x == m_columns - 1)) return false;
	if (color == PieceColor::Red &&
		(point.y == 0 || point.y == m_rows - 1)) return false;
	//verificare daca pe punctul ales nu este deja pillar;
	if (m_bases[point.y][point.x]->getColor() != PieceColor::None) return false;
	//daca verificarile sunt bune se va adauga pillarul;
	m_bases[point.y][point.x] =
		std::make_unique<Pillar>(point, color);
	return true;
}

const bool& Board::addBridge(const Point& point1, const Point& point2, const PieceColor& color)
{
	if (!isInBoard(point1) || !isInBoard(point2)) return false;
	//verificare daca pillari sunt de aceiasi culoare cu playerul current
	if (m_bases[point1.y][point1.x]->getColor() != color ||
		m_bases[point2.y][point2.x]->getColor() != color) return false;
	//verificare daca podul creat nu se intersecteaza cu alte poduri;
	if (!isNotIntersection(point1, point2)) return false;
	//creare Bridge;
	m_bridges[TwoPoint{ point1, point2 }] = Bridge(point1, point2, color);
	//adaug conexiunile dintre cei doi noi vecini;
	static_cast<Pillar*>(m_bases[point1.y][point1.x].get())->addNeighbor(point2);
	static_cast<Pillar*>(m_bases[point2.y][point2.x].get())->addNeighbor(point1);
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
	static_cast<Pillar*>(m_bases[point1.y][point1.x].get())->removeNeighbor(point2);
	static_cast<Pillar*>(m_bases[point2.y][point2.x].get())->removeNeighbor(point1);
	return true;
}

const bool& Board::gameIsEnded(const Point& point1, const Point& point2, const PieceColor& color)
{
	//Algoritmul Dijkstra
	//creare comparator pentru prioritate in functie de culoarea playerului;
	auto comparator = [this,color](const Point& p1, const Point& p2) {
		if (color == PieceColor::Blue) {
			return std::min(abs(p1.y - m_rows - 1), abs(p1.y - 0)) >
				std::min(abs(p2.y - m_rows - 1), abs(p2.y - 0));
		}
		if (color == PieceColor::Red) {
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
		if ((loc_current.y == 0 && color == PieceColor::Blue) ||
			(loc_current.x == 0 && color == PieceColor::Red))
		{
			base1 = true;
		}
		if ((loc_current.y == m_rows - 1 && color == PieceColor::Blue) ||
			(loc_current.x == m_columns - 1 && color == PieceColor::Red))
		{
			base2 = true;
		}
		//verificare daca sa ajuns la ambele baze;
		if (base1 && base2) {
			return true;
		}
		//parcurgere toti vecini;
		for (auto neighbor : static_cast<Pillar*>(m_bases[loc_current.y][loc_current.x].get())->getNeighbors()) {
			//daca vecinul este deja vizitat se trece mai departe;
			if (matrice_vizitate[neighbor.y][neighbor.x]) continue;
			//se adauga locatia vecinului in coada de prioritate;
			pqueue.push(neighbor);
			matrice_vizitate[neighbor.y][neighbor.x] = true;
		}
	}
	return false;
}

void Board::reset()
{
	m_bridges.clear();
	initBoard();
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
	//citire poduri
	uint16_t nr_bridges;
	char color;
	Point point1, point2;
	input >> nr_bridges;
	for (uint16_t i = 0; i < nr_bridges; i++) {
		input >> color >> point1.x >> point1.y >> point2.x >> point2.y;
		board.m_bridges[TwoPoint{ point1, point2 }] = Bridge{ point1, point2, charToPieceColor(color) };
		//adaug conexiunile dintre cei doi noi vecini;
		static_cast<Pillar*>(board.m_bases[point1.y][point1.x].get())->addNeighbor(point2);
		static_cast<Pillar*>(board.m_bases[point2.y][point2.x].get())->addNeighbor(point1);
	}
	return input;
}
