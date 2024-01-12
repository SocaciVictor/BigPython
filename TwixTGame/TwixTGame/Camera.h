#pragma once
#include<QGraphicsView>

class Camera : public QGraphicsView
{
public:
	Camera(int width, int height, QWidget* parent = nullptr);
};

