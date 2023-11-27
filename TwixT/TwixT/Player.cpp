#include "Player.h"
#include "Pillar.h"
#include "Bridge.h"

QPoint Player::hashForBridge(const QPoint& start, const QPoint& end){
	QPoint rezult(start.x() * pow(10, (std::to_string(end.x()).length())) + end.x(),
		start.y() * pow(10, (std::to_string(end.y()).length())) + end.y());
	return rezult;
	
}

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

bool Player::operator==(Player other) const{
	return (name == other.name);
}

void Player::addPiece(QPoint& coord, Piece* piece){
	Pillar* check = dynamic_cast<Pillar*>(piece);
	if (check != nullptr) {
		pillarCount++;
	}
	pieces.insert(std::make_pair(coord, piece));
}

void Player::addPiece(const QPoint& start, const QPoint& end, Piece* piece){
	Bridge* check = dynamic_cast<Bridge*>(piece);
	if (check != nullptr) {
		bridgeCount++;
	}
	pieces.insert(std::make_pair(hashForBridge(start, end), piece));
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

bool Player::isContained(const QPoint& point) const
{
	return pieces.contains(point);
}
