#pragma once
#include "Board.h"
#include "AiPlayer.h"
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
	uint16_t m_turnNumber{ 0 };
	uint16_t maxNumPillars;
	uint16_t maxNumBridges;
public:
	Game(const uint16_t& rows, const uint16_t& columns, const uint16_t& number_pillars, const uint16_t& number_bridges);
	Game() = default;
	const Board& getBoard() const noexcept;
	Board* getBoardPtr();
	uint16_t getTurnNumber() const noexcept;
	Player* getCurrentPlayer() const noexcept;
	void setPlayerAi(uint16_t nr_player, std::string fileData);
	Player* getPlayer1() const noexcept;
	Player* getPlayer2() const noexcept;
	bool addMove(Move* move); //return true when a move is an end turn move, false otherwise
	const State& getState() const noexcept;
	void setState(State&& state);
	bool finished() const;
	void nextPlayer();
	void switchPlayer(); //changes to other player without checking gameState and updating the state
	virtual bool addPillar(const Point& point);
	bool addBridge(const Point& point1, const Point& point2);
	bool removePillar(const Point& point);
	bool removeBridges(const Point& point1,const Point& point2);
	void reset();
	void updateState();
	void updateState(const Point& point1, const Point& point2);
	void swichColor();
	bool saveGame(const std::string& fisier);
	bool loadGame(const std::string& fisier);
	std::unique_ptr<Move> getHint();
protected:
	std::unique_ptr<Player> m_player1;
	std::unique_ptr<Player> m_player2;
	//observer
	Player* m_current_player;
public:
	static std::unique_ptr<AiPlayer> m_aiPlayer;
};
