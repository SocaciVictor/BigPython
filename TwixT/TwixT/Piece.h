#pragma once
#include <QtWidgets>

class Piece : public QWidget
{
private:
	
protected:
	uint16_t radius;
	QColor color;
	QPoint coordonates;
public:

	Piece(const QColor& color, QPoint& coordonates, uint16_t& radius);
	Piece(const Piece&) = default;
	Piece(Piece&&) = default;
	Piece& operator=(const Piece&) = default;
	Piece& operator=(Piece&&) = default;
	virtual ~Piece() = default;
};

