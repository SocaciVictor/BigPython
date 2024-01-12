#pragma once
#include"Base.h"
#include"Bridge.h"
#include"Player.h"
#include<iostream>
#include<vector>
#include<ranges>
#include<unordered_map>
#include<memory>
#include<queue>

class Board
{
protected:
	std::uint16_t m_rows;
	std::uint16_t m_columns;
	std::vector<std::vector<std::unique_ptr<Base>>> m_bases;
	std::unordered_map<TwoPoint, Bridge, TwoPointHash> m_bridges;
	const bool& isNotIntersection(const Point& p1, const Point& p2);
public:
	Board(const std::uint16_t& rows, const std::uint16_t& columns);
	Board() = default;
	const std::vector<std::vector<std::unique_ptr<Base>>>& getBases() const noexcept;
	const uint16_t& getRows() const noexcept;
	const uint16_t& getColumns() const noexcept;
	const std::unordered_map<TwoPoint, Bridge, TwoPointHash>& getBridges() const noexcept;
	const bool& isInBoard(const Point& point);
	const bool& addPillar(const Point& point, const PieceColor& color);
	const bool& addBridge(const Point& point1, const Point& point2, const PieceColor& color);
	uint16_t removePillar(const Point& point);
	const bool& removeBridge(const Point& point1, const Point& point2,const PieceColor& color);
	const bool& gameIsEnded(const Point& point1, const Point& point2,const PieceColor& color);
	friend std::ostream& operator<<(std::ostream& output, const Board& board);
	friend std::istream& operator>>(std::istream& input, Board& board);
};

