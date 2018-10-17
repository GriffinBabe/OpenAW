#pragma once
#include <QtWidgets/qopenglwidget.h>
#include <QPainter>
#include <iostream>
#include <qtimer.h>

class Helper{
	/*
		QT Opengl widget tutorial here: 
		http://doc.qt.io/qt-5/qtopengl-2dpainting-example.html#
	*/

public:
	void paint(QPainter *painter, QPaintEvent *event, int elasped);
	Helper();

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
	Widget(Helper *helper, QWidget *parent);

public slots:
	void animate();

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	Helper *helper;
	int elapsed;
};

class GLWidget : public QOpenGLWidget {
	/*
		We are using the GL Widget in this case,
		not the simple widget.
	*/
	Q_OBJECT;

public:
	GLWidget(Helper *helper, QWidget *parent);

public slots:
	void animate();

protected:
	void paintEvent(QPaintEvent *event) override;


};