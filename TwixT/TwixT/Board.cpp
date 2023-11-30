#include "Board.h"
#include "Game.h"

Board::Board(std::uint8_t rows, std::uint8_t columns, GameElement* parent) :
	GameElement{ parent }, m_rows{ rows }, m_columns{ columns }
{
	m_date.resize(m_rows);
	for (std::uint8_t i = 0; i < m_rows; i++) {
		m_date[i].resize(m_columns);
		for (std::uint8_t j = 0; j < m_columns; j++) {
			if (i == 0 && j == 0) continue;
			if (i == 0 && j == m_columns - 1) continue;
			if (i == m_rows - 1 && j == 0) continue;
			if (i == m_rows - 1 && j == columns - 1) continue;
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
	//verifica
	m_date[coordinates.y][coordinates.x] =
		std::make_unique<Pillar>(coordinates, static_cast<Game*>(getParent())->getCurrentPlayer()->getColor(), this);
	static_cast<Game*>(getParent())->getCurrentPlayer()->setMoved(true);
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
