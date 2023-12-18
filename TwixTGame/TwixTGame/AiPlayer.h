#pragma once
#include "Player.h"
#include "Board.h"

class AiPlayer : public Player
{
private:
	std::string m_dataFile{ "" };
	Board& m_board;

	void loadPolicy();
	void savePolicy();
	std::vector<std::unique_ptr<Move>> generateMoveCollection();

public:
	AiPlayer(const std::uint16_t& number_pillars, const std::uint16_t& number_bridges, const PieceColor& color,
		const std::string& dataFile, Board& board);
	~AiPlayer();
};

