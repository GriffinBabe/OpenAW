#ifndef UI_H
#define UI_H

#include "game.h"
#include <QPainter>

class UI
{
public:
	UI();
	void moveMenu(QPainter* p, Unit* u);
	void mapMenu(QPainter* p);
	void unitMenu(QPainter* p, Unit* u);
	void paint(QPainter* p, Unit* u);

	void setMenuType(int t);
	void cursorDown();
	void cursorUp();
	void setDimensions(int w, int h, int c);
	void setGame(Game* g);

	void setMoveCells(std::vector<std::pair<int,int>> mv);

private:
	Game* game;
	QPixmap* arrow;
	QPixmap* moveCellImage;
	int menuType; // Type of menu that we need to show; O = no menu; 1 = moveMenu; 2 = unitMenu; 3 = mapMenu;
	Unit* selectedUnit;
	int width, height, cellDim, cursorPos; // Window width and height, used for displaying menu at the right place
	std::vector<std::pair<int,int>> moveCells;
};

#endif // UI_H
