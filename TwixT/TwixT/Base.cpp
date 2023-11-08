#include "Base.h"

Base::Base(QWidget* parent) :
	QWidget{ parent }, radius{ 5 }, coordinates{ QPoint{5,5} }, background_color{ QColor{"blue"} }
{
	styleBase();
}

Base::Base(uint16_t radius, uint16_t poz_x, uint16_t poz_y, QColor background_color, QWidget* parent) :
	QWidget{ parent }, radius{ radius }, coordinates{ QPoint(poz_x,poz_y) }, background_color{ QColor{background_color} }
{
	styleBase();
}

Base::~Base()
{}