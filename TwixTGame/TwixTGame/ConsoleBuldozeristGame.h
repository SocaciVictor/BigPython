#pragma once
#include "ConsoleGame.h"
#include "BuldozeristGame.h"

class ConsoleBuldozeristGame : public ConsoleGame
{
public:
	ConsoleBuldozeristGame(const std::string path);
	void drawBoard(const Board& board) override;
	void run() override;
};

