#include "Game.h"
#include "MainWindow.h"
#include "Player.h"
#include <QtWidgets/QApplication>

int Game::run(int& argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow main_window{ 960 , 540, "#efefef" };
    //ceva
    main_window.show();
    return app.exec();
}
