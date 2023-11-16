#include "Piece.h"

void Piece::setBoard(GameBoard* board)
{
	parentBoard = board;
}

Piece::Piece(const QColor& color, QPoint& coordonates) : color{ color }, coordonates{coordonates}
{
}
