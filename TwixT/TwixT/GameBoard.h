#pragma once

#include <QWidget>
#include "ui_GameBoard.h"

class GameBoard : public QWidget
{
	Q_OBJECT

public:
	GameBoard(QWidget *parent = nullptr);
	~GameBoard();

private:
	Ui::GameBoardClass ui;
};
