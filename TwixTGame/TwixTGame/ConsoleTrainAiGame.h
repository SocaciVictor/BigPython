#pragma once
#include "Game.h"
#include <iomanip>
#include <ranges>
#include <fstream>
#include "AiPlayer.h"
#include "ConsoleGame.h"

class ConsoleTrainAiGame : public ConsoleGame
{
private:
	void drawAiMove(Move* move);
	void wipeAiFiles(std::string redFileData, std::string blueFileData);
public:
	ConsoleTrainAiGame(const uint16_t& size);
	void playerPillarMove();
	void playerBridgesMove();
	void run();
	void train(std::string redFileData, std::string blueFileData);
};

