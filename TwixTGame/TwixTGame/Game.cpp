#include "Game.h"
#include "AiPlayer.h"

Game::Game(const uint16_t& rows, const uint16_t& columns, const uint16_t& number_pillars, const uint16_t& number_bridges) :
	m_board{ rows,columns },
	m_player1{ std::make_shared<Player>(Player{number_pillars,number_bridges,PieceColor::Blue}) },
	m_player2{ std::make_shared<Player>(Player{number_pillars,number_bridges,PieceColor::Red}) },
	m_current_player{ m_player1 }
{
	//for testing
	m_aiRed = std::make_unique<AiPlayer>(number_pillars, number_bridges, PieceColor::Red, "RedData", m_board);
	m_aiBlue = std::make_unique<AiPlayer>(number_pillars, number_bridges, PieceColor::Blue, "BlueData", m_board);
}

const Board& Game::getBoard() const noexcept
{
	return m_board;
}

Player* Game::getCurrentPlayer() const noexcept
{
	return m_current_player.get();
}

const State& Game::getState() const noexcept
{
	return m_state;
}

const bool& Game::finished() const 
{
	if (m_state != State::None) return true;
	return false;
}

void Game::nextPlayer()
{
	if (finished()) return;
	if (m_current_player == m_player1) {
		m_current_player = m_player2;
	}
	else {
		m_current_player = m_player1;
	}
	m_current_player->setMoved(false);
	updateState();
}

const bool& Game::addPillar(const Point& point)
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

const bool& Game::addBridge(const Point& point1, const Point& point2)
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

const bool& Game::removeBridges(const Point& point1, const Point& point2)
{
	//verificare daca player a adaugat pilon;
	if (!m_current_player->getMoved()) return false;
	//verificam daca se sterge podul;
	if (!m_board.removeBridge(point1, point2, m_current_player->getColor())) return false;
	//playerului curent i se adauga un bridge;
	m_current_player->updateNumberBridges(1);
	return true;
}

void Game::updateState()
{
	if (m_player1->getNumberPillars() == 0 && m_player2->getNumberPillars() == 0) m_state = State::Draw;
}

void Game::updateState(const Point& point1, const Point& point2)
{
	if(m_board.gameIsEnded(point1,point2,m_current_player->getColor())) m_state = State::Win;
}

const bool& Game::saveGame(const std::string& fisier)
{
	std::ofstream output_file{fisier};
	// Check if the file is successfully opened
	if (!output_file.is_open()) {
		std::cerr << "Unable to open the file." << std::endl;
		return false;
	}
	// Write to the file
	// First line is the currentPlayer
	if (m_current_player == m_player1)
		output_file << 0;
	else
		output_file << 1;
	output_file << std::endl;
	//salvez cei 2 playeri
	output_file << *m_player1.get() << std::endl;
	output_file << *m_player2.get() << std::endl;
	//salvez bordul;
	output_file << m_board;
	return true;
}

const bool& Game::loadGame(const std::string& fisier)
{
	std::ifstream input_file{ fisier };
	// Check if the file is successfully opened
	if (!input_file.is_open()) {
		std::cerr << "Unable to open the file." << std::endl;
		return false;
	}
	//citirea pentru cei playeri
	char color;
	bool last_player, player_move;
	uint16_t number_pillars, number_bridges;
	input_file >> last_player;
	input_file >> color >> number_pillars >> number_bridges >> player_move;
	m_player1 = std::make_shared<Player>(number_pillars, number_bridges, charToPieceColor(color));
	m_player1->setMoved(player_move);
	input_file >> color >> number_pillars >> number_bridges >> player_move;
	m_player2 = std::make_shared<Player>(number_pillars, number_bridges, charToPieceColor(color));
	m_player2->setMoved(player_move);
	if (!last_player) m_current_player = m_player1;
	else m_current_player = m_player2;
	//citire board;
	input_file >> m_board;
	//inchidere fisier;
	input_file.close();

	return true;
}

