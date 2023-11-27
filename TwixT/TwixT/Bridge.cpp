#include "Bridge.h"


double Bridge::calculUnghi(const QPoint& point1, const QPoint& point2)
{
	// Calculul coordonatelor relative
	double deltaX = point2.x() - point1.x();
	double deltaY = point2.y() - point1.y();

	// Calculul unghiului folosind atan2
	double unghiRad = atan2(deltaY, deltaX);

	return 0.0f;
}

Bridge::Bridge(Pillar* start, Pillar* end, QColor color, QWidget* parent) :
	Piece{color,parent}
{
	p_start = start->getCoordinates();
	p_end = end->getCoordinates();
	paintEvent(nullptr);
}
void Bridge::paintEvent(QPaintEvent*){
	setFixedSize(50, 50);
	//mut Base astfel incat sa aiba mijlocul fix in punctul coordinates
	move(200, 200);

	QString backgroundColor = "background-color:" + color.name() + ";";
	QString rotate = "transform: rotate(45deg);";
	setStyleSheet(backgroundColor + rotate);
	show();
}
Pillar* Bridge::save_pillar = nullptr;
