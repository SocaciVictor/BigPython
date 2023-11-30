#include "Base.h"
#include "Board.h"

void Base::click()
{
	std::cout << "Click on: " << getCoordinates().x << ", " << getCoordinates().y << " base\n";
	static_cast<Board*>(getParent())->addPillar(getCoordinates());
}

//Clasa Base

Base::Base(Point coordinates, GameElement* parent) :
	GameElement{ parent }, m_coordinates{ coordinates }
{}

const Point& Base::getCoordinates() const noexcept
{
	return m_coordinates;
}

PieceColor Base::getColor() const noexcept
{
	return PieceColor::None;
}