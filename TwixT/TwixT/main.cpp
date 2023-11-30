#include <QtCore/QCoreApplication>
#include "ConsoleGame.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConsoleGame game;
    game.run();

    return a.exec();
}
