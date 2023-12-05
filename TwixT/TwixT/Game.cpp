#include "Game.h"

void Game::updateState(Pillar* pillar1, Pillar* pillar2)
{


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