#pragma once
#include "Game.h"
#include <iomanip>
#include <ranges>
#include <fstream>
#include "AiPlayer.h"

class ConsoleGame
{
private:
	std::unique_ptr<Game> m_game;

	void drawAiMove(Move* move);
	void wipeAiFiles(std::string redFileData, std::string blueFileData);
public:
	virtual void drawBoard(const Board& board);
	void drawPlayer(const Player* player);
	void playerPillarMove();
	void playerBridgesMove();
	virtual void run();
	void train(std::string redFileData, std::string blueFileData);
};

