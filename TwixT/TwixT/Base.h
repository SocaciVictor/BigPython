#pragma once
#include "GameElement.h"
#include<iostream>
#include <unordered_map>
#include<memory>

enum class PieceColor : std::uint8_t {
	Red,
	Black,
	None
};

char pieceColorToChar(PieceColor color);

struct Point {
	std::uint16_t x;
	std::uint16_t y;
	Point(std::uint16_t c_x, std::uint16_t c_y) : x{ c_x }, y{ c_y } {};
	bool operator==(const Point& other) const {
		return ((x == other.x) && (y == other.y));
	}
};
struct PointHash {
	size_t operator()(const Point& p) const {
		size_t hashX = std::hash<int>{}(p.x);
		size_t hashY = std::hash<int>{}(p.y);
		return hashX ^ (hashY << 1);
	}
};
struct TwoPoint {
	Point first;
	Point last;
	TwoPoint(Point first, Point last) : first{ first }, last{ last } {}
	bool operator==(const TwoPoint& other) const {
		return ((first == other.first && last == other.last) || (first == other.last && last == other.first));
	}
};
struct TwoPointHash {
	size_t operator()(const TwoPoint& two) const {
		size_t hashX = PointHash{}(two.first);
		size_t hashY = PointHash{}(two.last);
		return hashX ^ (hashY);
	}
};

class Base : public GameElement {
protected:
	Point m_coordinates;
public:
	Base(Point coordinates, GameElement* parent = nullptr);
	const Point& getCoordinates() const noexcept;
	virtual PieceColor getColor() const noexcept;
	virtual void click();
};

class Pillar : public Base
{
protected:
	PieceColor m_color;
	std::unordered_map<Point, Pillar*, PointHash> m_neighbors;
public:
	Pillar(Point coordinates, PieceColor color, GameElement* parent = nullptr);
	void addNeighbor(Pillar* neighbor);
	void removeNeighbor(Point& point);
	const auto& getNeighbors() const noexcept;
	PieceColor getColor() const noexcept override;
	void click();
};
