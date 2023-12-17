//#include "TwixTGame.h"
//
//TwixTGame::TwixTGame()
//{
//	QApplication::setStyle("Plastique");
//	QFontDatabase::addApplicationFont("../assets/Itim.ttf");//fontul pe care il folosesc
//	m_camera.setScene(&m_main_menu);
//}
//
//void TwixTGame::run()
//{
//	m_camera.show();
//}
//
//void TwixTGame::switchScreen()
//{
//	if (!m_camera.isFullScreen()) {
//		QSize min = m_camera.size();
//		m_camera.showFullScreen();
//		QSize max = m_camera.size();
//		m_camera.scale(qreal(max.height()) / qreal(min.height()), qreal(max.height()) / qreal(min.height()));
//	}
//	else {
//		m_camera.showNormal();
//		m_camera.resetTransform();
//	}
//	m_camera.update();
//}
//
//void TwixTGame::backToMyMenu()
//{}
//
//void TwixTGame::play()
//{
//	m_game_scene->newGame();
//	m_camera.setScene(m_game_scene.get());
//}
//
//void TwixTGame::exit()
//{
//	m_camera.close();
//}
//
//void TwixTGame::backToMainMenu()
//{
//	m_camera.setScene(&m_main_menu);
//	m_main_menu.update();
//	std::unique_ptr<GameScene> m_game_scene{ std::make_unique<GameScene>(this) };
//}