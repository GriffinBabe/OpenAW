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


// --------------------------------------------------------------
class Mountain : public Cell
{
private:

public:
    Mountain(int x, int y, int id);


};

// --------------------------------------------------------------
class City : public Cell
{
private:

public:
    City(int x, int y, int id);


};

// --------------------------------------------------------------

class Woods : public Cell
{
private:

public:
    Woods(int x, int y, int id);
};

// --------------------------------------------------------------

class River : public Cell
{
private:

public:
    River(int x, int y, int id);
};

// --------------------------------------------------------------

class Roads : public Cell
{
private:

public:
    Roads(int x, int y, int id);


};
class Sea : public Cell
{
private:

public:
    Sea(int x, int y, int id);


};

class Reefs : public Cell
{
private:

public:
    Reefs(int x, int y, int id);


};



#endif // CELL_H
