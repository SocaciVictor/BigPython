#pragma once
#include "Game.h"
#include <iomanip>
#include <ranges>
#include<fstream>

class ConsoleGame
{
private:
	Game m_game{ 24,24,50,50, "RedData", "BlueData"};
public:
	void drawBoard(const Board& board);
	void drawPlayer(const Player* player);
	void playerPillarMove();
	void playerBridgesMove();
	void run();
	void train();
};

