#include "Board.h"
#include "Game.h"

bool Board::isNotIntersection(const Point& p1, const Point& p2)
{
	//calculam directiile
	short dx = p1.x - p2.x;
	short dy = p1.y - p2.y;
	//verificam daca distantele calculate sunt egale cu 3 (daca e 3 inseamna ca e forma de L);
	if (abs(dx) + abs(dy) != 3) return false;

	//initializam erorile distantelor cu 1;
	short erorY = 1;
	short erorX = 1;

	//verificam in ce cadran ne aflam;
	if (dy < 0) erorY = -1;
	if (dx < 0) erorX = -1;

	//vectori pentru cazul dx>dy cadran 1;
	short X1[9]{ -1,0,-2,1,-1,-1,-2,-2,-1 }; // x pt P1;
	short Y1[9]{ 1,-1,0,-1,-1,0,1,-2,-1 }; // y pt P1;
	short X2[9]{ 2,0,1,1,-1,2,1,1,2 }; // x pt P2;
	short Y2[9]{ 0,1,-1,1,1,-1,0,1,2 }; // y pt P2;

	//verificam care directie e mai mare;
	if (abs(dx) < abs(dy)) {
		std::swap(X1, Y1);
		std::swap(X2, Y2);
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

void Board::addPillar(Point coordinates)
{
	//verificare daca playerul a adaugat deja un pillar sa nu mai poata adauga;
	if (static_cast<Game*>(getParent())->getCurrentPlayer()->getMoved()) return;
	//verificare ca playerul sa nu poata adauga pillar in bazele inamice;
	if (static_cast<Game*>(getParent())->getCurrentPlayer()->getColor() == PieceColor::Red &&
		coordinates.x == 0 || coordinates.x == m_columns
		) return;
	if (static_cast<Game*>(getParent())->getCurrentPlayer()->getColor() == PieceColor::Black &&
		coordinates.y == 0 || coordinates.y == m_rows
		) return;
	//daca verificarile sunt bune se va adauga pillarul;
	m_date[coordinates.y][coordinates.x] =
		std::make_unique<Pillar>(coordinates, static_cast<Game*>(getParent())->getCurrentPlayer()->getColor(), this);
	//playerul este setat ca si cum a adaugat deja un pillar;
	static_cast<Game*>(getParent())->getCurrentPlayer()->setMoved(true);
}

void Board::addBridge(Point coordinates)
{
	//verificare daca player a adaugat pilon
	if (!static_cast<Game*>(getParent())->getCurrentPlayer()->getMoved()) return;
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
			//creare Bridge;
			bridges[TwoPoint{ coordinates, Bridge::save_pillar->getCoordinates() }] =
				std::make_unique<Bridge>(coordinates, Bridge::save_pillar->getCoordinates(), static_cast<Game*>(getParent())->getCurrentPlayer()->getColor(),
					this);
			Bridge::save_pillar = nullptr;
		}
	}
	else {
		Bridge::save_pillar = static_cast<Pillar*>(m_date[coordinates.y][coordinates.x].get());
	}
}

std::ostream& operator<<(std::ostream& output, const Board& board)
{
	for (const auto& [y, row] : std::views::enumerate(board.getData()))
	{
		for (const auto& [x, element] : std::views::enumerate(row)) {
			if (element == nullptr) {
				output << "  ";
				continue;
			}
			if (element->getColor() != PieceColor::None) {
				output << pieceColorToChar(element->getColor()) << ' ';
			}
			else {
				output << "_ ";
			}
		}
		output << "\n";
	}
	return output;
}
