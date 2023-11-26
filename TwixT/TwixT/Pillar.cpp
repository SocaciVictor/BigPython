#include "Pillar.h"
#include "GameBoard.h"

Pillar::Pillar(const QColor& color, QPoint coordinates, uint16_t radius, QWidget* parent) :
	Piece{ color, parent },m_coordinates{coordinates},m_radius{radius}
{
	paintEvent(nullptr);
}

void Pillar::paintEvent(QPaintEvent*){
	setFixedSize(m_radius * 2, m_radius * 2);
	//mut Base astfel incat sa aiba mijlocul fix in punctul coordinates
	move(m_coordinates.x() - m_radius, m_coordinates.y() - m_radius);

	QString border = "border-radius: " + QString::number(m_radius) + "px;border: none;";
	QString backgroundColor = "background-color: " + color.name() + ";";

	setStyleSheet(backgroundColor + border);
	show();
}

void Pillar::mousePressEvent(QMouseEvent* event){
	if (event->button() == Qt::RightButton) {
		Pillar* check = dynamic_cast<Pillar*>(this);
		if (check != nullptr) {
			static_cast<GameBoard*>(parentWidget())->addBase(m_radius, m_coordinates, GameBoard::BASE_COLOR);
			static_cast<GameBoard*>(parentWidget())->removePiece(this, m_coordinates);
		}
		else {
			//to do delete bridge
		}
	}
	else if (event->button() == Qt::LeftButton) {

		if (Bridge::save_pillar != nullptr) {
			//check if pillar belongs to curent player
			if (!isCurentPlayer(static_cast<GameBoard*>(parentWidget())->curentPlayer->getColor())) {
				Bridge::save_pillar = nullptr;
				return;
			}
			
			//Bridge bridge(Bridge::save_pillar, this, this->color, this->parentWidget());
			static_cast<GameBoard*>(parentWidget())->addPiece(Bridge::save_pillar, this);
			Bridge::save_pillar = nullptr;
		}
		else {
			Bridge::save_pillar = this;
		}
	}

}

const QPoint& Pillar::getCoordinates() const noexcept
{
	return m_coordinates;
}

