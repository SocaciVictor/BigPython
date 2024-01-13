#include "MineGame.h"

std::vector<Point> MineGame::allPossibleMinePos()
{
	std::vector<Point> possiblePositions;
	for (const auto& line : m_board.getBases())
		for (const auto& base : line)
			if (base)
				possiblePositions.push_back(base.get()->getCoordinates());
	return possiblePositions;
}

MineGame::MineGame(const uint16_t& rows, const uint16_t& columns, const uint16_t& number_pillars, const uint16_t& number_bridges) :
	Game{ rows,columns ,number_pillars ,number_bridges }
	
{
	generateMine(rows);
}

bool MineGame::addMine(const Point& point)
{
	return m_board.addMine(point);
}

void MineGame::generateMine(const uint16_t& size)
{
	int nrMine{(size*size-4)/10};

	std::mt19937 gen(m_random());


	std::vector<Point> pozitii_disponibile{ allPossibleMinePos() };

	std::shuffle(pozitii_disponibile.begin(), pozitii_disponibile.end(), gen);
	
	for (int i = 0;i < nrMine;i++)
	{
		addMine(pozitii_disponibile[i]);
	}
}

int MineGame::addPillar(const Point& point)
{
	if (m_board.getBases()[point.y][point.x]->getColor() == PieceColor::Mine)
	{
		if (!static_cast<Mine*>(m_board.getBases()[point.y][point.x].get())->getActive()) return false;
		static_cast<Mine*>(m_board.getBases()[point.y][point.x].get())->setActive(false);
		return true;
	}	
	if (!Game::addPillar(point)) return false;

	return true;
}
