#include "Game.h"
#include <queue>

void Game::updateState(Pillar* pillar1, Pillar* pillar2)
{
	auto comparator = [this](const Point& p1, const Point& p2) {
		if (getCurrentPlayer()->getColor() == PieceColor::Red) {
			return std::min(abs(p1.y - getBoard().getRows()), abs(p1.y - 0)) >
				std::min(abs(p2.y - getBoard().getRows()), abs(p2.y - 0));
		}
		if (getCurrentPlayer()->getColor() == PieceColor::Black) {
			return std::min(abs(p1.x - getBoard().getColumns()), abs(p1.x - 0)) >
				std::min(abs(p2.x - getBoard().getColumns()), abs(p2.x - 0));
		}
	};
	
	std::priority_queue<Point, std::vector<Point>, decltype(comparator)> pq(comparator);



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