#include "map.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <iostream>
#include <regex>
#include <algorithm>
#include "buildings/citybuilding.h"
#include "buildings/factorybuilding.h"
#include "buildings/airportbuilding.h"

Map::Map(int mapId)
{
   /*Ouverture du Fichier et récupération des données
    Le lien du fichier est ":/Maps/map1.txt"
    On détermine la taille du tableau et on stocke les éléments dans un vector de vector d'entier data
    Ensuite, on crée les Cell à partir de ce vector.
    */
    std::vector<std::vector<int>> data;
	this->buildings = new std::vector<Buildings*>;

	//:/Maps/map1.txt
	QString path = QString::fromStdString(":/Maps/"+mapPath+".txt");

    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        int counter=0;
        while(!in.atEnd()) {
            QString line = in.readLine();
            std::string line2=line.toStdString();

            std::vector<int> line3=split(line2,',');
            data.push_back(line3);
            counter+=1;
            sizeX=line3.size();
        }
    sizeY=counter;
    std::cout << "Map width: " << sizeX << std::endl;
    std::cout << "Map height: " << sizeY <<std::endl;
    file.close();
    } else {
        throw "The file didn't open correctly";
    }
    this->cells = new std::vector<std::vector<Cell>>;
    for (int y = 0; y < data[1].size(); y++) {
        this->cells->push_back(std::vector<Cell>());
        for (int x = 0; x < data.size(); x++) {
			this->cells->at(y).push_back(getNewCell(y,x,data[x][y]));
        }
	}
}

Cell Map::getNewCell(int j,int i, int id) {
    /*
     * Gives a cell with the right x and y coordinates
     */
    if(id>=101 && id<=110){
        Pipe pipe(j,i,id);
        return pipe;
    }else if(id==2){
        Mountain mountain(j,i,id);
        return mountain;
    }else if(id==34 || id==125 || id==95){
        City city(j,i,id);
		this->buildings->push_back(new CityBuilding(j,i,id));
        return city;
	} else if (id==35 || id==92 || id== 123) {
		Factory factory(j,i,id);
		this->buildings->push_back(new FactoryBuilding(j,i,id));
		return factory;
    }else if (id==36) {
        Airport airport(j,i,id);
		this->buildings->push_back(new AirportBuilding(j,i,id));
        return airport;
    }else if(id==3){
        Woods woods(j,i,id);
        return woods;
    }else if(id>=4&&id<=10){
        River river(j,i,id);
        return river;
    }else if(id>=15&&id<=25){
        Roads roads(j,i,id);
        return roads;
    }else if(id>=29&&id<=30){
        Sea sea(j,i,id);
        return sea;
    }else if(id==33){
        Reefs reefs(j,i,id);
		return reefs;
	} else if (id==26 || id==27) {
		Bridge bridge(j,i,id);
		return bridge;
    }else {
        Grass grass(j,i,1);
        return grass;
    }
}

std::vector<int> Map::split(const std::string& input, char delim) { // Char is the devider characer
    std::stringstream ss(input);
    std::string item;
    std::vector<std::string> elems;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    std::vector<int> intelems;
    for (int i = 0; i < elems.size(); ++i) {
        int temp = std::stoi(elems.at(i));
        intelems.push_back(temp);
    }
    return intelems;
}

int Map::getSizeX() {
    return sizeX;
}

int Map::getSizeY(){
    return sizeY;
}

Cell Map::getCellAt(int x, int y) {
	return cells->at(x).at(y);
}

std::vector<std::vector<Cell> > *Map::getCells()
{
	if (this->cells != nullptr) {
		return this->cells;
	} else {
		throw "Cells Pointer in Map is null";
	}

}

std::vector<Buildings*> *Map::getBuildings()
{
	return this->buildings;
}
