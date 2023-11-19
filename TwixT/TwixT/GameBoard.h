#pragma once
#include <QWidget>
#include "Player.h"
#include "Base.h"

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
	//pot fi pusi in constructori (da mai incolo)
	Player player1 = Player("red", QColor(Qt::red));
	Player player2 = Player("black", QColor(Qt::black));
	Player& curentPlayer = player1;

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

	GameBoard(const GameBoard&) = default;
	GameBoard& operator=(const GameBoard&) = default;

	//Deconstructor
	~GameBoard();

	void removeBase(Base* base);
	void addPiece(QPoint& coord, uint16_t& radius);
	void removePiece(Piece* piece, const QPoint& point);
	void addBase(uint16_t& radius, QPoint& point, QColor& background_color);

protected:
	void styleBoard();
	void paintEvent(QPaintEvent*) override;
	void addBases();
	
};
