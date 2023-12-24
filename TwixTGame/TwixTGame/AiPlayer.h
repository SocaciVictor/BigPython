#pragma once
#include "Player.h"
#include "Board.h"
#include <random>

struct CharPtrEqual {
	bool operator()(const char* a, const char* b) const {
		return (std::strcmp(a, b) == 0);
	}
};
struct HashChar{
	//BKDR hash algorithm
	int operator()(char* str)const
	{
		int seed = 131;
		int hash = 0;
		while (*str)
		{
			hash = (hash * seed) + (*str);
			str++;
		}
		return hash & (0x7FFFFFFF);
	}
};

class AiPlayer : public Player
{
private:
	std::string m_dataFile;
	Board& m_board;
	std::unordered_map<char*, float, HashChar, CharPtrEqual> m_stateMoveCosts;
	std::vector<std::string> m_previousStateMoves;

	void generateMoveCollection(std::vector<std::unique_ptr<Move>>& moves);
	void alocateCharPtr(char*& dest, std::string& source);

	//used for getNextMove
	std::random_device randomDevice;
	std::mt19937 randomEngine = std::mt19937{ randomDevice()};
	const float initialEstimation = 0.5f;
	const float explorationRate = 0.3f;
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

