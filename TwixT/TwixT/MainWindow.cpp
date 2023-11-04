#include "MainWindow.h"
#include <QPainter>

MainWindow::MainWindow(int width, int height, QString color, QWidget* parent)
{
	this->resize(width, height);
    this->setFixedSize(this->size());
    QPalette palette;
    QColor backgroundColor(color);
    palette.setColor(QPalette::Window, backgroundColor);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{}

void MainWindow::paintEvent(QPaintEvent*)
{
    //Desenat Dreptunghiuri
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(QColor("#DD125C"));
    painter.drawRect(200, 200, 100, 100);
    painter.setBrush(QColor("#12DDD1"));
    painter.drawRect(50, 50, 100, 100);
}
