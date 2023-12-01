#include "Bridge.h"

Bridge::Bridge(Point start, Point end, PieceColor color, GameElement* parent) :
	GameElement{ parent }, m_start{ start }, m_end{ end }, m_color{ color }
{}

Pillar* Bridge::save_pillar = nullptr;