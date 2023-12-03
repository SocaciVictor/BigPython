#pragma once
#include <ranges>
#include<vector>
#include "Base.h"
#include "Bridge.h"
#include <unordered_map>
#include <algorithm>
#include <string>

//bool operator==(const std::pair<Point, Point>& p1, const std::pair<Point, Point>& p2) {
//	return(((p1.first == p2.first) && (p1.second == p2.second)) ||
//		((p1.first == p2.second) && (p1.second == p2.first)));
//}

class Hash {
public:
	std::size_t operator()(const std::pair<Point, Point>& p) const
	{
		return std::hash<std::string>()(std::to_string(std::min(p.first.x, p.second.x) + std::max(p.first.x, p.second.x)) + 
			std::to_string(std::min(p.first.y, p.second.y) + std::max(p.first.y, p.second.y)));
	}
};


class Board : public GameElement
{
protected:
	std::uint8_t m_rows;
	std::uint8_t m_columns;
	std::vector<std::vector<std::unique_ptr<Base>>> m_date;
	std::unordered_map<TwoPoint, std::unique_ptr<Bridge>, TwoPointHash> bridges;
	static bool isNotIntersection(const Point& p1, const Point& p2);
public:
	Board() = default;
	Board(std::uint8_t rows, std::uint8_t columns, GameElement* parent = nullptr);
	const std::vector<std::vector<std::unique_ptr<Base>>>& getData() const noexcept;
	void addPillar(Point coordinates);
	void addBridge(Point coordinates);
	friend std::ostream& operator<<(std::ostream& output, const Board& board);
};