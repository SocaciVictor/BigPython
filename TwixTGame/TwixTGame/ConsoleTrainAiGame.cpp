#include "ConsoleTrainAiGame.h"
#include <thread>
#include <chrono>
#include <fstream>

void ConsoleTrainAiGame::drawAiMove(Move* move)
{
	drawBoard(m_game->getBoard());
	drawPlayer(m_game->getCurrentPlayer());
	std::cout << "\nMoved ";
	MoveBridge* ptr = dynamic_cast<MoveBridge*>(move);

	//if move is end turn
	if (ptr != nullptr && ptr->moveType == MoveType::Next) {
		std::cout << "End Turn\n";
		system("PAUSE");
		system("CLS");
		return;
	}

	std::string text{ "" };
	switch (move->type) {
	case PieceType::BluePillar:
		text = "Blue Pillar";
		break;
	case PieceType::BlueBridge:
		text = "Blue Bridge";
		break;
	case PieceType::RedPillar:
		text = "Red Pillar";
		break;
	case PieceType::RedBridge:
		text = "Red Bridge";
		break;
	default:
		break;
	}
	std::cout << text << " ";
	move->print();
	system("PAUSE");
	system("CLS");
}

void ConsoleTrainAiGame::wipeAiFiles(std::string redFileData, std::string blueFileData)
{
	std::ofstream wipe(redFileData, std::ios::trunc);
	if (wipe.good())
		wipe.close();
	wipe.open(blueFileData, std::ios::trunc);
	if (wipe.good())
		wipe.close();
}
ConsoleTrainAiGame::ConsoleTrainAiGame(const uint16_t& size) : ConsoleGame{size}
{}
void ConsoleTrainAiGame::playerPillarMove()
{
	bool valid_move{ true };
	uint16_t x, y;
	m_game->saveGame("save1.txt");
	do {
		std::system("cls");
		drawBoard(m_game->getBoard());
		if (!valid_move)
			std::cout << "Invalid moved!\n";
		drawPlayer(m_game->getCurrentPlayer());
		std::cout << "add pillars on x y pozition: ";
		std::cin >> x >> y;
		valid_move = m_game->addPillar(Point{ x, y });
	} while (!valid_move);
	m_game->saveGame("save1.txt");
}

void ConsoleTrainAiGame::playerBridgesMove()
{
	bool valid_move{ true };
	uint16_t x, y, a, b;
	do {
		std::system("cls");
		drawBoard(m_game->getBoard());
		if (!valid_move)
			std::cout << "Invalid moved!\n";
		drawPlayer(m_game->getCurrentPlayer());
		std::cout << "add Bridges or remove on x y, a b pozition or add 99 for next player: ";
		std::cin >> x;
		if (x == 99) break;

		std::cin >> y >> a >> b;

		valid_move = m_game->addBridge(Point{ x, y }, Point{ a,b });
		if (!valid_move)
			valid_move = m_game->removeBridges(Point{ x, y }, Point{ a,b });
		m_game->saveGame("save1.txt");
	} while (x != 99 && !m_game->finished());
}

void ConsoleTrainAiGame::run()
{
	//if there are aiplayers load policy
	AiPlayer* p1 = dynamic_cast<AiPlayer*>(m_game->getCurrentPlayer());
	m_game->switchPlayer();
	AiPlayer* p2 = dynamic_cast<AiPlayer*>(m_game->getCurrentPlayer());
	m_game->switchPlayer();
	if (p1)
		p1->loadPolicy();
	if (p2)
		p2->loadPolicy();

	//m_game.loadGame("save1.txt");
	do {
		//moves by aiPlayer
		if (dynamic_cast<AiPlayer*>(m_game->getCurrentPlayer())) {
			std::unique_ptr<Move> move;
			bool isEndTurn;
			do {
				move = m_game->getCurrentPlayer()->getNextMove(false);//best action available
				//case for 0 possible moves, is considered a draw
				if (!move) {
					m_game->setState(State::Draw);
					break;
				}
				//std::cout << "Hash before applied move: " << const_cast<Board&>(m_game.getBoard()).getHashWithMove(move.get()) << "\n";
				//isEndTurn is true when a end turn move is made
				isEndTurn = m_game->addMove(move.get());
				drawAiMove(move.get());
			} while (!isEndTurn && !m_game->finished());
		}
		//moves by human player
		else {
			playerPillarMove();
			playerBridgesMove();
		}
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
	system("PAUSE");
	m_game.reset();

}

void ConsoleTrainAiGame::train(std::string redFileData, std::string blueFileData)
{
	m_game->setPlayerAi(redFileData, blueFileData);
	uint64_t count{ 0 };
	bool watchCount{ true };

	//meniu for training
	bool continueMeniu = true;
	int input;
	do {
		system("CLS");
		std::cout << "0. Train\n1. Wipe Training Data\n";
		std::cin >> input;
		switch (input) {
		case 0:
			continueMeniu = false;
			break;
		case 1:
			std::cout << "Are you sure?(y/n)?";
			char choise;
			std::cin >> choise;
			if (choise == 'y' || choise == 'Y') {
				wipeAiFiles(redFileData, blueFileData);
				std::cout << "Files wiped!\n";
				system("PAUSE");
				return;
			}
		default:
			break;
		}
	} while (continueMeniu);
	system("CLS");
	std::cout << "How many games to train? ";
	std::cin >> count;
	std::shared_ptr<uint64_t> gameCount{ std::make_shared<uint64_t>(0) };

	//start thread to watch gameCount
	std::thread watchThread{ [](std::shared_ptr<uint64_t> gameCount, uint64_t count, bool& watchCount)
		{
			using namespace std::chrono_literals;
			while (watchCount) {
				system("CLS");
				std::cout << "Games played: " << *gameCount << " / " << count << "\n";
				std::this_thread::sleep_for(0.5s);
			}
		}, gameCount, count, std::ref(watchCount)
	};

	bool isEndTurn;
	//start timer
	auto start = std::chrono::high_resolution_clock::now();
	std::unique_ptr<Move> move;
	while (count != *gameCount) {
		do {

			//current player move
			do {
				
				move = m_game->getCurrentPlayer()->getNextMove();
				//case for 0 possible moves, is considered a draw
				if (!move) {
					m_game->setState(State::Draw);
					break;
				}
				//isEndTurn is true when a end turn move is made
				isEndTurn = m_game->addMove(move.get());
				//drawAiMove(move.get());
			} while (!isEndTurn && !m_game->finished());

			//next
			//if player wins next player is not switching players
			m_game->nextPlayer();
		} while (!m_game->finished());

		//feed reward for each ai
		switch (m_game->getState()) {
		case State::Draw:
			static_cast<AiPlayer*>(m_game->getCurrentPlayer())->feedReward(0.1f);
			m_game->switchPlayer();
			static_cast<AiPlayer*>(m_game->getCurrentPlayer())->feedReward(0.1f);
			break;
		case State::Win:
			static_cast<AiPlayer*>(m_game->getCurrentPlayer())->feedReward(1.0f);
			m_game->switchPlayer();
			static_cast<AiPlayer*>(m_game->getCurrentPlayer())->feedReward(0.0f);
			break;
		}

		//reset
		m_game->reset();
		(*gameCount)++;
	}
	//end timer
	auto end = std::chrono::high_resolution_clock::now();

	//wait for watch thread to join
	watchCount = false;
	watchThread.join();

	//display stats
	std::cout << "Games trained: " << count << "\n";

	//dispay time
	std::chrono::duration<double> duration = end - start;
	std::cout << "Time spent training: " << duration << "\n";

	//display getStateSize()
	uint64_t stateSize = static_cast<AiPlayer*>(m_game->getCurrentPlayer())->getStateSize();
	m_game->switchPlayer();
	std::cout << "Maximum states != initialEstimation: "
		<< std::max(stateSize, static_cast<AiPlayer*>(m_game->getCurrentPlayer())->getStateSize()) << "\n";
	//set player to initial state
	m_game->switchPlayer();

	static_cast<AiPlayer*>(m_game->getCurrentPlayer())->savePolicy();
	m_game->switchPlayer();
	static_cast<AiPlayer*>(m_game->getCurrentPlayer())->savePolicy();
	system("PAUSE");
}