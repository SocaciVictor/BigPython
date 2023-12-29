//#include "Button.h"
//
//void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
//{
//    emit buttonClicked();
//    setPixmap(normalPixmap);
//}
//
//void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
//{
//    setPixmap(hoverPixmap);
//}
//
//void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
//{
//    setPixmap(normalPixmap);
//}
//
//Button::Button(const QString& path, const QPoint& pozitie, QGraphicsItem* parent) :
//    QGraphicsPixmapItem(QPixmap{ path + ".png" }, parent),
//    normalPixmap{ path + ".png" }, hoverPixmap{ path + "_hover.png" }
//{
//    setAcceptHoverEvents(true);
//    setTransformationMode(Qt::SmoothTransformation);
//    setAcceptedMouseButtons(Qt::LeftButton);
//    setCursor(Qt::PointingHandCursor);
//    setScale(0.5);
//    setPos(pozitie);
//}