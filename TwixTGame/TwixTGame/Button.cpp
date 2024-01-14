#include "Button.h"

void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!m_enable) return;
    setPixmap(m_normalPixmap);
    emit buttonClicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    if (!m_enable) return;
    setPixmap(m_hoverPixmap);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    if (!m_enable) return;
    setPixmap(m_normalPixmap);
}

Button::Button(const QString& path,const QPoint& pozitie, QGraphicsItem* parent) :
    QGraphicsPixmapItem(QPixmap{ path + ".png" }, parent),
    m_normalPixmap{ path + ".png" }, m_hoverPixmap{ path + "_hover.png" }, m_disablePixmap{ path + "_disable.png" }
{
    setAcceptHoverEvents(true);
    setTransformationMode(Qt::SmoothTransformation);
    setAcceptedMouseButtons(Qt::LeftButton);
    setCursor(Qt::PointingHandCursor);
    setScale(0.5);
    setPos(pozitie);
}

void Button::setDisable()
{
    m_enable = false;
    setCursor(Qt::ArrowCursor);
    setPixmap(m_disablePixmap);
}

void Button::setEnable()
{
    m_enable = true;
    setCursor(Qt::PointingHandCursor);
    setPixmap(m_normalPixmap);
}

void Button::setPath(const QString& path)
{
    m_normalPixmap = QPixmap{ path + ".png" };
    m_hoverPixmap = QPixmap{ path + "_hover.png" };
    m_disablePixmap = QPixmap{ path + "_disable.png" };
}
