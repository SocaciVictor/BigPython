#include "ConsoleMineGame.h"

ConsoleMineGame::ConsoleMineGame()
{
	m_game = std::make_unique<MineGame>(24, 24, 50, 50);
}

void ConsoleMineGame::drawBoard(const Board& board)
{
	std::cout << "   ";
	for (int i = 0; i < board.getBases().size(); i++) {
		std::cout << std::setw(3) << i;
	}
	std::cout << "\n";
	for (const auto& [y, row] : std::views::enumerate(board.getBases()))
	{
		std::cout << std::setw(2) << y << "  ";
		for (const auto& [x, element] : std::views::enumerate(row)) {
			if (element == nullptr) {
				std::cout << "   ";
				continue;
			}
			if (element->getColor() != PieceColor::None) {
				if (element->getColor() == PieceColor::Mine) {
					if (static_cast<Mine*>(element.get())->getActive())
						std::cout << ' ' << pieceColorToChar(element->getColor()) << ' ';
					else
						std::cout << ' - ';
				}
				else
				{
					std::cout << ' ' << pieceColorToChar(element->getColor()) << ' ';
				}
				
			}
			else {
				std::cout << " . ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	std::cout << "Bridges: ";
	for (const auto& bridge : board.getBridges()) {
		std::cout << pieceColorToChar(bridge.second.getColor()) << "("
			<< bridge.first.point1.x << " " << bridge.first.point1.y << ", "
			<< bridge.first.point2.x << " " << bridge.first.point2.y << "); ";
	}
	std::cout << std::endl;
}

void ConsoleMineGame::playerPillarMove()
{
	if (m_game->getCurrentPlayer()->getNumberPillars() == 0) return;
	if (m_game->getCurrentPlayer()->getMoved()) return;
	bool valid_move{ true };
	uint16_t x, y;
	do {
		std::system("cls");
		drawBoard(m_game->getBoard());
		if (!valid_move)
			std::cout << "Invalid moved!\n";
		drawPlayer(m_game->getCurrentPlayer());
		std::cout << "add pillars on x y pozition or press 88 for save game: ";
		std::cin >> x;
		if (x == 88) {
			m_game->saveGame("save1.txt");
			continue;
		}
		std::cin >> y;
		valid_move = m_game->addPillar(Point{ x,y });
	} while (!valid_move || x == 88);
}
