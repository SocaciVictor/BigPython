#pragma once
#include "ConsoleGame.h"
#include "MineGame.h"

class ConsoleMineGame : public ConsoleGame
{
public:
	ConsoleMineGame();
	
	void drawBoard(const Board& board) override;
	void playerPillarMove() override;
};

