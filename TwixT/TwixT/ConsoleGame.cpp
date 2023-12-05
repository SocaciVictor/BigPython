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
	//clickul pentru a adauga pillar;
	do {
		std::cout << std::format("\n Player {}, pillars {}, click on base x y: ",
			pieceColorToChar(m_game.getCurrentPlayer()->getColor()),
			m_game.getCurrentPlayer()->getNumberPillars());
		std::cin >> x >> y;
		std::system("cls");
		std::cout << m_game.getBoard() << "\n";
		validMove = isInBoard(Point{ x,y });
		if (!validMove) {
			std::cout << "\nNot a valid base!\n";
		}
		else {
			m_game.getBoard().getData()[y][x]->click();
		}
	} while (!m_game.getCurrentPlayer()->getMoved());
}

void ConsoleGame::playerAddBridge()
{
	bool validMove{ false };
	std::uint16_t x, y;
	//clickul pentru a adauga bridge sau a trece la urmatorul player;
	do {
		std::cout << std::format("\n Player {}, bridges {}, click on pillar or prees 99 for next ",
			pieceColorToChar(m_game.getCurrentPlayer()->getColor()),m_game.getCurrentPlayer()->getNumberBridges());
		std::cin >> x;
		if (x == 99) break;
		std::cin >> y;
		std::system("cls");
		std::cout << m_game.getBoard() << "\n";
		validMove = isInBoard(Point{ x,y });
		if (!validMove) {
			std::cout << "\nNot a valid pillar!\n";
		}
		else {
			m_game.getBoard().getData()[y][x]->click();
		}
	} while (x != 99 && y != 99);
}

void ConsoleGame::run()
{
	do {
		std::system("cls");
		std::cout << m_game.getBoard() << "\n";
		playerAddPillar();
		std::system("cls");
		std::cout << m_game.getBoard() << "\n";
		playerAddBridge();
		if (!m_game.finished()) {
			m_game.nextPlayer();
		}
	} while (!m_game.finished());
	if (m_game.getState() == State::Draw) {
		std::cout << "Jocul sa terminat cu remiza. \n";
	}
	if (m_game.getState() == State::Win) {
		std::cout << std::format("\n Player {}, a castigat ! ",
			pieceColorToChar(m_game.getCurrentPlayer()->getColor()));
	}
}

