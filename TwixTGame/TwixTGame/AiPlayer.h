#pragma once
#include "Player.h"
#include "Board.h"
#include <limits>
#include <random>

class AiPlayer : public Player
{
private:
	std::string m_dataFile{ "" };
	Board& m_board;
	std::unordered_map<std::string, float> m_stateMoveCosts;
	std::vector<std::string> m_previousStateMoves;

	void loadPolicy();
	void savePolicy();
	std::vector<std::unique_ptr<Move>> generateMoveCollection();

	//used for getNextMove
	std::random_device randomDevice;
	std::mt19937 randomEngine = std::mt19937{ randomDevice()};
	const float initialEstimation = 0.5f;
	const float explorationRate = 0.1f;
	const float learningRate = 0.1f;

public:
	AiPlayer(const std::uint16_t& number_pillars, const std::uint16_t& number_bridges, const PieceColor& color,
		const std::string& dataFile, Board& board);
	~AiPlayer();
	std::unique_ptr<Move> getNextMove() override;
};

