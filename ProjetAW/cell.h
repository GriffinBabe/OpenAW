#ifndef CELL_H
#define CELL_H


class Cell
{
private:
    int posX;
    int posY;
    int type;

public:
    Cell(int posX,int posY,int t);
    Cell();
    int gettype();
    void settype(int Type);
    void setPos(int x,int y);
    int getPosX();
    int getPosY();

};

#endif // CELL_H
