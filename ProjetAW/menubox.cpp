#include "menubox.h"

MenuBox::MenuBox() {}

int MenuBox::getPosX()
{
	return posX;
}

int MenuBox::getPosY() {
	return posY;
}


int MenuBox::getWidth() {
	return width;
}

int MenuBox::getHeight() {
	return height;
}

int MenuBox::getAction()
{
	return action;
}

std::string MenuBox::getTitle()
{
	return title;
}

QPixmap *MenuBox::getImage()
{
	return this->image;
}

// -----------------------------------------------------------------------------------

WaitBox::WaitBox(int x, int y, int w, int h) {
	posX=x; posY=y; width=w; height=h; title="Wait"; action = 0;
	this->image = new QPixmap(":/Images/wait.png");
}

// ------------------------------------------------------------------------------------

AttackBox::AttackBox(int x, int y, int w, int h) {
	posX=x; posY=y; width=w; height=h; title="Attack"; action = 1;
	this->image = new QPixmap(":/Images/attack.png");
}

// ------------------------------------------------------------------------------------

CaptureBox::CaptureBox(int x, int y, int w, int h) {
	posX=x; posY=y; width=w; height=h; title="Capture"; action = 2;
	this->image = new QPixmap(":/Images/capture.png");
}

// ------------------------------------------------------------------------------------

NextTurnBox::NextTurnBox(int x, int y, int w, int h) {
	posX=x; posY=y; width=w; height=h; title="Next Turn"; action = 3;
	this->image = new QPixmap(":/Images/end.png");
}
