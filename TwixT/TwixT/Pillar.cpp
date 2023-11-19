#include "Pillar.h"
#include "GameBoard.h"

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
	QString backgroundColor = "background-color: " + color.name() + ";";

	setStyleSheet(backgroundColor + border);
	show();
}

void Pillar::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton) {
		Pillar* check = dynamic_cast<Pillar*>(this);
		if (check != nullptr) {
			static_cast<GameBoard*>(parentWidget())->addBase(radius, coordonates, GameBoard::BASE_COLOR);
			static_cast<GameBoard*>(parentWidget())->removePiece(this, coordonates);
		}
		else {
			//to do delete bridge
		}
	}
	else {
		//to add bridge
	}
	
}

