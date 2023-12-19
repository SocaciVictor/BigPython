#pragma once
#include"Base.h"

enum class MoveType {
	Delete,
	Add,
	None
};

struct Move {
	PieceType type : 3; //4 types
	Move(PieceType type = PieceType::None) : type{ type } {}
	virtual ~Move() = default;
};
struct MovePillar : public Move{
	Point pozition;
	MovePillar(Point pozition, PieceType type = PieceType::None) : Move{ type }, pozition{ pozition } {}
};
struct MoveBridge : public Move {
	Point startPozition;
	Point endPozition;
	MoveType moveType : 2;
	MoveBridge(Point startPozition, Point endPozition,MoveType moveType = MoveType::None, PieceType type = PieceType::None)
		: Move{ type }, startPozition{ startPozition }, endPozition{ endPozition } {
		if (endPozition < startPozition)
			std::swap(endPozition, startPozition); //startPosition is always on top and to the left of endPosition
	}
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
	virtual std::unique_ptr<Move> getNextMove();
	const PieceColor& getColor() const noexcept;
	const uint16_t& getNumberPillars() const noexcept;
	const uint16_t& getNumberBridges() const noexcept;
	void updateNumberPillars(const int16_t& addend);
	void updateNumberBridges(const int16_t& addend);
	const bool& getMoved() const noexcept;
	void setMoved(const bool& moved);
	friend std::ostream& operator<<(std::ostream& output, const Player& player);
};

