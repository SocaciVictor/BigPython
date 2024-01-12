#pragma once
#include "Game.h"
#include <iomanip>
#include <ranges>

class ConsoleGame
{
protected:
	std::unique_ptr<Game> m_game;
public:
	ConsoleGame();
	virtual void drawBoard(const Board& board);
    void drawPlayer(const Player* player);
	void playerPillarMove();
    void playerBridgesMove();
    virtual void run();
};

