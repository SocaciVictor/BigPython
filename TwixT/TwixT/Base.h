#pragma once
#include "GameElement.h"
#include<iostream>

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

public:
	Pillar(Point coordinates, PieceColor color, GameElement* parent = nullptr);
	PieceColor getColor() const noexcept override;
	void click();
};
