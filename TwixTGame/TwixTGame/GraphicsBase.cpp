#include "GraphicsBase.h"

QString pieceColorToColor(const PieceColor& piece_color)
{
	switch (piece_color) {
	case PieceColor::Blue: return "#4798CE";
	case PieceColor::Red: return "#E31021";
	case PieceColor::None: return "#000000";
	default: return "?";
	}
}

QString pieceColorToHoverColor(const PieceColor& piece_color)
{
	switch (piece_color) {
	case PieceColor::Blue: return "#38D3CA";
	case PieceColor::Red: return  "#F84C27";
	case PieceColor::None: return "#000000";
	default: return "?";
	}
}

PieceColor colorToPieceColor(const QColor& color)
{
	if (color == "#4798CE" || color == "#38D3CA")
		return PieceColor::Blue;
	if (color == "#E31021" || color == "#F84C27")
		return PieceColor::Red;
	return PieceColor::None;
}


void GraphicsBase::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	emit baseClicked(this);
}

void GraphicsBase::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	emit baseHover(this);
}

void GraphicsBase::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	setBrush(QColor(m_color));
	setOpacity(1.0);
	setCursor(Qt::ArrowCursor);
	if(!m_isPillar)
		setScale(1.0);
}

GraphicsBase::GraphicsBase(const uint16_t size, const Point& coordinates, const QString& color, const bool& is_pillar, QGraphicsItem* parent) :
	m_coordinates{ coordinates }, m_color{ color }, m_isPillar{ is_pillar }, QGraphicsEllipseItem{ parent }
{
	uint16_t margine_distance = 24 / size * 35;
	uint16_t base_size = (490 - margine_distance * 2) / (3 * size - 2);
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton);
	setRect(235 + margine_distance + coordinates.x * 3 * base_size, 25 + margine_distance + coordinates.y * 3 * base_size, base_size, base_size);
	setTransformOriginPoint(boundingRect().center());
	setBrush(m_color);
	setPen(Qt::NoPen);
	setZValue(2);
}

const Point& GraphicsBase::getCoordinates() const noexcept
{
	return m_coordinates;
}

const QColor& GraphicsBase::getColor() const noexcept
{
	return m_color;
}

bool GraphicsBase::isPillar() const noexcept
{
	return m_isPillar;
}

void GraphicsBase::setColor(const QString& color)
{
	m_color = color;
	setBrush(m_color);
}

void GraphicsBase::setIsPillar(const bool& is_pillar)
{
	m_isPillar = is_pillar;
}
