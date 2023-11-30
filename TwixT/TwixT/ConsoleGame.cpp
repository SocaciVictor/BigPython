#include "ConsoleGame.h"

bool ConsoleGame::isInBoard(Point move)
{
	if (move.x < 0 || move.y < 0 || move.x >= 24 || move.y >= 24) return false;
	if ((move.x == 0 || move.x == 23) && (move.y == 0 || move.y == 23)) return false;
	return true;
}

void ConsoleGame::playerAddPillar()
{
	bool validMove{};
	std::uint16_t x, y;
	m_game.getCurrentPlayer()->setMoved(false);
	//clickul pentru a adauga pillar;
	do {
		std::cout << std::format("\n Player {}, click on base x y: ",
			pieceColorToChar(m_game.getCurrentPlayer()->getColor()));
		std::cin >> x >> y;
		validMove = isInBoard(Point{ x,y });
		if (!validMove) {
			std::cout << "Not a valid base!";
		}
		else {
			m_game.getBoard().getData()[y][x]->click();
		}
	} while (!validMove || !m_game.getCurrentPlayer()->getMoved());
}