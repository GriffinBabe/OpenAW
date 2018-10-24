#include "map.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <iostream>
#include <regex>
#include <algorithm>


Map::Map(std::string mapPath)
{
   /*Ouverture du Fichier et récupération des données
    Le lien du fichier est ":/Maps/map1.txt"
    On détermine la taille du tableau et on stocke les éléments dans un vector de vector d'entier data
    Ensuite, on crée les Cell à partir de ce vector.
    */
    std::vector<std::vector<int>> data;

    QString path = QString::fromStdString(mapPath);
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
    for(int i=0;i<data.size();i++) {
        this->cells->push_back(std::vector<Cell>());
        for(int j=0;j<data[1].size();j++){
            this->cells->at(i).push_back(getNewCell(i, j, data[i][j]));
        }
    }

}

Cell Map::getNewCell(int i,int j, int id) {
    if(id>=101 && id<=110){
        Pipe pipe(j,i,id);
        return pipe;
    }else if(id==2){
        Mountain mountain(j,i,id);
        return mountain;
    }else if(id==34){
        City city(j,i,id);
        return city;
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
        std::cout<<reefs.getPosX()<<";"<<reefs.getPosY()<<std::endl;
        return reefs;
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
    std::cout << this->cells->size() << std::endl;
    std::cout << this->cells->at(1).size() << std::endl;
    return this->cells->at(x).at(y);
}
