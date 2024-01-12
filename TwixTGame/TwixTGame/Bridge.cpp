#include "Bridge.h"

Bridge::Bridge(const Point& start, const Point& end, const PieceColor& color) :
	m_start{ start }, m_end{ end }, m_color{ color }
{}

const PieceColor& Bridge::getColor() const noexcept
{
	return m_color;
}