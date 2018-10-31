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
	QPixmap* image;
public:
	MenuBox(int x, int y, int w, int h);
	MenuBox();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	int getAction();

	std::string getTitle();
	QPixmap* getImage();
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

class NextTurnBox : public MenuBox
{
public:
	NextTurnBox(int x, int y, int w, int h);
};

class NewInfateryBox : public MenuBox
{
public:
	NewInfateryBox(int x, int y, int w, int h);
};

class NewBazookaBox : public MenuBox
{
public:
	NewBazookaBox(int x,int y,int w,int h);
};

class NewReconBox : public MenuBox
{
public:
	NewReconBox(int x,int y,int w,int h);
};

class NewTankBox : public MenuBox
{
public:
	NewTankBox(int x,int y,int w,int h);
};

class NewMdTankBox : public MenuBox
{
public:
	NewMdTankBox(int x,int y,int w,int h);
};

class NewMegaTankBox : public MenuBox
{
public:
	NewMegaTankBox(int x,int y,int w,int h);
};

class NewNeoTankBox : public MenuBox
{
public:
	NewNeoTankBox(int x,int y,int w,int h);
};

class NewAntiAirBox : public MenuBox
{
public:
		NewAntiAirBox(int x, int y, int w, int h);
};

class NewBCopterBox : public MenuBox
{
public:
	NewBCopterBox(int x, int y, int w, int h);
};

class NewBomberBox : public MenuBox
{
public:
	NewBomberBox(int x, int y, int w, int h);
};

class NewFighterBox : public MenuBox
{
public:
	NewFighterBox(int x, int y, int w, int h);
};

#endif // MENUBOX_H
