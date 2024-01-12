#include "ConsoleBulzozeristGame.h"

ConsoleBulzozeristGame::ConsoleBulzozeristGame() 
{
	m_game = std::make_unique<BuldozeristGame>(24, 24, 50, 50);
}

void ConsoleBulzozeristGame::drawBoard(const Board& board)
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
			if (Point{ uint16_t(x),uint16_t(y) } == static_cast<BuldozeristGame*>(m_game.get())->getBuldozerCoordinates()) {
				std::cout << " D ";
				continue;
			}
			if (element == nullptr) {
				std::cout << "   ";
				continue;
			}
			if (element->getColor() != PieceColor::None) {
				std::cout << ' ' << pieceColorToChar(element->getColor()) << ' ';
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

void ConsoleBulzozeristGame::run()
{
	uint16_t player = 0;
	do {
		playerPillarMove();
		playerBridgesMove();
		player++;
		if (player % 2 == 0)
			static_cast<BuldozeristGame*>(m_game.get())->buldozerMove();
		m_game->nextPlayer();
	} while (!m_game->finished());
	std::system("cls");
	drawBoard(m_game->getBoard());
	if (m_game->getState() == State::Draw) {
		std::cout << "Jocul sa terminat cu remiza. \n";
	}
	else {
		std::cout << std::format("\n Player {}, a castigat! ",
			pieceColorToChar(m_game->getCurrentPlayer()->getColor()));
	}
}
