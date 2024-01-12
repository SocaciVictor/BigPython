#pragma once
#include<iostream>
#include <unordered_set>

enum class PieceType : std::uint8_t {
	BluePillar,
	BlueBridge,
	RedPillar,
	RedBridge,
	None
};

enum class PieceColor : std::uint8_t {
	Blue,
	Red,
	None
};

char pieceColorToChar(const PieceColor& color);

PieceColor charToPieceColor(const char& character);

struct Point {
	std::uint16_t x;
	std::uint16_t y;
	Point() = default;
	Point(const std::uint16_t& c_x,const std::uint16_t& c_y) : x{ c_x }, y{ c_y } {};
	bool operator==(const Point& other) const {
		return ((x == other.x) && (y == other.y));
	}
	bool operator<(const Point& other) const { //the minimum point is the one at top left corner
		if (y == other.y)
			return (x < other.x);
		return (y < other.y);
	}
	friend std::ostream& operator<<(std::ostream& out, const Point& point) {
		out << "(" << point.x << ", " << point.y << ")";
		return out;
	}
};

struct PointHash {
	size_t operator()(const Point& p) const {
		size_t hashX = std::hash<uint16_t>{}(p.x);
		size_t hashY = std::hash<uint16_t>{}(p.y);
		return hashX ^ (hashY << 1);
	}
};

struct TwoPoint {
	Point point1;
	Point point2;
	TwoPoint() = default;
	TwoPoint(const Point& first, const Point& last) : point1{ first }, point2{ last } {}
	bool operator==(const TwoPoint& other) const {
		return ((point1 == other.point1 && point2 == other.point2) || (point1 == other.point2 && point2 == other.point1));
	}
};

struct TwoPointHash {
	size_t operator()(const TwoPoint& two) const {
		size_t hashX = PointHash{}(two.point1);
		size_t hashY = PointHash{}(two.point2);
		return hashX ^ (hashY);
	}
};

//Clasa Base
class Base
{
protected:
	Point m_coordinates;
public:
	Base(const Point& coordinates);
	const Point& getCoordinates() const noexcept;
	virtual PieceColor getColor() const noexcept;
};

//Clasa Pillar
class Pillar : public Base
{
protected:
	PieceColor m_color;
	std::unordered_set<Point, PointHash> m_neighbors;
public:
	Pillar(const Point& coordinates,const PieceColor& color);
	void addNeighbor(const Point& neighbor);
	void removeNeighbor(const Point& neighbor);
	const std::unordered_set<Point, PointHash>& getNeighbors() const noexcept;
	PieceColor getColor() const noexcept override;
};



