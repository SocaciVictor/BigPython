#pragma once
#include <QtWidgets>
#include "MainWindow.h"


class Piece : public QWidget
{
private:
	
protected:
	QColor color;
public:

	Piece(const QColor& color, QWidget* parent);
	Piece(const Piece&) = default;
	Piece(Piece&&) = default;
	Piece& operator=(const Piece&) = default;
	Piece& operator=(Piece&&) = default;
	virtual ~Piece() = default;

	const bool isCurentPlayer(const QColor& playerColor);
};

