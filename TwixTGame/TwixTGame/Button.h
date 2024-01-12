#pragma once
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QPixmap>
#include <QCursor>
#include <QDebug>


class Button : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    QString m_path;
    QPixmap m_normalPixmap;
    QPixmap m_hoverPixmap;
    QPixmap m_disablePixmap;
    bool m_enable{true};
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
public:
    Button() = default;
    Button(const QString& path,const QPoint& pozitie, QGraphicsItem* parent = nullptr);
    void setDisable();
    void setEnable();
    void setPath(const QString& path);
signals:
    void buttonClicked();
};

