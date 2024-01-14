#include "Player.h"

Player::Player(const std::uint16_t& number_pillars, const std::uint16_t& number_bridges, const PieceColor& color) :
	m_numberPillars{ number_pillars }, m_numberBridges{ number_bridges }, m_color{ color }, m_moved{ false }
{}

//only used by AiPlayer
std::unique_ptr<Move> Player::getNextMove(bool randomMoves)
{
	if (randomMoves) {
		throw std::runtime_error("Cannot be used by Player");
	}

	return std::unique_ptr<Move>();
}

PieceColor Player::getColor() const noexcept
{
	return m_color;
}

void Player::setColor(const PieceColor& color)
{
	m_color = color;
}

uint16_t Player::getNumberPillars() const noexcept
{
	return m_numberPillars;
}

uint16_t Player::getNumberBridges() const noexcept
{
	return m_numberBridges;
}

void Player::updateNumberPillars(const int16_t& addend)
{
	m_numberPillars += addend;
}

void Player::updateNumberBridges(const int16_t& addend)
{
	m_numberBridges += addend;
}

bool Player::getMoved() const noexcept
{
	return m_moved;
}

void Player::setMoved(const bool& moved)
{
	m_moved = moved;
}

void Player::reset(uint16_t& maxNumPillars, uint16_t& maxNumBridge)
{
	m_numberPillars = maxNumPillars;
	m_numberBridges = maxNumBridge;
	m_moved = false;
}

//TODO make friend function getting acces to private members of player
std::ostream& operator<<(std::ostream& output, const Player& player)
{
	output << pieceColorToChar(player.getColor()) << " " << player.getNumberPillars() << " "
		<< player.getNumberBridges() << " " << player.getMoved();
	return output;
}
