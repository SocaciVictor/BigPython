#pragma once
#include "Game.h"
class ConsoleGame
{
protected:
	Game m_game{};
	bool isInBoard(Point move);
public:
	void playerAddPillar();
	void playerAddBridge();
	void run();
};

