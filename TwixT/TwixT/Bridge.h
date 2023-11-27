#pragma once
#include "Pillar.h"

class Bridge : public Piece
{
private:
	QPoint p_start, p_end;
	double calculUnghi(const QPoint& point1, const QPoint& point2);
public:
	static Pillar* save_pillar;
	Bridge() = default;
	Bridge(Pillar* start, Pillar* end,QColor color,QWidget* parent);
	void paintEvent(QPaintEvent*) override;
	
};
