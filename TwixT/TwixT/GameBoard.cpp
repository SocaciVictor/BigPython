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

GameBoard::GameBoard(int size, QWidget* parent) : QWidget(parent)
{
	this->size = size;
	this->lines = 10;
	this->columns = 10;
	this->size_width = this->size * (this->columns + 1);
	this->size_height = this->size * (this->lines + 1);
	this->coordinates = QPoint(this->size_width / 2, this->size_height / 2);
	this->background_color = QColor("blue");

	styleBoard();
	addBases();
}

GameBoard::GameBoard(int size, QColor backround_color, QWidget* parent) : QWidget(parent)
{
	this->size = size;
	this->lines = 10;
	this->columns = 10;
	this->size_width = this->size * (this->columns + 1);
	this->size_height = this->size * (this->lines + 1);
	this->coordinates = QPoint(this->size_width / 2, this->size_height / 2);
	this->background_color = backround_color;

	styleBoard();
	addBases();
}

GameBoard::GameBoard(int lines, int columns, QWidget* parent) : QWidget(parent)
{
	this->size = 20;
	this->lines = lines;
	this->columns = columns;
	this->size_width = this->size * (this->columns + 1);
	this->size_height = this->size * (this->lines + 1);
	this->coordinates = QPoint(this->size_width / 2, this->size_height / 2);
	this->background_color = QColor("blue");

	styleBoard();
	addBases();
}

GameBoard::GameBoard(int size, int lines, int columns, QWidget* parent) : QWidget(parent)
{
	this->size = size;
	this->lines = lines;
	this->columns = columns;
	this->size_width = this->size * (this->columns + 1);
	this->size_height = this->size * (this->lines + 1);
	this->coordinates = QPoint(this->size_width / 2, this->size_height / 2);
	this->background_color = QColor("blue");

	styleBoard();
	addBases();
}

GameBoard::GameBoard(int size, int lines, int columns, int poz_x, int poz_y, QWidget* parent) : QWidget(parent)
{
	this->size = size;
	this->lines = lines;
	this->columns = columns;
	this->size_width = this->size * (this->columns + 1);
	this->size_height = this->size * (this->lines + 1);
	this->coordinates = QPoint(poz_x, poz_y);
	this->background_color = QColor("blue");

	styleBoard();
	addBases();
}

GameBoard::GameBoard(int size, int lines, int collumns, QPoint coordinates, QWidget* parent) : QWidget(parent)
{
	this->size = size;
	this->lines = lines;
	this->columns = columns;
	this->size_width = this->size * (this->columns + 1);
	this->size_height = this->size * (this->lines + 1);
	this->coordinates = coordinates;
	this->background_color = QColor("blue");

	styleBoard();
	addBases();
}

GameBoard::GameBoard(int size, int lines, int columns, int poz_x, int poz_y, QColor backround_color, QWidget* parent) : QWidget(parent)
{
	this->size = size;
	this->lines = lines;
	this->columns = columns;
	this->size_width = this->size * (this->columns + 1);
	this->size_height = this->size * (this->lines + 1);
	this->coordinates = QPoint(poz_x, poz_y);
	this->background_color = backround_color;

	styleBoard();
	addBases();
}

GameBoard::GameBoard(int size, int lines, int columns, QPoint coordinates, QColor backround_color, QWidget* parent) : QWidget(parent)
{
	this->size = size;
	this->lines = lines;
	this->columns = columns;
	this->size_width = this->size * (this->columns + 1);
	this->size_height = this->size * (this->lines + 1);
	this->coordinates = coordinates;
	this->background_color = backround_color;

	styleBoard();
	addBases();
}
