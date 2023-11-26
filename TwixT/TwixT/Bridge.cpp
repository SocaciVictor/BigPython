#include "Bridge.h"

Bridge::Bridge(Pillar* start, Pillar* end, QColor color, QWidget* parent) :
	Piece{color,parent}
{
	p_start = start->getCoordinates();
	p_end = end->getCoordinates();
	paintEvent(nullptr);
}
void Bridge::paintEvent(QPaintEvent*){
	//setFixedSize(radius * 2, radius * 2);
	////mut Base astfel incat sa aiba mijlocul fix in punctul coordinates
	//move(coordinates.x() - radius, coordinates.y() - radius);

	//QString border = "border-radius: " + QString::number(radius) + "px;border: none;";
	//QString backgroundColor = "background-color:" + background_color.name() + ";";

	//setStyleSheet(backgroundColor + border);
	//show();
}
Pillar* Bridge::save_pillar = nullptr;
