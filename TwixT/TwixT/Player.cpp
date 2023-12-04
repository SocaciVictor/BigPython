#include "Player.h"

Player::Player(std::uint8_t number_pillars, std::uint8_t number_bridges, PieceColor color) :
	m_number_pillars{ number_pillars }, m_number_bridges{ number_bridges }, m_color{ color }, m_moved{ false }
{}

const PieceColor& Player::getColor() const noexcept
{
	return m_color;
}

const uint8_t Player::getNumberPillars() const noexcept
{
	return m_number_pillars;
}

const uint8_t Player::getNumberBridges() const noexcept
{
	return m_number_pillars;
}

const bool& Player::getMoved() const noexcept
{
	return m_moved;
}

void Player::setMoved(bool moved)
{
	m_moved = moved;
}
