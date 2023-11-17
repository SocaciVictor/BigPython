#include "Pillar.h"

Pillar::Pillar(const QColor& color, QPoint& coordonates, uint16_t& radius) :
	Piece(color, coordonates, radius)
{}

void Pillar::paintEvent(QPaintEvent*)
{
	setFixedSize(radius * 2, radius * 2);
	move(coordonates.x() - radius, coordonates.y() - radius);
	QString border = "border-radius: " + QString::number(radius) + "px;border: none";
	QString backgroundColor = "background-color:" + color.name() + ";";
	setStyleSheet(backgroundColor + border);
}
