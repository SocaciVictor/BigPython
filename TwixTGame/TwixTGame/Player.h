#pragma once
#include"Base.h"

enum class MoveType {
	Delete,
	Add,
	Next, //end turn
	None
};

struct Move {
	PieceType type : 3; //5 types
	Move(PieceType type = PieceType::None) : type{ type } {}
	virtual ~Move() = default;
	virtual void print() = 0;
};
struct MovePillar : public Move{
	Point pozition;
	MovePillar(Point pozition, PieceType type = PieceType::None) : Move{ type }, pozition{ pozition } {}
	void print() {
		std::cout << pozition << "\n";
	}
};
struct MoveBridge : public Move {
	Point startPozition;
	Point endPozition;
	MoveType moveType : 3;
	MoveBridge(Point startPozition, Point endPozition,MoveType moveType = MoveType::None, PieceType type = PieceType::None)
		: Move{ type }, startPozition{ startPozition }, endPozition{ endPozition }, moveType{ moveType } {
		if (endPozition < startPozition)
			std::swap(this->endPozition, this->startPozition); //startPosition is always on top and to the left of endPosition
	}
	void print() {
		std::cout << startPozition << " " << endPozition << " ";
		switch (moveType) {
		case MoveType::Add:
			std::cout << "Add";
			break;
		case MoveType::Delete:
			std::cout << "Delete";
			break;
		case MoveType::Next:
			std::cout << "End Turn";
			break;
		}
		std::cout << "\n";
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
	virtual std::unique_ptr<Move> getNextMove(bool randomMoves = true);
	const PieceColor& getColor() const noexcept;
	void setColor(PieceColor& color);
	const uint16_t& getNumberPillars() const noexcept;
	const uint16_t& getNumberBridges() const noexcept;
	void updateNumberPillars(const int16_t& addend);
	void updateNumberBridges(const int16_t& addend);
	bool getMoved() const noexcept;
	void setMoved(bool moved);
	void reset(uint16_t& maxNumPillars, uint16_t& maxNumBridge);
	friend std::ostream& operator<<(std::ostream& output, const Player& player);
};

	