#include "Mine.h"

void Mine::setActive(const bool& active)
{
	m_active = active;
}

Mine::Mine(const Point& coordinates, const bool& active, const PieceColor& color) : Base{ coordinates },
m_active{ active }, m_color{ color }
{}

bool Mine::getActive()
{
	return m_active;
}

void Mine::setColor(const PieceColor& color)
{
	m_color = color;
}

PieceColor Mine::getColor() const noexcept
{

	return m_color;
}
