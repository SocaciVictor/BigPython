#include "MainWindow.h"
#include "GameBoard.h"
#include "Piece.h"

//Constructori
MainWindow::MainWindow(QWidget* parent)
{
	this->size_width = 800;
	this->size_height = 600;
	this->background_color = "#ffffff";

	styleMainWindow();
	displayChildren();
}

MainWindow::MainWindow(int width, int height, QWidget* parent)
{
	this->size_width = width;
	this->size_height = height;
	this->background_color = "#ffffff";

	styleMainWindow();
	displayChildren();
}

MainWindow::MainWindow(int width, int height, QColor background_color, QWidget* parent)
{
	this->size_width = width;
	this->size_height = height;
	this->background_color = background_color;

	styleMainWindow();
	displayChildren();
}

//Deconstructtor
MainWindow::~MainWindow()
{
	for (QWidget* widget : vector_widgeturi) {
		delete widget;
	}
	vector_widgeturi.clear();
}

//Geteri
int MainWindow::getWidth()
{
	return size_width;
}

int MainWindow::getHeight()
{
	return size_height;
}

QColor MainWindow::getColor()
{
	return background_color;
}

//Functie de stilizat fereastra
void MainWindow::styleMainWindow()
{
	//schimbarea marimi ferestrei
	resize(size_width, size_height);
	setFixedSize(size());
	//schimbarea culoarei de fundal
	QPalette palette;
	palette.setColor(QPalette::Window, background_color);
	setPalette(palette);
}

//functie de afisat widgeturi in aceasta
void MainWindow::displayChildren()
{
	addBoard();
}

void MainWindow::addBoard()
{
	GameBoard* board{ new GameBoard{ size_width / 50, 24, 24, size_width / 2, size_height / 2, "#C0C0C0", this } };
	vector_widgeturi.push_back(board);
}
