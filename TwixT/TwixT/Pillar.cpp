#include "Pillar.h"

Pillar::Pillar(const QColor& color, QPoint coordonates, uint16_t radius, QWidget* parent) :
	Piece(color,coordonates, radius, parent)
{
	paintEvent(nullptr);
}

void Pillar::paintEvent(QPaintEvent*){
	setFixedSize(radius * 2, radius * 2);
	//mut Base astfel incat sa aiba mijlocul fix in punctul coordinates
	move(coordonates.x() - radius, coordonates.y() - radius);

	QString border = "border-radius: " + QString::number(radius) + "px;border: none;";
	QString backgroundColor = "background-color: #ff0000;";// + color.name() + ";";

	setStyleSheet(backgroundColor + border);
	show();
}

void Pillar::mousePressEvent(QMouseEvent*)
{
	//to add bridge
}

