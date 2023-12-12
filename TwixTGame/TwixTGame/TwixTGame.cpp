#include "TwixTGame.h"

TwixTGame::TwixTGame()
{
	QApplication::setStyle("Plastique");
	QFontDatabase::addApplicationFont("../assets/Itim.ttf");//fontul pe care il folosesc
	m_camera.setScene(&m_main_menu);
}

void TwixTGame::run()
{
	m_camera.show();
}

void TwixTGame::switchScreen()
{}

void TwixTGame::backToMyMenu()
{}

void TwixTGame::play()
{
	m_game_scene->newGame();
	m_camera.setScene(m_game_scene.get());
}

void TwixTGame::exit()
{
	m_camera.close();
}

void TwixTGame::backToMainMenu()
{
	m_camera.setScene(&m_main_menu);
	m_main_menu.update();
	std::unique_ptr<GameScene> m_game_scene{ std::make_unique<GameScene>(this) };
}