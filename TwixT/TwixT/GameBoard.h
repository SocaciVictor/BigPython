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
	
};
