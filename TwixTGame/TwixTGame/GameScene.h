#pragma once
#include <QGraphicsScene>
#include<QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QPixmap>
#include <QMessageBox>
#include<array>
#include "Game.h"
#include"SecondMenu.h"
#include "GraphicsBase.h"
#include "GraphicsBridge.h"
#include "Button.h";


class GameScene : public QGraphicsScene
{
private:
    std::unique_ptr<Game> m_game;
    SecondMenu m_second_menu;
    QGraphicsPixmapItem m_board;
    QGraphicsPixmapItem m_hint1;
    QGraphicsPixmapItem m_hint2;
    std::array<std::unique_ptr<GraphicsBase>, 572> m_bases;
    std::unordered_map<TwoPoint, std::unique_ptr<GraphicsBridge>, TwoPointHash> m_bridges;
    GraphicsBase* save_pillar{nullptr};
    std::array<std::unique_ptr<Button>, 4> m_next;
    std::array<std::unique_ptr<QGraphicsPixmapItem>, 4> m_images;
    std::array<std::unique_ptr<QGraphicsTextItem>, 4> m_texts;
protected:
    void keyPressEvent(QKeyEvent* event) override;
public:
	GameScene(QObject* parent = nullptr);
    void reset();
    void addPillar(GraphicsBase* base);
    void addBridge(GraphicsBase* base);
    void newGame(const uint16_t& size);
    void endGame();
public slots:
    void nextPlayer();
    void switchColor();
    void getBaseClicked(GraphicsBase* base);
    void getBaseHover(GraphicsBase* base);
    void saveGame();
    void resetGame();
    void seeHint();
};

