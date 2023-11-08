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
