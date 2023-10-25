#include "All_Include_File.h"
#include "Game.h"

int main()
{
    std::cout << "Stemi main\n"; // Verificare Branch
    //Initializare game onject
    Game game;

    //Game loop
    while (game.running()) {
        game.update();
        game.render();
    }

    // nu modificati main-ul cand dati commit 
    // puteti sa il folositi pt testare dar cand dati commit sa ramana asa
    // este stufful pt SFML 
    
    return 0;
}

