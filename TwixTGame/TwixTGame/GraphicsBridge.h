#pragma once
#include <QGraphicsLineItem>
#include <QPen>
#include <QMouseEvent>
#include <QEvent>
#include <QCursor>
#include "Base.h"
#

class GraphicsBridge : public QObject, public QGraphicsLineItem
{
	Q_OBJECT
private:
	Point m_point1;
	Point m_point2;
	QColor m_color;
public:
	GraphicsBridge() = default;
	GraphicsBridge(const uint16_t size, const Point& point1, const Point& point2, const QString& color, QGraphicsItem* parent = nullptr);
	const Point& getStart() const noexcept;
	const Point& getEnd() const noexcept;
	const QColor& getColor() const noexcept;
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
signals:
	void bridgeClicked(GraphicsBridge* base);
signals:
	void bridgeHover(GraphicsBridge* base);
};

