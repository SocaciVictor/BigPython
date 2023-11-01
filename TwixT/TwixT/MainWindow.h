#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"


class MainWindow : public QMainWindow
{
private:
    void paintEvent(QPaintEvent*);

public:
    MainWindow(int width = 400, int height = 300, QString color = "#ffffff", QWidget* parent = nullptr);
    ~MainWindow();
};
