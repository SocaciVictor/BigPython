#pragma once
#include <QGraphicsRectItem>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include<array>
#include<memory>
#include "Button.h"

class SecondMenu : public QGraphicsRectItem
{
private:
	QGraphicsPixmapItem m_logo{ QPixmap{ "../assets/logo.png" }, this };
	std::array<std::unique_ptr<Button>, 4> m_buttons;
protected:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
public:
	SecondMenu(QGraphicsScene* parent = nullptr);
};

