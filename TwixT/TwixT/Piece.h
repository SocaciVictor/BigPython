#pragma once
#include <QtWidgets>
class Piece : public QWidget
{
private:
	QColor color;
	QPoint coordonates;
public:
	Piece(QColor& color, QPoint& coordonates);
	Piece(Piece&) = default;
	Piece(Piece&&) = default;
	Piece& operator=(Piece&) = default;
	Piece& operator=(Piece&&) = default;
	virtual ~Piece() = default;
};

