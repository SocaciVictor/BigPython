#include <QtWidgets/QApplication>
#include "ConsoleGame.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ConsoleGame game;
    game.run();
    return app.exec();
}
