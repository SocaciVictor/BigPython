#pragma once
#include "Game.h"
#include <iomanip>
#include <ranges>
#include <fstream>
#include "AiPlayer.h"

class ConsoleGame
{
private:
	Game m_game{ 5,5,50,50};

	void drawAiMove(Move* move);
	void wipeAiFiles(std::string redFileData, std::string blueFileData);
public:
	void drawBoard(const Board& board);
	void drawPlayer(const Player* player);
	void playerPillarMove();
	void playerBridgesMove();
	void run();
	void train(std::string redFileData, std::string blueFileData);
};

