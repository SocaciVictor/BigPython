#include "squarewidget.h"
#include <QPainter>

SquareWidget::SquareWidget(QWidget* parent)
    : QWidget(parent) {
}

void SquareWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Setați culoarea pătratului
    painter.setBrush(Qt::blue);

    // Desenați un pătrat la coordonatele (50, 50) cu latura de 100 de unități
    QRect squareRect1(50, 50, 100, 100);
    QRect squareRect2(200, 200, 100, 100);
    painter.drawRect(50,50,100,100);
    painter.drawRect(200, 200, 100, 100);
}
