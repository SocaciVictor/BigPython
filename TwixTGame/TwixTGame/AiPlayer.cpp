#include "AiPlayer.h"

void AiPlayer::loadPolicy()
{
}

void AiPlayer::savePolicy()
{
}

std::vector<std::unique_ptr<Move>> AiPlayer::generateMoveCollection()
{
	//TODO: generate all the possible moves from the current board state
	return std::vector<std::unique_ptr<Move>>();
}

AiPlayer::AiPlayer(const std::uint16_t& number_pillars, const std::uint16_t& number_bridges, const PieceColor& color,
	const std::string& dataFile, Board& board)
	: Player{ number_pillars, number_bridges, color }, m_dataFile{ dataFile }, m_board{board}
{
	loadPolicy();
}

AiPlayer::~AiPlayer()
{
	savePolicy();
}
