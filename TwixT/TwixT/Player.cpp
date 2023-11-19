#include "Player.h"
#include "Pillar.h"

Player::Player(const std::string_view& name, QColor& playerColor) :name{ name }, color{playerColor}
{
}

Player::Player(const std::string_view& name, QColor&& playerColor):
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

void Player::addPiece(QPoint& coord, Piece* piece){
	Pillar* check = dynamic_cast<Pillar*>(piece);
	if (check != nullptr) {
		pillarCount++;
	}
	else {
		bridgeCount++;
	}
	pieces.insert(std::make_pair(coord, piece));
}

bool Player::canPlace() const
{
	return(pillarCount < maxPillar && bridgeCount < maxBridge);
}

QColor Player::getColor() const
{
	return color;
}

void Player::removePiece(const QPoint& point){
	pieces.erase(point);
}
