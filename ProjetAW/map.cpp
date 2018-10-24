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
    Cell cells[sizeX][sizeY];
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[1].size();j++){
            cells[j][i] = getNewCell(i, j, data[i][j]);
        }
    }

}

Cell Map::getNewCell(int i,int j, int id) {
    if(id>=101 && id<=110){
        Pipe pipe(j,i,id);
        return pipe;
    } else {
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
