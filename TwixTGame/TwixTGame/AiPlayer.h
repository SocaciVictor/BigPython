#pragma once
#include "Player.h"
#include "Board.h"
#include <random>

class AiPlayer : public Player
{
private:
	std::string m_dataFile;
	Board& m_board;
	std::unordered_map<std::string, float> m_stateMoveCosts;
	std::vector<std::string> m_previousStateMoves;

	
	std::vector<std::unique_ptr<Move>> generateMoveCollection();

	//used for getNextMove
	std::random_device randomDevice;
	std::mt19937 randomEngine = std::mt19937{ randomDevice()};
	const float initialEstimation = 0.5f;
	const float explorationRate = 0.1f;
	const float learningRate = 0.3f;

public:
	AiPlayer(const std::uint16_t& number_pillars, const std::uint16_t& number_bridges, const PieceColor& color,
		const std::string& dataFile, Board& board);
	~AiPlayer();
	std::unique_ptr<Move> getNextMove(bool randomMoves = true) override; //if false will give only best action availble no exploration
	void loadPolicy();
	void savePolicy();
	void feedReward(float target);
	uint64_t getStateSize() const noexcept; //return the count of values that are not equal to initialEstimation
};

