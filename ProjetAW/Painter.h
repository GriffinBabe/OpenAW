#pragma once
#include <QtWidgets/qopenglwidget.h>
#include <QPainter>
#include <iostream>

class Painter {
	/*
		tutoriel pour le widget opengl dans la fenetre
		http://doc.qt.io/qt-5/qtopengl-2dpainting-example.html#
	*/

public:
	void paint(QPainter *painter, QPaintEvent *event, int elasped);

private:
	QBrush background;
	QBrush circleBrush;
	QFont textFont;
	QPen circlePen;
	QPen textPen;
};

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(Painter *painter, QWidget *parent);

public slots:
	void animate();

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	Painter *painter;
	int elapsed;
};