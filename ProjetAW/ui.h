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

	void cursorDown();
	void cursorUp();
	void setDimensions(int w, int h, int c);
	void setGame(Game* g);

	void setMoveCells(std::vector<std::pair<int,int>> mv);

private:
	Game* game;
	QPixmap* arrow;
	QPixmap* moveCellImage;
	int width, height, cellDim, cursorPos; // Window width and height, used for displaying menu at the right place
	std::vector<std::pair<int,int>> moveCells;
};

#endif // UI_H
