#pragma once
#include"Player.h"
#include"Board.h"

enum class State : std::uint8_t
{
	None,
	Draw,
	Win,
};

class Game : public GameElement
{
protected:
	Board m_board;
	State m_state{ State::None };
	void updateState(Pillar* pillar1, Pillar* pillar2);
	void updateState();
public:
	Game();
	const Board& getBoard() const noexcept;
	Player* getCurrentPlayer() const noexcept;
	const State& getState() const noexcept;
	void nextPlayer();
	bool finished();
private:
	std::shared_ptr<Player> m_player1;
	std::shared_ptr<Player> m_player2;
	Player* m_current_player;
};

