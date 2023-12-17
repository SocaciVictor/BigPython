//#pragma once
//#include <QGraphicsPixmapItem>
//#include <QMouseEvent>
//#include <QPixmap>
//#include <QCursor>
//#include <QDebug>
//
//
//class Button : public QObject, public QGraphicsPixmapItem {
//    Q_OBJECT
//private:
//    QPixmap normalPixmap;
//    QPixmap hoverPixmap;
//protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
//    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
//public:
//    Button() = default;
//    Button(const QString& path, const QPoint& pozitie, QGraphicsItem* parent = nullptr);
//signals:
//    void buttonClicked();
//};