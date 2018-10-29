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

// -----------------------------------------------------------------------------------

WaitBox::WaitBox(int x, int y, int w, int h) {
	posX=x; posY=y; width=w; height=h; title="Wait"; action = 0;
}

// ------------------------------------------------------------------------------------

AttackBox::AttackBox(int x, int y, int w, int h) {
	posX=x; posY=y; width=w; height=h; title="Attack"; action = 1;
}

// ------------------------------------------------------------------------------------

CaptureBox::CaptureBox(int x, int y, int w, int h) {
	posX=x; posY=y; width=w; height=h; title="Capture"; action = 2;
}
