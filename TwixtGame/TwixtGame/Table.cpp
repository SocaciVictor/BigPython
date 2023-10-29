#include "Table.h"

Table::Table(int height, int width, std::string color)
{
	this->height = height;
	this->width = width;
	this->color = color;
}

Table::~Table()
{
}

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
}

int Table::getHeight()
{
	return 0;
}

int Table::getWidth()
{
	return 0;
}

std::string Table::getColor()
{
	return std::string();
}
