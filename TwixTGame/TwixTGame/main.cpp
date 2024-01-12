#include <QtWidgets/QApplication>
#include <QFontDatabase>
#include "ConsoleGame.h"
#include "ConsoleTrainAiGame.h"
#include "ConsoleBulzozeristGame.h"
#include "TwixTGame.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFont appFont("Itim", 24, 1);
    app.setFont(appFont);
   /*ConsoleTrainAiGame game{5};
    game.run();*/
    /*ConsoleTrainAiGame trainGame{ 5 };
    trainGame.train("RedData", "BlueData");*/
  /*  ConsoleBulzozeristGame game;
    game.run();*/

   

    TwixTGame game;
    game.run();

    return app.exec();
}