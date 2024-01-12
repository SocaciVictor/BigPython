#pragma once
#include <QGraphicsLineItem>
#include <QPen>
#include "Base.h"

class GraphicsBridge : public QGraphicsLineItem
{
private:
	Point m_point1;
	Point m_point2;
	QColor m_color;
public:
	GraphicsBridge() = default;
	GraphicsBridge(const uint16_t size, const Point& point1, const Point& point2, const QString& color, QGraphicsItem* parent = nullptr);
	
};

