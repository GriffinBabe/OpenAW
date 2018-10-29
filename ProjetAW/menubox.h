#ifndef MENUBOX_H
#define MENUBOX_H

#include <QPainter>
#include <string>

// ------------------------------------------------------------------------------------------------

class MenuBox
{
protected:
	int posX, posY, width, height, action;
	std::string title;
public:
	MenuBox(int x, int y, int w, int h);
	MenuBox();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	int getAction();

	std::string getTitle();
};

class WaitBox : public MenuBox
{
public:
	WaitBox(int x, int y, int w, int h);
};

class AttackBox : public MenuBox
{
public:
	AttackBox(int x, int y, int w, int h);
};

class CaptureBox : public MenuBox
{
public:
	CaptureBox(int x, int y, int w, int h);
};

#endif // MENUBOX_H
