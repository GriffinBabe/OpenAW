#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_window.h"
#include "Game.h"

class Window : public QMainWindow
{
	/*
		This class is the view core funtion
	*/

	Q_OBJECT

public:
	Window(QWidget *parent = Q_NULLPTR); 
private:
	Game game();
	Ui::WindowClass ui;
};
