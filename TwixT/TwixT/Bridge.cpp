#include "Bridge.h"

Bridge::Bridge(Point start, Point end, PieceColor color, GameElement* parent) :
	GameElement{ parent }, m_start{ start }, m_end{ end }, m_color{ color }
{}

const PieceColor& Bridge::getColor() const noexcept
{
	return m_color;
}

Pillar* Bridge::save_pillar = nullptr;