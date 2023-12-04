#include "Board.h"
#include "Game.h"
#include <iomanip>

bool Board::isNotIntersection(const Point& p1, const Point& p2)
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
		if (m_bridges.find({new_p1,new_p2}) != m_bridges.end()) return false;
	}
	return true;
}

//Constructor Board;
Board::Board(std::uint8_t rows, std::uint8_t columns, GameElement* parent) :
	GameElement{ parent }, m_rows{ rows }, m_columns{ columns }
{
	//Creare Tabla de joc;
	m_date.resize(m_rows);
	for (std::uint8_t i = 0; i < m_rows; i++) {
		m_date[i].resize(m_columns);
		for (std::uint8_t j = 0; j < m_columns; j++) {
			//verificare sa nu se creeze si in colturile tablei;
			if ((j == 0 || j == 23) && (i == 0 || i == 23)) continue;
			m_date[i][j] = std::make_unique<Base>(Point{ j,i }, this);
		}
	}
}

const std::vector<std::vector<std::unique_ptr<Base>>>& Board::getData() const noexcept
{
	return m_date;
}

const auto& Board::getBridges() const noexcept
{
	return m_bridges;
}

void Board::addPillar(Point coordinates)
{
	//verificare daca playerul a adaugat deja un pillar sa nu mai poata adauga;
	if (static_cast<Game*>(getParent())->getCurrentPlayer()->getMoved()) return;
	//verificare ca playerul sa nu poata adauga pillar in bazele inamice;
	if (static_cast<Game*>(getParent())->getCurrentPlayer()->getColor() == PieceColor::Red &&
		coordinates.x == 0 || coordinates.x == m_columns - 1
		) return;
	if (static_cast<Game*>(getParent())->getCurrentPlayer()->getColor() == PieceColor::Black &&
		coordinates.y == 0 || coordinates.y == m_rows - 1
		) return;
	//daca verificarile sunt bune se va adauga pillarul;
	m_date[coordinates.y][coordinates.x] =
		std::make_unique<Pillar>(coordinates, static_cast<Game*>(getParent())->getCurrentPlayer()->getColor(), this);
	//playerului curent i se scade un pillar;
	static_cast<Game*>(getParent())->getCurrentPlayer()->updateNumberPillars(-1);
	//playerul este setat ca si cum a adaugat deja un pillar;
	static_cast<Game*>(getParent())->getCurrentPlayer()->setMoved(true);
}

void Board::addBridge(Point coordinates)
{
	//verificare daca player a adaugat pilon
	if (!static_cast<Game*>(getParent())->getCurrentPlayer()->getMoved()) return;
	//verificare daca playerul curent mai are poduri;
	if (static_cast<Game*>(getParent())->getCurrentPlayer()->getNumberBridges() == 0) return;
	//verificare daca pillarul pe care sa apasat este de aceiasi culoare cu playerul current;
	if (m_date[coordinates.y][coordinates.x]->getColor() !=
		static_cast<Game*>(getParent())->getCurrentPlayer()->getColor()) return;
	//verific daca exista un pillar deja salvat pentru crearea podului;
	if (Bridge::save_pillar != nullptr) {
		//verificare daca pillarul apasat nu este acelasi cu cel salvat;
		if (Bridge::save_pillar == m_date[coordinates.y][coordinates.x].get()) {
			//in caz ca da se va scoate din salvare;
			Bridge::save_pillar = nullptr;
		}
		else {
			//verificare daca bridgeul creat nu se intersecteaza cu alte poduri;
			if (!isNotIntersection(Bridge::save_pillar->getCoordinates(), coordinates)) return;
			//creare Bridge;
			m_bridges[TwoPoint{ coordinates, Bridge::save_pillar->getCoordinates() }] =
				std::make_unique<Bridge>(coordinates, Bridge::save_pillar->getCoordinates(),
					static_cast<Game*>(getParent())->getCurrentPlayer()->getColor(), this);
			//playerului curent i se scade un bridge;
			static_cast<Game*>(getParent())->getCurrentPlayer()->updateNumberBridges(-1);
			//adaug conexiunile dintre cei doi noi vecini;
			Bridge::save_pillar->addNeighbor(static_cast<Pillar*>(m_date[coordinates.y][coordinates.x].get()));
			static_cast<Pillar*>(m_date[coordinates.y][coordinates.x].get())->addNeighbor(Bridge::save_pillar);
			//reinitializez save_pillar cu nullptr;
			Bridge::save_pillar = nullptr;
		}
	}
	else {
		Bridge::save_pillar = static_cast<Pillar*>(m_date[coordinates.y][coordinates.x].get());
	}
}

void Board::removeBridge(Point& first, Point& last)
{
	//stergerea podului;
	m_bridges.erase({ first,last });
	//playerului curent i se adauga un bridge;
	static_cast<Game*>(getParent())->getCurrentPlayer()->updateNumberBridges(1);
	//stergerea conexiuni de vecinatate dintre cei doi pillari;
	static_cast<Pillar*>(m_date[first.y][first.x].get())->removeNeighbor(last);
	static_cast<Pillar*>(m_date[last.y][last.x].get())->removeNeighbor(first);
}

std::ostream& operator<<(std::ostream& output, const Board& board)
{
	std::cout << "   ";
	for (int i = 0; i < board.getData().size(); i++) {
		std::cout << std::setw(3) << i;
	}
	std::cout << "\n";
	for (const auto& [y, row] : std::views::enumerate(board.getData()))
	{
		output << std::setw(2) << y << "  ";
		for (const auto& [x, element] : std::views::enumerate(row)) {
			if (element == nullptr) {
				output << "   ";
				continue;
			}
			if (element->getColor() != PieceColor::None) {
				output << ' ' << pieceColorToChar(element->getColor()) << ' ';
			}
			else {
				output << " . ";
			}
		}
		output << "\n";
	}
	output << "\n";
	output << "Bridges: ";
	for (const auto& pair : board.getBridges()) {
		output << "(" << pieceColorToChar(pair.second->getColor())<<" "
			<< pair.first.first.x << " " << pair.first.first.y << " , "
			<< pair.first.last.x << " " << pair.first.last.y << "); ";
	}
	return output;
}
