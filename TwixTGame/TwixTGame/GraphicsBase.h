#pragma once
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QMouseEvent>
#include <QEvent>
#include <QCursor>
#include <QTransform>
#include "Base.h"

const QString pieceColorToColor(const PieceColor& piece_color);
const QString pieceColorToHoverColor(const PieceColor& piece_color);
const PieceColor colorToPieceColor(const QColor& color);

class GraphicsBase : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT
private:
	Point m_coordinates;
	QColor m_color;
	bool m_is_pillar;
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
public:
	GraphicsBase(const uint16_t size, const Point& coordinates, const QString& color, const bool& is_pillar, QGraphicsItem* parent = nullptr);
	const Point& getCoordinates() const noexcept;
	const QColor& getColor() const noexcept;
	const bool& isPillar() const noexcept;
	void setColor(const QString& color);
	void setIsPillar(const bool& is_pillar);
signals:
	void baseClicked(GraphicsBase* base);
signals:
	void baseHover(GraphicsBase* base);
};

