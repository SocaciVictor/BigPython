#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TwixT2.h"

class TwixT2 : public QMainWindow
{
    Q_OBJECT

public:
    TwixT2(QWidget *parent = nullptr);
    ~TwixT2();

private:
    Ui::TwixT2Class ui;
};
