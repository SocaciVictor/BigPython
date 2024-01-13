#pragma once
#include<QGraphicsView>
#include <QDialog>

class Camera : public QGraphicsView
{
public:
	Camera(int width, int height, QWidget* parent = nullptr);
};

