#include <QtWidgets/QApplication>
#include "ConsoleGame.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ConsoleGame gameTrain;
    ConsoleGame game;
   

    gameTrain.train("RedData", "BlueData");
    game.run();
    
    //uncomment all the headers and sources from QtGraphics for this to work
    /*TwixTGame game;
    game.run();*/
    //return app.exec();
}
