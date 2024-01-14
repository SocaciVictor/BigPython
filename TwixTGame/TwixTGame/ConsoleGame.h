#pragma once
#include "Game.h"
#include <iomanip>
#include <ranges>

class ConsoleGame
{
protected:
	std::unique_ptr<Game> m_game;
	std::string m_path;
public:
	ConsoleGame(std::string path);
	virtual void drawBoard(const Board& board);
    virtual void drawPlayer(const Player* player);
	virtual void playerPillarMove();
	virtual void playerBridgesMove();
    virtual void run();
};

