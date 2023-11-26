#include "Piece.h"

Piece::Piece(const QColor& color, QWidget* parent) :
	QWidget(parent), color{ color }
{}

const bool Piece::isCurentPlayer(const QColor& playerColor){
	if (playerColor == color)
		return true;
	return false;
}
