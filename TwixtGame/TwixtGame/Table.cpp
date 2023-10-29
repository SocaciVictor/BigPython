#include "Table.h"

//Constructor Deconstructor
Table::Table(int height, int width, std::string color = "white", int pozitionX = 0, int pozitionY = 0)
{
	this->height = height;
	this->width = width;
	this->color = color;
	this->pozitionX = pozitionX;
	this->pozitionY = pozitionY;
}

Table::~Table()
{
}

//Setteri

void Table::setHeight(int height)
{
	this->height = height;
}

void Table::setWidth(int width)
{
	this->width = width;
}

void Table::setColor(std::string color)
{
	this->color = color;
}

void Table::setPozitionX()
{
	this->pozitionX = pozitionX;
}

void Table::setPozitionY()
{
	this->pozitionY = pozitionY;
}

//Geteri

int Table::getHeight()
{
	return this->height;
}

int Table::getWidth()
{
	return this->width;
}

int Table::getPozitionX()
{
	return this->pozitionX;
}

int Table::getPozitionY()
{
	return this->pozitionY;
}

std::string Table::getColor()
{
	return this->color;
}
