#pragma once
#include <QWidget>

class GameBoard : public QWidget
{
private:
	int size; //size ul per linie si coloana
	int lines;
	int columns;
	int size_width;
	int size_height;
	QPoint coordinates; //pozitia la centrul widgetului
	QColor background_color;
	QVector<QVector<QWidget*>> bases;
public:
	//Constructori
	GameBoard(QWidget* parent = nullptr);
	GameBoard(int size, QWidget* parent = nullptr);
	GameBoard(int size, QColor backround_color, QWidget* parent = nullptr);
	GameBoard(int lines, int columns, QWidget* parent = nullptr);
	GameBoard(int size, int lines, int columns, QWidget* parent = nullptr);
	GameBoard(int size, int lines, int columns, int poz_x, int poz_y, QWidget* parent = nullptr);
	GameBoard(int size, int lines, int collumns, QPoint coordinates, QWidget* parent = nullptr);
	GameBoard(int size, int lines, int columns, int poz_x, int poz_y, QColor backround_color, QWidget* parent = nullptr);
	GameBoard(int size, int lines, int columns, QPoint coordinates, QColor backround_color, QWidget* parent = nullptr);
	//Deconstructor
	~GameBoard();
protected:
	void styleBoard();
	void paintEvent(QPaintEvent*);
	void addBases();
};
