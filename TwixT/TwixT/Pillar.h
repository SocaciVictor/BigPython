#pragma once
#include "Piece.h"
class Pillar : public Piece
{
private:
	QPoint m_coordinates;
	uint16_t m_radius;
public:
	Pillar(const QColor& color, QPoint coordinates, uint16_t radius, QWidget* parent);
	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent*) override;
	const QPoint& getCoordinates() const noexcept;

	
};

