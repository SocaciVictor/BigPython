#pragma once

#include "Piece.h"
#include <unordered_map>
#include <string>

template <>
struct std::hash<QPoint>
{
	std::size_t operator()(const QPoint& q) const
	{
		return hash<std::string>()(std::to_string(q.x()) + std::to_string(q.y()));
	}
};

class Player
{
private:
	static const uint16_t maxPillar = 50;
	static const uint16_t maxBridge = 50;
	
	std::string name;
	QColor playerColor;

	std::unordered_map<QPoint, Piece*> pieces;
public:
	Player(std::string& name, QColor& playerColor);
	Player(Player& otherPlayer);
	~Player();
};

