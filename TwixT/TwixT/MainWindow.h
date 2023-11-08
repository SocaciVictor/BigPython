#pragma once
#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
private:
    int size_width;
    int size_height;
    QColor background_color;
    QVector<QWidget*> vector_widgeturi;

public:
    //Constructor Deconstructor
    MainWindow(QWidget* parent = nullptr);
    MainWindow(int width, int height, QWidget* parent = nullptr);
    MainWindow(int width, int height, QColor background_color, QWidget* parent = nullptr);
    ~MainWindow();
    //Geteri
   
};
