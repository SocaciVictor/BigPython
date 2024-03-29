#pragma once
#include <ranges>
#include "Game.h"
#include "Buldozer.h"

class BuldozeristGame : public Game
{
private:
	Buldozer m_buldozer;
public:
	BuldozeristGame() = default;
	BuldozeristGame(const uint16_t& rows, const uint16_t& columns, const uint16_t& number_pillars, const uint16_t& number_bridges);
	const Point& buldozerMove();
	const Point& getBuldozerCoordinates();
	bool addPillar(const Point& point) override;
	bool saveGame(const std::string& fisier)override;
	bool loadGame(const std::string& fisier)override;
};

