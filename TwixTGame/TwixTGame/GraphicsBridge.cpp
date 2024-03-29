#include "GraphicsBridge.h"


GraphicsBridge::GraphicsBridge(const uint16_t size, const Point& point1, const Point& point2, const QString& color, QGraphicsItem* parent) :
	QGraphicsLineItem(parent), m_point1{point1},m_point2{point2},m_color{color}
{
	uint16_t margine_distance = 24 / size * 35;
	uint16_t base_size = (490 - margine_distance * 2) / (3 * size - 2);
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton);
	setLine(235 + margine_distance + point1.x * 3 * base_size + base_size / 2, 25 + margine_distance + point1.y * 3 * base_size + base_size / 2,
		235 + margine_distance + point2.x * 3 * base_size + base_size / 2, 25 + margine_distance + point2.y * 3 * base_size + base_size / 2);
	setTransformOriginPoint(boundingRect().center());
	QPen pen;
	pen.setColor(m_color);
	pen.setWidth(base_size/6 * 4);
	setPen(pen);
}

const Point& GraphicsBridge::getStart() const noexcept
{
	return m_point1;
}

const Point& GraphicsBridge::getEnd() const noexcept
{
	return m_point2;
}

const QColor& GraphicsBridge::getColor() const noexcept
{
	return m_color;
}

void GraphicsBridge::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	emit bridgeClicked(this);
}

void GraphicsBridge::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	emit bridgeHover(this);
}

void GraphicsBridge::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	QPen new_pen{ pen() };
	new_pen.setColor(m_color);
	setPen(new_pen);
	setCursor(Qt::ArrowCursor);
}
