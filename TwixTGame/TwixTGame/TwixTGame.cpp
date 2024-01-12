#include "TwixTGame.h"
#include <QApplication>
#include <QFontDatabase>

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
{
    if (!m_camera.isFullScreen()) {
        QSize min = m_camera.size();
        m_camera.showFullScreen();
        QSize max = m_camera.size();
        m_camera.scale(qreal(max.height()) / qreal(min.height()), qreal(max.height()) / qreal(min.height()));
    }
    else {
        m_camera.showNormal();
        m_camera.resetTransform();
    }
    m_camera.update();
}

void TwixTGame::normalGame() 
{
    m_camera.setScene(&m_game_scene);
    m_game_scene.newGame(24);
    m_main_menu.back();
}

void TwixTGame::aiGame()
{
    m_camera.setScene(&m_game_scene);
    m_game_scene.newGame(8);
    m_main_menu.back();
}

void TwixTGame::load()
{
    std::cout << "load\n";
}

void TwixTGame::exit()
{
    m_camera.close();
}

void TwixTGame::backToMainMenu()
{
    m_camera.setScene(&m_main_menu);
    m_main_menu.update();
    m_game_scene.reset();
}
