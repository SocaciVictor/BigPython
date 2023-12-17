#include "AiPlayer.h"

void AiPlayer::loadPolicy()
{
}

void AiPlayer::savePolicy()
{
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
