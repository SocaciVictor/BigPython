#include "TwixTGame.h"
#include <QApplication>
#include <QFontDatabase>

TwixTGame::TwixTGame()
{
	QApplication::setStyle("Plastique");
	QFontDatabase::addApplicationFont("../assets/Itim.ttf");//fontul pe care il folosesc
	m_camera.setScene(&m_mainMenu);
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
    m_camera.setScene(&m_gameScene);
    m_gameScene.newGame(24);
    m_mainMenu.back();
}

void TwixTGame::aiGame()
{
    Game::m_aiPlayerRed = std::make_unique<AiPlayer>(14, 14, PieceColor::Red, "RedData");
    Game::m_aiPlayerBlue = std::make_unique<AiPlayer>(14, 14, PieceColor::Blue, "BlueData");
    Game::m_aiPlayerRed->loadPolicy();
    Game::m_aiPlayerBlue->loadPolicy();
    m_camera.setScene(&m_gameScene);
    m_gameScene.newGame(6);
    m_mainMenu.back();
}

void TwixTGame::load()
{
    m_camera.setScene(&m_gameScene);
    m_gameScene.loadGame();
}

void TwixTGame::exit()
{
    m_camera.close();
}

void TwixTGame::backToMainMenu()
{
    m_camera.setScene(&m_mainMenu);
    m_mainMenu.update();
    m_gameScene.reset();
    Game::m_aiPlayerRed.reset();
    Game::m_aiPlayerBlue.reset();
}
