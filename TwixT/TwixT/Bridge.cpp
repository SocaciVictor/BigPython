#include "Bridge.h"


double Bridge::calculUnghi(const QPoint& point1, const QPoint& point2)
{
	// Calculul coordonatelor relative
	double deltaX = point2.x() - point1.x();
	double deltaY = point2.y() - point1.y();

	// Calculul unghiului folosind atan2
	double unghiRad = atan2(deltaY, deltaX);

	// Convertirea unghiului din radiani in grade
	double unghiGrade = unghiRad * 180.0 / M_PI;

	// Asigurarea că unghiul este în intervalul [0, 360)
	if (unghiGrade < 0) {
		unghiGrade += 360.0;
	}

	return unghiGrade;
}

double Bridge::dinstantaPoints(const QPoint& point1, const QPoint& point2)
{
	double deltaX = point2.x() - point1.x();
	double deltaY = point2.y() - point1.y();
	return std::sqrt(deltaX * deltaX + deltaY * deltaY);
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
