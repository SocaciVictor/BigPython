#pragma once
#include <QtWidgets>
#include "GameBoard.h"

class Piece : public QWidget
{
private:
	QColor color;
	QPoint coordonates;
	inline static GameBoard* parentBoard = nullptr;
public:
	static void setBoard(GameBoard* board);
	Piece(const QColor& color, QPoint& coordonates);
	Piece(const Piece&) = default;
	Piece(Piece&&) = default;
	Piece& operator=(const Piece&) = default;
	Piece& operator=(Piece&&) = default;
	virtual ~Piece() = default;
};

