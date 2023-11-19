#include "GameController.h"

void GameController::switchPlayer(Player& p1,Player& p2, Player& curentPlayer){
	if (curentPlayer == p1)
		curentPlayer = p2;
	else
		curentPlayer = p1;
}
