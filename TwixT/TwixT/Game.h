#pragma once
#include"Player.h"
#include"Board.h"

class Game : public GameElement
{
protected:
	Board m_board;
public:
	Game();
	const Board& getBoard() const noexcept;
	Player* getCurrentPlayer() const noexcept;
	void nextPlayer();
	bool finished();
private:
	std::shared_ptr<Player> m_player1;
	std::shared_ptr<Player> m_player2;
	Player* m_current_player;
};

