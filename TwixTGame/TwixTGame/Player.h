#pragma once
#include"Base.h"

class Player
{
protected:
	PieceColor m_color;
	std::uint16_t m_number_pillars;
	std::uint16_t m_number_bridges;
	bool m_moved;
public:
	Player(const std::uint16_t& number_pillars,const std::uint16_t& number_bridges,const PieceColor& color);
	const PieceColor& getColor() const noexcept;
	void setColor(const PieceColor& color);
	const uint16_t& getNumberPillars() const noexcept;
	const uint16_t& getNumberBridges() const noexcept;
	void updateNumberPillars(const int16_t& addend);
	void updateNumberBridges(const int16_t& addend);
	const bool& getMoved() const noexcept;
	void setMoved(const bool& moved);
	friend std::ostream& operator<<(std::ostream& output, const Player& player);
};

