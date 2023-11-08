#include <QtWidgets/QApplication>
#include "MainWindow.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow main_window{ 960 , 540, "#efefef" };

    //ceva

    main_window.show();

    return app.exec();
}