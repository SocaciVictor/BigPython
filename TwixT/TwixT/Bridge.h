#pragma once
#include "Base.h"

class Bridge : public GameElement
{
private:
	Point m_start, m_end;
	PieceColor m_color;
public:
	static Pillar* save_pillar;
	Bridge(Point start, Point end, PieceColor color,GameElement* parent = nullptr);
};





