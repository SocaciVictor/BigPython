#pragma once
#include <QGraphicsScene>
#include<QGraphicsPixmapItem>
#include <QPixmap>
#include<array>
#include<memory>
#include "Button.h"

class MainMenu : public QGraphicsScene
{
private:
	QGraphicsPixmapItem m_fundal;
	std::array<std::unique_ptr<Button>, 4> m_buttons;
public:
	MainMenu(QObject* parent = nullptr);
	void populateScene();
};

