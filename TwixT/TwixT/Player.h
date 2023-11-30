#pragma once
#include "Base.h"
class Player
{
protected:
	PieceColor m_color;
	std::uint8_t m_number_pillars;
	std::uint8_t m_number_bridges;
	bool m_moved;
public:
	void setMoved(bool moved);
	Player() = default;
	Player(std::uint8_t number_pillars, std::uint8_t number_bridges, PieceColor color);
	PieceColor getColor() const noexcept;
	const bool& getMoved() const noexcept;
};

