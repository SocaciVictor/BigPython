#pragma once
#include "Base.h"
class Bridge 
{
private:
	Point m_start, m_end;
	PieceColor m_color;
public:
	Bridge() = default;
	Bridge(const Point& start, const Point& end, const PieceColor& color);
	const PieceColor& getColor() const noexcept;
};

