#pragma once
#include "ConsoleGame.h"
#include "BuldozeristGame.h"

class ConsoleBulzozeristGame : public ConsoleGame
{
public:
	ConsoleBulzozeristGame();
	void drawBoard(const Board& board) override;
	void run() override;
};

