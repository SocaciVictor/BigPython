#pragma once
#include "Base.h"
class Player
{
protected:
	PieceColor m_color;
	std::uint16_t m_number_pillars;
	std::uint16_t m_number_bridges;
	bool m_moved;
public:
	void setMoved(bool moved);
	Player() = default;
	Player(std::uint16_t number_pillars, std::uint16_t number_bridges, PieceColor color);
	const PieceColor& getColor() const noexcept;
	const uint8_t getNumberPillars() const noexcept;
	const uint8_t getNumberBridges() const noexcept;
	void updateNumberPillars(int16_t addend);
	void updateNumberBridges(int16_t addend);
	const bool& getMoved() const noexcept;
};

