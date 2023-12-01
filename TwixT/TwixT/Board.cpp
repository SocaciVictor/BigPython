#include "Board.h"
#include "Game.h"

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
		coordinates.x == 0 || coordinates.x == 23
		) return;
	if (static_cast<Game*>(getParent())->getCurrentPlayer()->getColor() == PieceColor::Black &&
		coordinates.y == 0 || coordinates.y == 23
		) return;
	//daca verificarile sunt bune se va adauga pillarul;
	m_date[coordinates.y][coordinates.x] =
		std::make_unique<Pillar>(coordinates, static_cast<Game*>(getParent())->getCurrentPlayer()->getColor(), this);
	//playerul este setat ca si cum a adaugat deja un pillar;
	static_cast<Game*>(getParent())->getCurrentPlayer()->setMoved(true);
}

void Board::addBridge(Point coordinates)
{
	//verificare daca pillarul pe care sa apasat este de aceiasi culoare cu playerul current;
	if (m_date[coordinates.y][coordinates.x]->getColor() !=
		static_cast<Game*>(getParent())->getCurrentPlayer()->getColor()) return;

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
