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

// -------------------------------------------------------------------------------------

NewInfateryBox::NewInfateryBox(int x, int y, int w, int h) {
	posX = x; posY = y; width =w; height = h; title="New Infantery Box"; action = 4;
	this->image = new QPixmap(":/Images/newInfantery.png");
}

// -------------------------------------------------------------------------------------

NewBazookaBox::NewBazookaBox(int x, int y, int w, int h) {
	posX = x; posY = y; width =w; height = h; title="New Bazooka Box"; action = 5;
	this->image = new QPixmap(":/Images/newBazooka.png");
}

// -------------------------------------------------------------------------------------

NewReconBox::NewReconBox(int x, int y, int w, int h) {
	posX = x; posY = y; width =w; height = h; title="New Recon Box"; action = 6;
	this->image = new QPixmap(":/Images/newRecon.png");
}

// -------------------------------------------------------------------------------------

NewTankBox::NewTankBox(int x, int y, int w, int h) {
	posX = x; posY = y; width =w; height = h; title="New Tank Box"; action = 7;
	this->image = new QPixmap(":/Images/newTank.png");
}

// -------------------------------------------------------------------------------------

NewMdTankBox::NewMdTankBox(int x, int y, int w, int h) {
	posX = x; posY = y; width =w; height = h; title="New MdTank Box"; action = 8;
	this->image = new QPixmap(":/Images/newMdTank.png");
}
// -------------------------------------------------------------------------------------

NewMegaTankBox::NewMegaTankBox(int x, int y, int w, int h) {
	posX = x; posY = y; width =w; height = h; title="New MegaTank Box"; action = 9;
	this->image = new QPixmap(":/Images/newMegaTank.png");
}
// -------------------------------------------------------------------------------------

NewNeoTankBox::NewNeoTankBox(int x, int y, int w, int h) {
	posX = x; posY = y; width =w; height = h; title="New NeoTank Box"; action = 10;
	this->image = new QPixmap(":/Images/newNeoTank.png");
}
// -------------------------------------------------------------------------------------

NewAntiAirBox::NewAntiAirBox(int x, int y, int w, int h) {
	posX = x; posY = y; width =w; height = h; title="New AntiAir Box"; action = 11;
	this->image = new QPixmap(":/Images/newAntiAir.png");
}
