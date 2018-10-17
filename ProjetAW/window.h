#pragma once

#include <qgridlayout.h>
#include <qlabel.h>
#include <QtWidgets/QMainWindow>
#include "ui_window.h"
#include "Game.h"
#include "Painter.h"

class Window : public QWidget
{
	/*
		This class is the view core funtion, it uses a OpenGL widget
	*/

	Q_OBJECT

public:
	Window();
private:
	Helper helper;
};

