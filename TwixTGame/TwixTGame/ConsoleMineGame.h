#pragma once
#include "ConsoleGame.h"
#include "MineGame.h"

class ConsoleMineGame : public ConsoleGame
{
public:
	ConsoleMineGame(const std::string& path);
	void drawBoard(const Board& board) override;
	void playerPillarMove() override;
	void playerMineMove();
	void run() override;
};

