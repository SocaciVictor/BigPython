#include "GameScene.h"
#include<QDebug>


void GameScene::keyPressEvent(QKeyEvent* event)
{
	if (m_game->finished()) return;
	if (event->key() == Qt::Key_Escape) {
		if (items().contains(&m_second_menu)) {
			removeItem(&m_second_menu);
		}
		else {
			addItem(&m_second_menu);
		}
		update();
	}
	QGraphicsScene::keyPressEvent(event);
}

GameScene::GameScene(QObject* parent) : QGraphicsScene{ 0,0,960,540,parent },
	m_second_menu{ this }
{
	setBackgroundBrush(QBrush("#efefef"));
	m_texts[0] = std::make_unique<QGraphicsTextItem>("Pillars: " + QString::number(50));
	m_texts[1] = std::make_unique<QGraphicsTextItem>("Bridges: " + QString::number(50));
	m_texts[2] = std::make_unique<QGraphicsTextItem>("Pillars: " + QString::number(50));
	m_texts[3] = std::make_unique<QGraphicsTextItem>("Bridges: " + QString::number(50));
}

void GameScene::newGame(const uint16_t& size)
{
	//game logic
	m_game = std::make_unique<Game>(size, size, size*2+2, size*2+2);
	//board
	m_board.setPixmap(QPixmap{ "../assets/board.png" });
	m_board.setTransformationMode(Qt::SmoothTransformation);
	m_board.setScale(0.5);
	m_board.setPos(235, 25);
	m_hint1.setPixmap(QPixmap{ "../assets/hint.png" });
	m_hint1.setTransformationMode(Qt::SmoothTransformation);
	m_hint1.setScale(0.5);
	m_hint1.setZValue(2);
	m_hint1.setVisible(false);
	m_hint2.setPixmap(QPixmap{ "../assets/hint.png" });
	m_hint2.setTransformationMode(Qt::SmoothTransformation);
	m_hint2.setScale(0.5);
	m_hint2.setZValue(2);
	m_hint2.setVisible(false);
	addItem(&m_board);
	addItem(&m_hint1);
	addItem(&m_hint2);
	uint16_t count = 0;
	for (uint16_t i = 0; i < m_game->getBoard().getRows(); i++) {
		for (uint16_t j = 0; j < m_game->getBoard().getColumns(); j++) {
			if (m_game->getBoard().getBases()[i][j] != nullptr) {
				m_bases[count] = std::make_unique<GraphicsBase>(size, Point(j, i), "#000000", false);
				QObject::connect(m_bases[count].get(), &GraphicsBase::baseClicked, this, &GameScene::getBaseClicked);
				QObject::connect(m_bases[count].get(), &GraphicsBase::baseHover, this, &GameScene::getBaseHover);
				addItem(m_bases[count].get());
				count++;
			}
		}
	}
	//next button and swich color button
	m_next[0] = std::make_unique<Button>("../assets/nextB", QPoint{ 50,420 });
	m_next[1] = std::make_unique<Button>("../assets/nextR", QPoint{ 760,420 });
	m_next[2] = std::make_unique<Button>("../assets/switch", QPoint{ 760,230 });
	m_next[3] = std::make_unique<Button>("../assets/bec", QPoint{ 16,480 });
	QObject::connect(m_next[0].get(), &Button::buttonClicked, this, &GameScene::nextPlayer);
	QObject::connect(m_next[1].get(), &Button::buttonClicked, this, &GameScene::nextPlayer);
	QObject::connect(m_next[2].get(), &Button::buttonClicked, this, &GameScene::switchColor);
	QObject::connect(m_next[3].get(), &Button::buttonClicked, this, &GameScene::seeHint);
	m_next[1]->setDisable();
	addItem(m_next[0].get());
	addItem(m_next[1].get());
	addItem(m_next[3].get());
	if (size != 6) {
		m_next[3]->setVisible(false);
	}
	//textul
	m_texts[0]->setPlainText("Pillars: " + QString::number(m_game->getPlayer1()->getNumberPillars()));
	m_texts[1]->setPlainText("Bridges: " + QString::number(m_game->getPlayer1()->getNumberBridges()));
	m_texts[2]->setPlainText("Pillars: " + QString::number(m_game->getPlayer2()->getNumberPillars()));
	m_texts[3]->setPlainText("Bridges: " + QString::number(m_game->getPlayer2()->getNumberBridges()));
	m_texts[0]->setPos(48, 110);
	m_texts[1]->setPos(40, 151);
	m_texts[0]->setDefaultTextColor(QColor("#4798CE"));
	m_texts[1]->setDefaultTextColor(QColor("#4798CE"));
	m_texts[2]->setDefaultTextColor(QColor("#E31021"));
	m_texts[3]->setDefaultTextColor(QColor("#E31021"));
	m_texts[2]->setPos(768, 110);
	m_texts[3]->setPos(760, 151);
	for (auto& text : m_texts) {
		addItem(text.get());
	}
	//Pixmap Images
	m_images[0] = std::make_unique<QGraphicsPixmapItem>(QPixmap{ "../assets/player1B" });
	m_images[1] = std::make_unique<QGraphicsPixmapItem>(QPixmap{ "../assets/player2R" });
	m_images[0]->setPos(20, 50);
	m_images[1]->setPos(740, 50);
	m_images[2] = std::make_unique<QGraphicsPixmapItem>(QPixmap{ "../assets/arrowB" });
	m_images[3] = std::make_unique<QGraphicsPixmapItem>(QPixmap{ "../assets/arrowR" });
	m_images[2]->setPos(100, 10);
	m_images[3]->setPos(820, 10);
	for (auto& player : m_images) {
		player->setTransformationMode(Qt::SmoothTransformation);
		player->setScale(0.5);
		addItem(player.get());
	}
	removeItem(m_images[3].get());
	if (Game::m_aiPlayer) {
		Game::m_aiPlayer->setBoard(m_game->getBoardPtr());
	}
}

//loadGame

void GameScene::loadGame()
{
	//game logic
	m_game = std::make_unique<Game>();
	m_game->loadGame("save1.txt");
	//board
	m_board.setPixmap(QPixmap{ "../assets/board.png" });
	m_board.setTransformationMode(Qt::SmoothTransformation);
	m_board.setScale(0.5);
	m_board.setPos(235, 25);
	m_hint1.setPixmap(QPixmap{ "../assets/hint.png" });
	m_hint1.setTransformationMode(Qt::SmoothTransformation);
	m_hint1.setScale(0.5);
	m_hint1.setZValue(2);
	m_hint1.setVisible(false);
	m_hint2.setPixmap(QPixmap{ "../assets/hint.png" });
	m_hint2.setTransformationMode(Qt::SmoothTransformation);
	m_hint2.setScale(0.5);
	m_hint2.setZValue(2);
	m_hint2.setVisible(false);
	addItem(&m_board);
	addItem(&m_hint1);
	addItem(&m_hint2);
	uint16_t count = 0;
	for (uint16_t i = 0; i < m_game->getBoard().getRows(); i++) {
		for (uint16_t j = 0; j < m_game->getBoard().getColumns(); j++) {
			if (m_game->getBoard().getBases()[i][j] != nullptr) {
				m_bases[count] = std::make_unique<GraphicsBase>(m_game->getBoard().getRows(), Point(j, i),
					pieceColorToColor(m_game->getBoard().getBases()[i][j]->getColor()), m_game->getBoard().getBases()[i][j]->getColor() != PieceColor::None);
				QObject::connect(m_bases[count].get(), &GraphicsBase::baseClicked, this, &GameScene::getBaseClicked);
				QObject::connect(m_bases[count].get(), &GraphicsBase::baseHover, this, &GameScene::getBaseHover);
				addItem(m_bases[count].get());
				if (m_game->getBoard().getBases()[i][j]->getColor() != PieceColor::None)
					m_bases[count]->setScale(1.2);
				count++;
			}
		}
	}
	//adaugare pillars;
	for (auto& bridge : m_game->getBoard().getBridges()) {
		m_bridges.emplace(TwoPoint{ bridge.second.getStartPoint(),bridge.second.getEndPoint() },
			std::make_unique<GraphicsBridge>(m_game->getBoard().getRows(), bridge.second.getStartPoint(), bridge.second.getEndPoint(),
				pieceColorToColor(bridge.second.getColor())));
		addItem(m_bridges[TwoPoint{ bridge.second.getStartPoint(),bridge.second.getEndPoint() }].get());
	}
	
	//next button and swich color button
	m_next[0] = std::make_unique<Button>("../assets/nextB", QPoint{ 50,420 });
	m_next[1] = std::make_unique<Button>("../assets/nextR", QPoint{ 760,420 });
	m_next[2] = std::make_unique<Button>("../assets/switch", QPoint{ 760,230 });
	m_next[3] = std::make_unique<Button>("../assets/bec", QPoint{ 16,480 });
	QObject::connect(m_next[0].get(), &Button::buttonClicked, this, &GameScene::nextPlayer);
	QObject::connect(m_next[1].get(), &Button::buttonClicked, this, &GameScene::nextPlayer);
	QObject::connect(m_next[2].get(), &Button::buttonClicked, this, &GameScene::switchColor);
	QObject::connect(m_next[3].get(), &Button::buttonClicked, this, &GameScene::seeHint);
	addItem(m_next[0].get());
	addItem(m_next[1].get());
	addItem(m_next[3].get());
	if (m_game->getBoard().getRows() != 6) {
		m_next[3]->setVisible(false);
	}
	//textul
	m_texts[0]->setPlainText("Pillars: " + QString::number(m_game->getPlayer1()->getNumberPillars()));
	m_texts[1]->setPlainText("Bridges: " + QString::number(m_game->getPlayer1()->getNumberBridges()));
	m_texts[2]->setPlainText("Pillars: " + QString::number(m_game->getPlayer2()->getNumberPillars()));
	m_texts[3]->setPlainText("Bridges: " + QString::number(m_game->getPlayer2()->getNumberBridges()));
	m_texts[0]->setPos(48, 110);
	m_texts[1]->setPos(40, 151);
	m_texts[0]->setDefaultTextColor(QColor("#4798CE"));
	m_texts[1]->setDefaultTextColor(QColor("#4798CE"));
	m_texts[2]->setDefaultTextColor(QColor("#E31021"));
	m_texts[3]->setDefaultTextColor(QColor("#E31021"));
	m_texts[2]->setPos(768, 110);
	m_texts[3]->setPos(760, 151);
	for (auto& text : m_texts) {
		addItem(text.get());
	}
	//Pixmap Images
	m_images[0] = std::make_unique<QGraphicsPixmapItem>(QPixmap{ "../assets/player1B" });
	m_images[1] = std::make_unique<QGraphicsPixmapItem>(QPixmap{ "../assets/player2R" });
	m_images[0]->setPos(20, 50);
	m_images[1]->setPos(740, 50);
	m_images[2] = std::make_unique<QGraphicsPixmapItem>(QPixmap{ "../assets/arrowB" });
	m_images[3] = std::make_unique<QGraphicsPixmapItem>(QPixmap{ "../assets/arrowR" });
	m_images[2]->setPos(100, 10);
	m_images[3]->setPos(820, 10);

	for (auto& player : m_images) {
		player->setTransformationMode(Qt::SmoothTransformation);
		player->setScale(0.5);
		addItem(player.get());
	}

	if (m_game->getCurrentPlayer() == m_game->getPlayer1()) {
		m_next[1]->setDisable();
		removeItem(m_images[3].get());
	}
	else {
		m_next[0]->setDisable();
		removeItem(m_images[2].get());
	}
	if (m_game->getBoard().getRows() == 6) {
		Game::m_aiPlayer = std::make_unique<AiPlayer>(14, 14, PieceColor::None, "aiData");
		Game::m_aiPlayer->loadPolicy();
		Game::m_aiPlayer->setBoard(m_game->getBoardPtr());
	}
}

void GameScene::reset()
{
	m_second_menu.setNormal();
	removeItem(&m_second_menu);
	for (QGraphicsItem* item : items()) {
		removeItem(item);
	}
}

void GameScene::nextPlayer()
{
	if (!m_game->getCurrentPlayer()->getMoved()) return;
	if (save_pillar != nullptr) {
		save_pillar->setColor(pieceColorToColor(m_game->getCurrentPlayer()->getColor()));
		save_pillar = nullptr;
	}
	m_game->nextPlayer();
	m_next[m_game->getTurnNumber() % 2]->setEnable();
	m_next[(m_game->getTurnNumber() + 1) % 2]->setDisable();
	addItem(m_images[(m_game->getTurnNumber()) % 2 + 2].get());
	removeItem(m_images[(m_game->getTurnNumber() + 1) % 2 + 2].get());
	if(m_game->getTurnNumber() == 1) 
		addItem(m_next[2].get());
	m_hint1.setVisible(false);
	m_hint2.setVisible(false);
}

void GameScene::switchColor()
{
	m_game->swichColor();
	m_next[0]->setPath("../assets/nextR");
	m_next[1]->setPath("../assets/nextB");
	m_next[0]->setEnable();
	m_next[1]->setDisable();
	m_texts[0]->setDefaultTextColor(QColor("#E31021"));
	m_texts[1]->setDefaultTextColor(QColor("#E31021"));
	m_texts[2]->setDefaultTextColor(QColor("#4798CE"));
	m_texts[3]->setDefaultTextColor(QColor("#4798CE"));
	m_texts[0]->setPlainText("Pillars: " + QString::number(m_game->getPlayer1()->getNumberPillars()));
	m_texts[1]->setPlainText("Bridges: " + QString::number(m_game->getPlayer1()->getNumberBridges()));
	m_texts[2]->setPlainText("Pillars: " + QString::number(m_game->getPlayer2()->getNumberPillars()));
	m_texts[3]->setPlainText("Bridges: " + QString::number(m_game->getPlayer2()->getNumberBridges()));
	m_images[0]->setPixmap(QPixmap{ "../assets/player1R" });
	m_images[1]->setPixmap(QPixmap{ "../assets/player2B" });
	m_images[2]->setPixmap(QPixmap{ "../assets/arrowR" });
	m_images[3]->setPixmap(QPixmap{ "../assets/arrowB" });
	removeItem(m_images[3].get());
	addItem(m_images[2].get());
	removeItem(m_next[2].get());
	m_hint1.setVisible(false);
}

void GameScene::addPillar(GraphicsBase* base)
{
	if (!m_game->addPillar(base->getCoordinates())) return;
	base->setBrush(QColor(pieceColorToColor(m_game->getCurrentPlayer()->getColor())));
	base->setOpacity(1.0);
	base->setScale(1.2);
	base->setColor(pieceColorToColor(m_game->getCurrentPlayer()->getColor()));
	base->setIsPillar(true);
	m_texts[0]->setPlainText("Pillars: " + QString::number(m_game->getPlayer1()->getNumberPillars()));
	m_texts[2]->setPlainText("Pillars: " + QString::number(m_game->getPlayer2()->getNumberPillars()));
	if (m_game->getTurnNumber() == 1)
		removeItem(m_next[2].get());
	m_hint1.setVisible(false);
}

void GameScene::addBridge(GraphicsBase* base)
{
	//verific daca playeryl a apasat deja;
	if (!m_game->getCurrentPlayer()->getMoved()) return;
	//verificare daca pillarul apesat este de aceiasi culoare;
	if (colorToPieceColor(base->getColor()) != m_game->getCurrentPlayer()->getColor()) return;
	//crearea bridgeului;
	if (save_pillar == nullptr) {
		save_pillar = base;
		base->setColor(pieceColorToHoverColor(m_game->getCurrentPlayer()->getColor()));
		return;
	}
	if (save_pillar == base) {
		base->setColor(pieceColorToColor(m_game->getCurrentPlayer()->getColor()));
		save_pillar = nullptr;
		return;
	}
	if (!m_game->addBridge(save_pillar->getCoordinates(), base->getCoordinates())) return;
	m_bridges.emplace(TwoPoint{save_pillar->getCoordinates(),base->getCoordinates()},
		std::make_unique<GraphicsBridge>(m_game->getBoard().getRows(), save_pillar->getCoordinates(), base->getCoordinates(),
				pieceColorToColor(m_game->getCurrentPlayer()->getColor())));
	addItem(m_bridges[TwoPoint{ save_pillar->getCoordinates(),base->getCoordinates() }].get());
	save_pillar->setColor(pieceColorToColor(m_game->getCurrentPlayer()->getColor()));
	save_pillar = nullptr;
	m_hint1.setVisible(false);
	m_hint2.setVisible(false);
	m_texts[1]->setPlainText("Bridges: " + QString::number(m_game->getPlayer1()->getNumberBridges()));
	m_texts[3]->setPlainText("Bridges: " + QString::number(m_game->getPlayer2()->getNumberBridges()));
	endGame();
}

void GameScene::endGame()
{
	if (m_game->finished()) {
		QString path = "../assets/win";
		m_second_menu.setEnd();
		m_second_menu.setWinner("../assets/win1b.png");
	    addItem(&m_second_menu);
	}
}

void GameScene::getBaseClicked(GraphicsBase* base)
{
	if (!base->isPillar()) {
		addPillar(base);
	}
	else {
		addBridge(base);
	}
}

void GameScene::getBaseHover(GraphicsBase* base)
{
	if (items().contains(&m_second_menu)) return;
	if (m_game->getCurrentPlayer()->getColor() == PieceColor::Blue &&
		(base->getCoordinates().x == 0 || base->getCoordinates().x == m_game->getBoard().getColumns() - 1)) return;
	if (m_game->getCurrentPlayer()->getColor() == PieceColor::Red &&
		(base->getCoordinates().y == 0 || base->getCoordinates().y == m_game->getBoard().getRows() - 1)) return;
	if (!base->isPillar()) {
		if (m_game->getCurrentPlayer()->getMoved()) return;
		base->setBrush(QColor(pieceColorToColor(m_game->getCurrentPlayer()->getColor())));
		base->setCursor(Qt::PointingHandCursor);
		base->setOpacity(0.8);
		base->setScale(1.2);
	}
	else {
		if (!m_game->getCurrentPlayer()->getMoved()) return;
		if (colorToPieceColor(base->getColor()) != m_game->getCurrentPlayer()->getColor()) return;
		base->setCursor(Qt::PointingHandCursor);
		base->setBrush(QColor(pieceColorToHoverColor(m_game->getCurrentPlayer()->getColor())));
	}
}

void GameScene::saveGame()
{
	m_game->saveGame("save1.txt");
}

void GameScene::resetGame()
{
	uint16_t size = m_game->getBoard().getColumns();
	reset();
	newGame(size);
}

void GameScene::seeHint()
{
	std::unique_ptr<Move> move = m_game->getHint();
	if (!move) return;
	//verificam daca este de tipul Move Pillar;
	MoveBridge* moveBridge = dynamic_cast<MoveBridge*>(move.get());
	if (moveBridge) {
		if (moveBridge->moveType == MoveType::Next) {
			if (m_game->getCurrentPlayer() == m_game->getPlayer1()) {
				m_hint1.setPos(110, 390);
			}
			else {
				m_hint1.setPos(825, 390);
			}
			m_hint1.setVisible(true);
		}
		else {
			uint16_t margine_distance = 24 / m_game->getBoard().getRows() * 35;
			uint16_t base_size = (490 - margine_distance * 2) / (3 * m_game->getBoard().getRows() - 2);
			m_hint1.setPos(235 + margine_distance + moveBridge->startPozition.x * 3 * base_size - base_size / 2, 25 + margine_distance + moveBridge->startPozition.y * 3 * base_size - base_size * 2 - 3);
			m_hint2.setPos(235 + margine_distance + moveBridge->endPozition.x * 3 * base_size - base_size / 2, 25 + margine_distance + moveBridge->endPozition.y * 3 * base_size - base_size * 2 - 3);
			m_hint1.setVisible(true);
			m_hint2.setVisible(true);
		}
	}
	else {
		MovePillar* movePillar = dynamic_cast<MovePillar*>(move.get());
		uint16_t margine_distance = 24 / m_game->getBoard().getRows() * 35;
		uint16_t base_size = (490 - margine_distance * 2) / (3 * m_game->getBoard().getRows() - 2);
		m_hint1.setPos(235 + margine_distance + movePillar->pozition.x * 3 * base_size - base_size/2, 25 + margine_distance + movePillar->pozition.y * 3 * base_size - base_size*2 - 3);
		m_hint1.setVisible(true);
	}
}





