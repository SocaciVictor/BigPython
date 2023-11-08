#include "MainWindow.h"

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