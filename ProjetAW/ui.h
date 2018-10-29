#ifndef UI_H
#define UI_H

#include "game.h"
#include "menubox.h"
#include <vector>
#include <QPainter>

class UI
{
public:
	UI();
	void moveMenu(QPainter* p, Unit* u);
	void mapMenu(QPainter* p);
	void unitMenu(QPainter* p, Unit* u);
	void attackMenu(QPainter* p, Unit* u);
	void paint(QPainter* p, Unit* u);

	void cursorDown();
	void cursorUp();
	void setDimensions(int w, int h, int c);
	void setGame(Game* g);

	void setMoveCells(std::vector<std::pair<int,int>> mv);

	int getType();
	void setType(Unit* u, int t);

	void clearMenuBoxes();

	MenuBox *getSelectedBox();

private:
	Game* game;
	QPixmap* arrow;
	QPixmap* target;
	QPixmap* redtarget;
	QPixmap* moveCellImage;
	int menuType; // Type of menu that we need to show; O = no menu; 1 = moveMenu; 2 = unitMenu; 3 = mapMenu;
	Unit* selectedUnit;
	int width, height, cellDim, cursorPos; // Window width and height, used for displaying menu at the right place
	std::vector<std::pair<int,int>> moveCells;
	std::vector<MenuBox*>* menuBoxes;
	std::vector<Unit*>* attackableUnits;

	MenuBox* selectedBox;
	Unit* selectedAttackableUnit;
};

#endif //UI_H
