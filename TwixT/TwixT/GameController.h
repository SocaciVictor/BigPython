#pragma once
#include "Player.h";

class GameController
{
public:
	static void switchPlayer(Player& p1, Player& p2, Player*& curentPlayer);
};

