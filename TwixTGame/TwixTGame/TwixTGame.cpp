#include "TwixTGame.h"

TwixTGame::TwixTGame()
{
	QApplication::setStyle("Plastique");
	QFontDatabase::addApplicationFont("../assets/Itim.ttf");//fontul pe care il folosesc
	m_camera.setScene(&m_main_menu);
}

void TwixTGame::run()
{
}

void TwixTGame::switchScreen()
{}

void TwixTGame::backToMyMenu()
{}

void TwixTGame::play()
{
}

void TwixTGame::exit()
{
}

void TwixTGame::backToMainMenu()
{}