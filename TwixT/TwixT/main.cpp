#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(800, 450, "#efefef");
   
    //Am adaugat Qt

    w.show();
    return a.exec();
}
