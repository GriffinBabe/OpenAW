#ifndef CELL_H
#define CELL_H


class Cell
{
protected:
    int posX, posY, type, dir;

public:
    Cell(int posX,int posY,int t);
    Cell();
    int gettype();
    void settype(int Type);
    void setPos(int x,int y);
    int getPosX();
    int getPosY();

};

// --------------------------------------------------

class Pipe : public Cell
{
private:

public:
    Pipe(int x, int y, int id);


};

// --------------------------------------------------------------
class Grass : public Cell
{
private:

public:
    Grass(int x, int y, int id);


};

#endif // CELL_H
