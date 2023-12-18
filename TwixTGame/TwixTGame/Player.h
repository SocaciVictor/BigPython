#pragma once
#include"Base.h"

struct Move {
	PieceType type : 2; //4 types
	Move(PieceType& type) : type{ type } {}
};
struct MovePillar : Move{
	Point pozition;
	MovePillar(PieceType& type, Point& pozition) : Move{ type }, pozition{ pozition } {}
};
struct MoveBridge : Move {
	Point startPozition;
	Point endPozition;
	MoveBridge(PieceType& type, Point& startPozition, Point& endPozition) : Move{ type }, startPozition{ startPozition }, endPozition{ endPozition } {}
};

class Player
{
protected:
	PieceColor m_color;
	std::uint16_t m_number_pillars;
	std::uint16_t m_number_bridges;
	bool m_moved;
public:
	Player(const std::uint16_t& number_pillars,const std::uint16_t& number_bridges,const PieceColor& color);
	virtual ~Player() = default;
	const PieceColor& getColor() const noexcept;
	const uint16_t& getNumberPillars() const noexcept;
	const uint16_t& getNumberBridges() const noexcept;
	void updateNumberPillars(const int16_t& addend);
	void updateNumberBridges(const int16_t& addend);
	const bool& getMoved() const noexcept;
	void setMoved(const bool& moved);
	friend std::ostream& operator<<(std::ostream& output, const Player& player);
};

