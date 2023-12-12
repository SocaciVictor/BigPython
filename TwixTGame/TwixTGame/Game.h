#pragma once
#include "Board.h"
#include "Player.h"
#include <fstream>
#include <string>

enum class State : std::uint8_t
{
	None,
	Draw,
	Win,
};

class Game
{
protected:
	Board m_board;
	State m_state{ State::None };
public:
	Game(const uint16_t& rows, const uint16_t& columns, const uint16_t& number_pillars, const uint16_t& number_bridges);
	Game() = default;
	const Board& getBoard() const noexcept;
	Player* getCurrentPlayer() const noexcept;
	const State& getState() const noexcept;
	const bool& finished() const;
	void nextPlayer();
	const bool& addPillar(const Point& point);
	const bool& addBridge(const Point& point1, const Point& point2);
	const bool& removeBridges(const Point& point1,const Point& point2);
	void updateState();
	void updateState(const Point& point1, const Point& point2);
	const bool& saveGame(const std::string& fisier);
	const bool& loadGame(const std::string& fisier);
protected:
	std::shared_ptr<Player> m_player1;
	std::shared_ptr<Player> m_player2;
	std::shared_ptr<Player> m_current_player;
};

