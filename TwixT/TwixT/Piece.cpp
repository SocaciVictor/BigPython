#include "Piece.h"

Piece::Piece(const QColor& color, QPoint coordonates, uint16_t radius, QWidget* parent) :
	QWidget(parent), color{ color }, coordonates{ coordonates }, radius{radius}
{}
