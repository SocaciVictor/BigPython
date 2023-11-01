#ifndef SQUAREWIDGET_H
#define SQUAREWIDGET_H

#include <QWidget>

class SquareWidget : public QWidget {
    Q_OBJECT
public:
    SquareWidget(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // SQUAREWIDGET_H

