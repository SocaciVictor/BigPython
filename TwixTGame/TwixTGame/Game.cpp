#include "Game.h"
#include "AiPlayer.h"
#include <random>
#include <chrono>

std::unique_ptr<AiPlayer> Game::m_aiPlayerRed = nullptr;
std::unique_ptr<AiPlayer> Game::m_aiPlayerBlue = nullptr;

Game::Game(const uint16_t& rows, const uint16_t& columns, const uint16_t& number_pillars, const uint16_t& number_bridges) :
	m_board{ rows,columns },
	m_player1{ std::make_unique<Player>(number_pillars,number_bridges,PieceColor::Blue) },
	m_player2{ std::make_unique<Player>(number_pillars,number_bridges,PieceColor::Red) },
	m_maxNumPillars{ number_pillars },
	m_maxNumBridges{ number_bridges },
	m_current_player{ m_player1.get() }
{}

const Board& Game::getBoard() const noexcept
{
	return m_board;
}

Board* Game::getBoardPtr()
{
	return &m_board;
}

uint16_t Game::getTurnNumber() const noexcept
{
	return m_turnNumber;
}

Player* Game::getCurrentPlayer() const noexcept
{
	return m_current_player;
}

void Game::setPlayerAi(uint16_t numar_player , std::string fileData)
{
	auto start = std::chrono::high_resolution_clock::now();
	if (numar_player == 1) {
		m_player1 = std::make_unique<AiPlayer>(m_player1->getNumberPillars(), m_player1->getNumberBridges(), PieceColor::Blue, fileData, &m_board);
		static_cast<AiPlayer*>(m_player1.get())->loadPolicy();
	}
	else {
		m_player2 = std::make_unique<AiPlayer>(m_player2->getNumberPillars(), m_player2->getNumberBridges(), PieceColor::Red, fileData, &m_board);
		static_cast<AiPlayer*>(m_player2.get())->loadPolicy();
	}
	
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Time spent loading files: " << duration << "\n";
	system("PAUSE");
}

Player* Game::getPlayer1() const noexcept
{
	return m_player1.get();
}

Player* Game::getPlayer2() const noexcept
{
	return m_player2.get();
}

//function assumes move is a valid move
//return true when a move is an end turn move, false otherwise
bool Game::addMove(Move* move)
{
	MovePillar* movePillar = dynamic_cast<MovePillar*>(move);
	MoveBridge* moveBridge = dynamic_cast<MoveBridge*>(move);
	//addPillar
	if (movePillar) {
		m_board.addPillar(movePillar->pozition, m_current_player->getColor(), false);//no checks for pillar
		m_current_player->updateNumberPillars(-1);
		m_current_player->setMoved(true);
	}
	//addBridge
	if (moveBridge) {
		switch (moveBridge->moveType) {
		case MoveType::Add:
			m_board.addBridge(moveBridge->startPozition, moveBridge->endPozition, m_current_player->getColor(), false);
			m_current_player->updateNumberBridges(-1);
			updateState(moveBridge->startPozition, moveBridge->endPozition);
			break;
		case MoveType::Delete:
			removeBridges(moveBridge->startPozition, moveBridge->endPozition);
			break;
		case MoveType::Next:
			return true;
			break;
		}
	}
	return false;
}

const State& Game::getState() const noexcept
{
	return m_state;
}

void Game::setState(State&& state)
{
	m_state = std::move(state);
}

bool Game::finished() const 
{
	if (m_state != State::None) return true;
	return false;
}

void Game::nextPlayer()
{
	if (finished()) return;
	m_current_player->setMoved(false);
	if (m_current_player == m_player1.get()) {
		m_current_player = m_player2.get();
	}
	else {
		m_current_player = m_player1.get();
	}
	updateState();
	m_turnNumber++;
}

//changes to other player without checking gameState and updating the state
//used for AiPlayer
void Game::switchPlayer()
{
	if (m_current_player == m_player1.get()) {
		m_current_player = m_player2.get();
	}
	else {
		m_current_player = m_player1.get();
	}
}

bool Game::addPillar(const Point& point)
{
	//verificare daca playerul a adaugat deja un pillar sa nu mai poata adauga;
	if (m_current_player->getMoved()) return false;
	//verific daca se creeaza pillarul;
	if(!m_board.addPillar(point,m_current_player->getColor())) return false;
	//playerului curent i se scade un pillar;
	m_current_player->updateNumberPillars(-1);
	//playerul este setat ca si cum a adaugat deja un pillar;
	m_current_player->setMoved(true);
	return true;
}

bool Game::addBridge(const Point& point1, const Point& point2)
{
	//verificare daca player a adaugat pilon;
	if (!m_current_player->getMoved()) return false;
	//verificare daca playerul curent mai are poduri;
	if (m_current_player->getNumberBridges() == 0) return false;
	//verific daca se creeaza podul;
	if(!m_board.addBridge(point1,point2,m_current_player->getColor())) return false;
	//playerului curent i se scade un bridge;
	m_current_player->updateNumberBridges(-1);
	updateState(point1, point2);
	return true;
}

bool Game::removePillar(const Point& point)
{
	PieceColor color = m_board.getBases()[point.y][point.x]->getColor();
	uint16_t removed_bridges = m_board.removePillar(point);
	if (!removed_bridges) return false;
	if ( color == m_player1->getColor()) {
		m_player1->updateNumberPillars(1);
		m_player1->updateNumberBridges(removed_bridges - 1);
	}
	else {
		m_player2->updateNumberPillars(1);
		m_player2->updateNumberBridges(removed_bridges - 1);
	}
	
	return true;
}

bool Game::removeBridges(const Point& point1, const Point& point2)
{
	//verificare daca player a adaugat pilon;
	if (!m_current_player->getMoved()) return false;
	//verificam daca se sterge podul;
	if (!m_board.removeBridge(point1, point2, m_current_player->getColor())) return false;
	//playerului curent i se adauga un bridge;
	m_current_player->updateNumberBridges(1);
	return true;
}

void Game::reset()
{
	m_board.reset();
	m_player1->reset(m_maxNumPillars, m_maxNumBridges);
	m_player2->reset(m_maxNumPillars, m_maxNumBridges);

	//default starting player
	m_current_player = m_player1.get();

	//if both players are ai starting player is random
	if (dynamic_cast<AiPlayer*>(m_player1.get()) && dynamic_cast<AiPlayer*>(m_player2.get())) {
		static std::random_device randomDevice;
		static std::mt19937 randomEngine = std::mt19937{ randomDevice() };
		std::bernoulli_distribution dis(0.5f);
		//50% chance that second player start
		if (dis(randomEngine))
			m_current_player = m_player2.get();
	}

	m_state = State::None;
}

void Game::updateState()
{
	if (m_player1->getNumberPillars() == 0 && m_player2->getNumberPillars() == 0) m_state = State::Draw;

	//check if the board is full with pillars
	for (const auto& line : m_board.getBases()) {
		for (const auto& base : line) {
			//ignore corners
			if (!base)
				continue;

			//check if base is a base not a pillar
			if (base->getColor() == PieceColor::None)
				return;
		}
	}
	m_state = State::Draw;
}

void Game::updateState(const Point& point1, const Point& point2)
{
	if(m_board.gameIsEnded(point1,point2,m_current_player->getColor())) m_state = State::Win;
}

void Game::swichColor()
{
	if (m_turnNumber != 1) return;
	std::swap(m_player1, m_player2);
	m_current_player = m_player1.get();
	m_turnNumber++;
}

bool Game::saveGame(const std::string& fisier)
{
	std::ofstream output_file{fisier};
	// Check if the file is successfully opened
	if (!output_file.is_open()) {
		std::cerr << "Unable to open the file." << std::endl;
		return false;
	}
	// Write to the file
	//Turn number;
	output_file << m_turnNumber << std::endl;
	// First line is the currentPlayer
	output_file << (m_current_player != m_player1.get());
	output_file << std::endl;
	//salvez cei 2 playeri
	output_file << *m_player1.get() << std::endl;
	output_file << *m_player2.get() << std::endl;
	//salvez bordul;
	output_file << m_board;
	// Close the file
	output_file.close();

	return true;
}

bool Game::loadGame(const std::string& fisier)
{
	std::ifstream input_file{ fisier };
	// Check if the file is successfully opened
	if (!input_file.is_open()) {
		std::cerr << "Unable to open the file." << std::endl;
		return false;
	}
	//read turn number;
	input_file >> m_turnNumber;
	//citirea pentru cei playeri
	char color;
	bool last_player, player_move;
	uint16_t number_pillars, number_bridges;
	input_file >> last_player;
	input_file >>color>> number_pillars >> number_bridges >> player_move;
	m_player1 = std::make_unique<Player>(number_pillars, number_bridges,charToPieceColor(color));
	m_player1->setMoved(player_move);
	input_file >> color >> number_pillars >> number_bridges >> player_move;
	m_player2 = std::make_unique<Player>(number_pillars, number_bridges, charToPieceColor(color));
	m_player2->setMoved(player_move);
	if (!last_player) m_current_player = m_player1.get();
	else m_current_player = m_player2.get();
	//citire board;
	input_file >> m_board;
	//inchidere fisier;
	//input_file.close();
	return true;
}

std::unique_ptr<Move> Game::getHint()
{
	if (m_aiPlayerRed.get() == nullptr) return nullptr;
	if (m_current_player->getColor() == PieceColor::Blue) {
		m_aiPlayerBlue->setMoved(m_current_player->getMoved());
		return m_aiPlayerBlue->getNextMove(false);
	}
	else {
		m_aiPlayerRed->setMoved(m_current_player->getMoved());
		return m_aiPlayerRed->getNextMove(false);
	}
	
}


