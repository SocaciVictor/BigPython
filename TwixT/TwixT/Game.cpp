#include "Game.h"
#include <queue>
#include <array>

void Game::updateState(Pillar* pillar1, Pillar* pillar2)
{
	//Algoritmul Dijkstra
	//creare comparator pentru prioritate in functie de culoarea playerului;
	auto comparator = [this](const Point& p1, const Point& p2) {
		if (getCurrentPlayer()->getColor() == PieceColor::Red) {
			return std::min(abs(p1.y - getBoard().getRows() - 1), abs(p1.y - 0)) >
				std::min(abs(p2.y - getBoard().getRows() - 1), abs(p2.y - 0));
		}
		if (getCurrentPlayer()->getColor() == PieceColor::Black) {
			return std::min(abs(p1.x - getBoard().getColumns() - 1), abs(p1.x - 0)) >
				std::min(abs(p2.x - getBoard().getColumns() - 1), abs(p2.x - 0));
		}
	};
	//initializare coada de prioritate;
	std::priority_queue<Point, std::vector<Point>, decltype(comparator)> pqueue(comparator);
	//initializare matrice de locuri vizitate;
	std::vector<std::vector<bool>> matrice_vizitate;
	matrice_vizitate.resize(m_board.getRows());
	for (auto& rows : matrice_vizitate)
		rows.resize(m_board.getColumns());
	//initiaizare a 2 tipuri bool care vor retine daca se ajunge la una dintre baze;
	bool base1{ false }, base2{ false };
	//incepere algoritm 
	pqueue.push(pillar1->getCoordinates());
	pqueue.push(pillar2->getCoordinates());
	matrice_vizitate[pillar1->getCoordinates().y][pillar1->getCoordinates().x] = true;
	matrice_vizitate[pillar2->getCoordinates().y][pillar2->getCoordinates().x] = true;
	while (pqueue.size() != 0) {
		Point loc_current = pqueue.top();
		if ((loc_current.y == 0 && m_current_player->getColor() == PieceColor::Red) ||
			(loc_current.x == 0 && m_current_player->getColor() == PieceColor::Black))
			base1 = true;
		if ((loc_current.y == m_board.getRows() - 1 && m_current_player->getColor() == PieceColor::Red) ||
			(loc_current.x == m_board.getColumns() - 1 && m_current_player->getColor() == PieceColor::Black))
			base2 = true;
	}

	
}

void Game::updateState()
{
	if (m_player1->getNumberPillars() == 0 && m_player2->getNumberPillars() == 0) m_state = State::Draw;
}

Game::Game() :
	m_board{ 24,24,this },
	m_player1{ std::make_shared<Player>(Player{50,50,PieceColor::Red}) },
	m_player2{ std::make_shared<Player>(Player{50,50,PieceColor::Black}) },
	m_current_player{ m_player1.get() }
{}

const Board& Game::getBoard() const noexcept
{
	return m_board;
}

Player* Game::getCurrentPlayer() const noexcept
{
	return m_current_player;
}

const State& Game::getState() const noexcept
{
	return m_state;
}

bool Game::finished()
{
	if (m_state != State::None) return true;
	return false;
}

void Game::nextPlayer()
{
	if (m_current_player == m_player1.get()) {
		m_current_player = m_player2.get();
	}
	else {
		m_current_player = m_player1.get();
	}
	Bridge::save_pillar = nullptr;
	getCurrentPlayer()->setMoved(false);
}