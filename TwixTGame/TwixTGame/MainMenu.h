#pragma once
#include <QGraphicsScene>
#include<QGraphicsPixmapItem>
#include <QPixmap>
#include<array>
#include<memory>
#include "Button.h"

class MainMenu : public QGraphicsScene
{
	Q_OBJECT
private:
	QGraphicsPixmapItem m_fundal;
	std::array<std::unique_ptr<Button>, 7> m_buttons;
public:
	MainMenu(QObject* parent = nullptr);
public slots:
	void play();
	void back();
};

