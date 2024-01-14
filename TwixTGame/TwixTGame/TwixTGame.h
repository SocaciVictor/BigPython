#pragma once
#include <QWidget>
#include "Camera.h"
#include "MainMenu.h"
#include "GameScene.h"

class TwixTGame : public QWidget
{
	Q_OBJECT
private:
	Camera m_camera{ 965,545 };
	MainMenu m_mainMenu{ this };
	GameScene m_gameScene{ this };
public:
	TwixTGame();
	void run();
public slots:
	void switchScreen();
	void normalGame();
	void aiGame();
	void load();
	void exit();
	void backToMainMenu();
};

