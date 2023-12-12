#include "Player.h"

Player::Player(const std::uint16_t& number_pillars, const std::uint16_t& number_bridges, const PieceColor& color) :
	m_number_pillars{ number_pillars }, m_number_bridges{ number_bridges }, m_color{ color }, m_moved{ false }
{}

const PieceColor& Player::getColor() const noexcept
{
	return m_color;
}

const uint16_t& Player::getNumberPillars() const noexcept
{
	return m_number_pillars;
}

const uint16_t& Player::getNumberBridges() const noexcept
{
	return m_number_bridges;
}

void Player::updateNumberPillars(const int16_t& addend)
{
	m_number_pillars += addend;
}

void Player::updateNumberBridges(const int16_t& addend)
{
	m_number_bridges += addend;
}

const bool& Player::getMoved() const noexcept
{
	return m_moved;
}

void Player::setMoved(const bool& moved)
{
	m_moved = moved;
}

std::ostream& operator<<(std::ostream& output, const Player& player)
{
	output << pieceColorToChar(player.getColor()) << " " << player.getNumberPillars() << " "
		<< player.getNumberBridges() << " " << player.getMoved();
	return output;
}