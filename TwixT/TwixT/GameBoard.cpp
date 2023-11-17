#include "GameBoard.h"
#include "Pillar.h"
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


GameBoard::~GameBoard(){
	for (auto& line : bases) {
		for (auto& base : line)
			delete base;
	}
}

void GameBoard::styleBoard()
{
	setFixedSize(size_width, size_height);
	//mut board astfel incat sa aiba mijlocul fix in punctul coordinates
	move(coordinates.x() - size_width / 2, coordinates.y() - size_height / 2);


	QString border = "border:" + QString::number(size / 10) + "px solid #AAAAAA;";
	QString backgroundColor = "background-color:" + background_color.name() + ";";

	setStyleSheet(backgroundColor + border);

}

void GameBoard::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	QPen pen;
	pen.setColor(Qt::red); // Setează culoarea liniei
	pen.setWidth(size / 5); // Setează grosimea liniei
	painter.setPen(pen);

	painter.drawLine(size * 2, size * 1.5, size * 23, size * 1.5);
	painter.drawLine(size * 2, size * 23.5, size * 23, size * 23.5);

	pen.setColor(Qt::black); // Setează culoarea liniei
	painter.setPen(pen);

	painter.drawLine(size * 1.5, size * 2, size * 1.5, size * 23);
	painter.drawLine(size * 23.5, size * 2, size * 23.5, size * 23);

}

void GameBoard::addBases()
{
	bases.resize(lines);
	for (uint16_t i{ 0 }; i < lines; i++) {
		bases[i].resize(columns);
		for (uint16_t j{ 0 }; j < columns; j++) {
			//verificari sa nu creez cele 4 colturi
			if (i == 0 && j == 0) continue;
			if (i == 0 && j == columns - 1) continue;
			if (i == lines - 1 && j == 0) continue;
			if (i == lines - 1 && j == columns - 1) continue;
			Base* base{ new Base{uint16_t(size / 5), uint16_t((j + 1) * size), uint16_t((i + 1) * size), "#808080", this} };
			bases[i][j] = base;
		}
	}
}

void GameBoard::addPiece(QPoint& coord, uint16_t& radius){
	if (curentPlayer.canPlace()) {
		Pillar* pillar{ new Pillar{curentPlayer.getColor(),coord, radius, this} };
		curentPlayer.addPiece(coord, pillar);
	}
}

void GameBoard::removeBase(Base* base){
	for(int i=0;i < bases.count();i++)
		for(int j=0;j<bases[i].count();j++)
			if (base == bases[i][j]) {
				bases[i].remove(j);
				delete base;
				return;
			}
}
