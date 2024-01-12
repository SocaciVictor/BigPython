#include "Camera.h"

Camera::Camera(int width, int height, QWidget* parent) : QGraphicsView{ parent }
{
	setWindowTitle("TwixT Game");
	setFixedSize(width, height);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setRenderHint(QPainter::Antialiasing, true);
}