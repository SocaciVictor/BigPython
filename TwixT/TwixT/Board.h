#pragma once
#include <ranges>
#include<vector>
#include "Base.h"

class Board : public GameElement
{
protected:
	std::uint8_t m_rows;
	std::uint8_t m_columns;
	std::vector<std::vector<std::unique_ptr<Base>>> m_date;
public:
	Board() = default;
	Board(std::uint8_t rows, std::uint8_t columns, GameElement* parent = nullptr);
	const std::vector<std::vector<std::unique_ptr<Base>>>& getData() const noexcept;
	void addPillar(Point coordinates);
	void addBridge(Point coordinates);
	friend std::ostream& operator<<(std::ostream& output, const Board& board);
};