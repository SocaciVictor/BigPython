#pragma once
#include "Base.h"
class Bridge 
{
private:
	Point m_start, m_end;
	PieceColor m_color;
public:
	Bridge(const Point& start = { 0,0 }, const Point& end = { 0,0 }, const PieceColor& color = { PieceColor::None });
	const PieceColor& getColor() const noexcept;
	Point getStartPoint() const noexcept;
	Point getEndPoint() const noexcept;
};

