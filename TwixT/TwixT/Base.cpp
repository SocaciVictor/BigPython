#include "Base.h"
#include "Board.h"

char pieceColorToChar(PieceColor color)
{
	switch (color) {
	case PieceColor::Red: return 'R';
	case PieceColor::Black: return 'B';
	case PieceColor::None: return 'N';
	default: return '?';
	}
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

void Base::click()
{
	std::cout << "Click on: " << getCoordinates().x << ", " << getCoordinates().y << " base!\n";
	static_cast<Board*>(getParent())->addPillar(getCoordinates());
}


//Clasa Pillar
Pillar::Pillar(Point coordinates, PieceColor color, GameElement* parent) :
	Base{ coordinates, parent }, m_color{ color }
{}

PieceColor Pillar::getColor() const noexcept
{
	return m_color;
}

void Pillar::click()
{
	std::cout << "Click on: " << getCoordinates().x << ", " << getCoordinates().y << " pillar!\n";
	static_cast<Board*>(getParent())->addBridge(getCoordinates());
}
