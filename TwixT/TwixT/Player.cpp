#include "Player.h"

Player::Player(std::string name, QColor& playerColor) :name{ name }, color{playerColor}
{
}

Player::Player(std::string name, QColor&& playerColor):
	name{ name }, color{playerColor}
{
}

Player::Player(Player& otherPlayer)
{
	name = otherPlayer.name;
	color = otherPlayer.color;
	for (auto& it : otherPlayer.pieces) {
		//to finish
		//pieces[it.first] = new Pie
	}
}

Player::~Player(){
	for (auto& it : pieces)
		delete it.second;
}
