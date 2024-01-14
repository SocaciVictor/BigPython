#include "ConsoleGame.h"

ConsoleGame::ConsoleGame(std::string path) : m_path{path}
{}

void ConsoleGame::drawBoard(const Board& board)
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

void ConsoleGame::drawPlayer(const Player* player)
{
	std::cout << std::format("\n Player {}, pillars {}, bridges {}, ",
		pieceColorToChar(player->getColor()), player->getNumberPillars(), player->getNumberBridges());
}

void ConsoleGame::playerPillarMove()
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
			m_game->saveGame(m_path);
			continue;
		} 
		std::cin >> y;
		valid_move = m_game->addPillar(Point{x,y});
	} while (!valid_move || x == 88);
}

void ConsoleGame::playerBridgesMove()
{
	if (m_game->getCurrentPlayer()->getNumberPillars() == 0) return;
	bool valid_move{ true };
	uint16_t x, y, a, b;
	do {
		std::system("cls");
		drawBoard(m_game->getBoard());
		if (!valid_move)
			std::cout << "Invalid moved!\n";
		drawPlayer(m_game->getCurrentPlayer());
		std::cout << "add Bridges or remove on x y, a b pozition or add 99 for next player or 88 for save game: ";
		std::cin >> x;
		if (x == 88) {
			m_game->saveGame(m_path);
			continue;
		}
		if (x == 99) break;
		std::cin >> y >> a >> b;
		valid_move = m_game->removeBridges(Point{ x, y }, Point{ a,b });
		if(!valid_move)
		valid_move = m_game->addBridge(Point{ x, y }, Point{ a,b });
		if (!valid_move)
			valid_move = m_game->removeBridges(Point{ x, y }, Point{ a,b });
	} while (x != 99 && !m_game->finished());
}

void ConsoleGame::run()
{
	uint16_t load = 0;
	std::cout << "Press 1 for a load game or whatever u want for a new game: ";
	std::cin >> load;
	if (load == 1)
		m_game->loadGame(m_path);
	else {
		uint16_t size;
		system("CLS");
		std::cout << "Introdu marimea tablei de joc: ";
		std::cin >> size;
		m_game = std::make_unique<Game>(size, size, size * 2 + 2, size * 2 + 2);
	}
	do {
		playerPillarMove();
		playerBridgesMove();
		m_game->nextPlayer();
	} while (!m_game->finished());
	std::system("cls");
	drawBoard(m_game->getBoard());
	if (m_game->getState() == State::Draw) {
		std::cout << "Jocul sa terminat cu remiza. \n";
	}else{
		std::cout << std::format("\n Player {}, a castigat! ",
			pieceColorToChar(m_game->getCurrentPlayer()->getColor()));
	}
}
