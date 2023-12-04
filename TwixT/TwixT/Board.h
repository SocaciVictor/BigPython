#pragma once
#include <ranges>
#include<vector>
#include "Base.h"
#include "Bridge.h"
#include <unordered_map>
#include <algorithm>
#include <string>

enum class State : std::uint8_t
{
	None,
	Draw,
	Win,
};

class Board : public GameElement
{
protected:
	std::uint8_t m_rows;
	std::uint8_t m_columns;
	std::vector<std::vector<std::unique_ptr<Base>>> m_date;
	std::unordered_map<TwoPoint, std::unique_ptr<Bridge>, TwoPointHash> m_bridges;
	bool isNotIntersection(const Point& p1, const Point& p2);
public:
	Board() = default;
	Board(std::uint8_t rows, std::uint8_t columns, GameElement* parent = nullptr);
	const std::vector<std::vector<std::unique_ptr<Base>>>& getData() const noexcept;
	const auto& getBridges() const noexcept;
	void addPillar(Point coordinates);
	void addBridge(Point coordinates);
	friend std::ostream& operator<<(std::ostream& output, const Board& board);
};