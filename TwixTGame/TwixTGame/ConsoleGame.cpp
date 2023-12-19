#include "ConsoleGame.h"

void ConsoleGame::drawBoard(const Board& board)
{
	std::cout << "   ";
	for (int i = 0; i < board.getData().size(); i++) {
		std::cout << std::setw(3) << i;
	}
	std::cout << "\n";
	for (const auto& [y, row] : std::views::enumerate(board.getData()))
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
	bool valid_move{ true };
	uint16_t x, y;
	m_game.saveGame("save1.txt");
	do {
		std::system("cls");
		drawBoard(m_game.getBoard());
		if (!valid_move)
			std::cout << "Invalid moved!\n";
		drawPlayer(m_game.getCurrentPlayer());
		//for test{
		{
			std::unique_ptr<Move> nextMove;
			if (m_game.getCurrentPlayer()->getColor() == PieceColor::Red) {
				nextMove = m_game.m_aiRed->getNextMove();
			}
			else {
				nextMove = m_game.m_aiBlue->getNextMove();
			}
			MovePillar* ptr = dynamic_cast<MovePillar*>(nextMove.get());
			if (ptr)
				std::cout << ptr->pozition.x << " " << ptr->pozition.y << " " << (int)ptr->type << "\n";
		}
		std::cout << "add pillars on x y pozition: ";
		std::cin >> x >> y;
		valid_move = m_game.addPillar(Point{ x, y });
	} while (!valid_move);
	m_game.saveGame("save1.txt");
}

void ConsoleGame::playerBridgesMove()
{
	bool valid_move{ true };
	uint16_t x, y, a, b;
	do {
		std::system("cls");
		drawBoard(m_game.getBoard());
		if (!valid_move)
			std::cout << "Invalid moved!\n";
		drawPlayer(m_game.getCurrentPlayer());
		std::cout << "add Bridges or remove on x y, a b pozition or add 99 for next player: ";
		std::cin >> x;
		if (x == 99) break;
		std::cin >> y >> a >> b;

		//for test{
		{
			std::unique_ptr<Move> move = std::make_unique<MoveBridge>(Point{ x,y }, Point{ a,b }, MoveType::Add);
			std::cout << "\n"
				<< const_cast<Board&>(m_game.getBoard()).getHashWithMove(move.get()) << "\n";
			system("PAUSE");
		}
		
		valid_move = m_game.addBridge(Point{ x, y }, Point{ a,b });
		if (!valid_move)
			valid_move = m_game.removeBridges(Point{ x, y }, Point{ a,b });
		m_game.saveGame("save1.txt");
	} while (x != 99 && !m_game.finished());
}

void ConsoleGame::run()
{
	//m_game.loadGame("save1.txt");
	do {
		playerPillarMove();
		playerBridgesMove();
		m_game.nextPlayer();
	} while (!m_game.finished());
	std::system("cls");
	drawBoard(m_game.getBoard());
	if (m_game.getState() == State::Draw) {
		std::cout << "Jocul sa terminat cu remiza. \n";
	}else{
		std::cout << std::format("\n Player {}, a castigat! ",
			pieceColorToChar(m_game.getCurrentPlayer()->getColor()));
	}
}
