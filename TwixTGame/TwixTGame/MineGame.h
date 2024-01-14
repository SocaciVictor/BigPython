#pragma once
#include "Game.h"
#include "Mine.h"
#include <random>
#include <algorithm>

class MineGame : public Game
{
private:
	std::random_device m_random;
	std::vector<Point> allPossibleMinePos();
public:
	MineGame() = default;
	MineGame(const uint16_t& rows, const uint16_t& columns, const uint16_t& number_pillars, const uint16_t& number_bridges);
	bool addMine(const Point& point);
	void generateMine(const uint16_t& size);
	bool addPillar(const Point& point) override;
};

