#pragma once
#include "ConsoleGame.h"
#include "BuldozeristGame.h"

class ConsoleBuldozeristGame : public ConsoleGame
{
public:
	ConsoleBuldozeristGame();
	void drawBoard(const Board& board) override;
	void run() override;
};

