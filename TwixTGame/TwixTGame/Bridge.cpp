#include "Bridge.h"

Bridge::Bridge(const Point& start, const Point& end, const PieceColor& color) :
	m_start{ start }, m_end{ end }, m_color{ color }
{}

const PieceColor& Bridge::getColor() const noexcept
{
	return m_color;
}
Point Bridge::getStartPoint() const noexcept
{
	return m_start;
}

Point Bridge::getEndPoint() const noexcept
{
	return m_end;
}