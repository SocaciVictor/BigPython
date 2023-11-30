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
