#include "BuldozeristGame.h"

BuldozeristGame::BuldozeristGame(const uint16_t& rows, const uint16_t& columns, const uint16_t& number_pillars, const uint16_t& number_bridges) :
	Game{ rows,columns,number_pillars,number_bridges },
	m_buldozer{ Point{m_buldozer.generateRandomNumber(0,rows - 1),m_buldozer.generateRandomNumber(0,rows - 1)} }
{
	for (uint16_t i = 0; i < rows - 1; i++) {
		for (uint16_t j = 0; j < columns - 1; j++) {
			if ((j == 0 || j == columns - 1) && (i == 0 || i == rows - 1)) continue;
			m_buldozer.addBasesPoint(Point{ j,i });
		}
	}
}

const Point& BuldozeristGame::buldozerMove()
{
	if (finished()) return m_buldozer.getCoordinates();
	Point newPosition = m_buldozer.coinToss();
	m_buldozer.setCoordinates(newPosition);
	removePillar(newPosition);
	return newPosition;
}

const Point& BuldozeristGame::getBuldozerCoordinates()
{
	return m_buldozer.getCoordinates();
}

bool BuldozeristGame::addPillar(const Point& point)
{
	if (point == m_buldozer.getCoordinates()) return false;
	if (!Game::addPillar(point)) return false;
	if (m_current_player->getColor() == PieceColor::Blue) {
		m_buldozer.addBluePillarsPoint(point);
	}
	else {
		m_buldozer.addRedPillarsPoint(point);
	}
	return true;
}
