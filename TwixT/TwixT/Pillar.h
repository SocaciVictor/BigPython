#pragma once
#include "Piece.h"
class Pillar : public Piece
{
private:

public:
	Pillar(const QColor& color, QPoint coordonates, uint16_t radius, QWidget* parent);
	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent*) override;
};

