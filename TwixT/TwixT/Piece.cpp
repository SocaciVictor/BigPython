#include "Piece.h"

void Piece::setBoard(QWidget* board)
{
	parentBoard = board;
}

Piece::Piece(const QColor& color, QPoint& coordonates, uint16_t& radius) : 
	color{ color }, coordonates{ coordonates }, radius{radius}
{}
