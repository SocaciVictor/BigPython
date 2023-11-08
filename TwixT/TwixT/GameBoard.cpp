#include "GameBoard.h"
#include "Base.h"
#include<QPainter>

GameBoard::GameBoard(QWidget* parent) : QWidget(parent)
{
	this->size = 20;
	this->lines = 10;
	this->columns = 10;
	this->size_width = this->size * (this->columns + 1);
	this->size_height = this->size * (this->lines + 1);
	this->coordinates = QPoint(this->size_width / 2, this->size_height / 2);
	this->background_color = QColor("blue");

	styleBoard();
	addBases();
}

GameBoard::~GameBoard()
{}
