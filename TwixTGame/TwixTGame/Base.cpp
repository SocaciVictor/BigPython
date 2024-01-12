#include "Base.h"

char pieceColorToChar(const PieceColor& color)
{
	switch (color) {
	case PieceColor::Blue: return 'B';
	case PieceColor::Red: return 'R';
	case PieceColor::None: return 'N';
	default: return '?';
	}
}

PieceColor charToPieceColor(const char& character)
{
	switch (character) {
	case 'B': return PieceColor::Blue;
	case 'R': return PieceColor::Red;
	default: return PieceColor::None;
	}
}

//Clasa Base
Base::Base(const Point& coordinates) : m_coordinates{coordinates}
{}

const Point& Base::getCoordinates() const noexcept
{
	return m_coordinates;
}

PieceColor Base::getColor() const noexcept
{
	return PieceColor::None;
}

//Clasa Pillar
Pillar::Pillar(const Point& coordinates, const PieceColor& color) :
	Base{ coordinates}, m_color{ color }
{}

void Pillar::addNeighbor(const Point & neighbor)
{
	m_neighbors.insert(neighbor);
}

void Pillar::removeNeighbor(const Point& neighbor)
{
	m_neighbors.erase(neighbor);
}

const std::unordered_set<Point, PointHash>& Pillar::getNeighbors() const noexcept
{
	return m_neighbors;
}

PieceColor Pillar::getColor() const noexcept
{
	return m_color;
}
