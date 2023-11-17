#pragma once

#include "Piece.h"
#include <unordered_map>
#include <string>

class Hash {
public:
	std::size_t operator()(const QPoint& q) const
	{
		return std::hash<std::string>()(std::to_string(q.x()) + std::to_string(q.y()));
	}
};

class Player
{
private:
	static const uint16_t maxPillar = 50;
	static const uint16_t maxBridge = 50;
	
	std::string name;
	uint16_t pillarCount = 0;
	uint16_t bridgeCount = 0;
	QColor color;

	std::unordered_map<QPoint, Piece*, Hash> pieces;
public:
	Player() = default;
	Player(const std::string_view& name, QColor& playerColor);
	Player(const std::string_view& name, QColor&& playerColor);
	Player(Player& otherPlayer);
	~Player();

	void addPiece(QPoint& coord,Piece* piece);
	bool canPlace() const;
	QColor getColor() const;
};

