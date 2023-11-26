#pragma once
#include "Pillar.h"

class Bridge : public Piece
{
private:
	QPoint p_start, p_end;
public:
	Bridge() = default;
	Bridge(Pillar start, Pillar end,QColor color,QWidget* parent);

};

