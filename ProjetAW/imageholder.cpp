#include "imageholder.h"
#include <iostream>

ImageHolder::ImageHolder()
{

    //Cells
    this->cursorImage = new QPixmap(":/Images/cursor.png");
    this->grassImage = new QPixmap(":/Images/Terrain/grass.png");
    this->reefImage = new QPixmap(":/Images/Terrain/reef.png");
    this->mountainImage = new QPixmap(":/Images/Terrain/mountain.png");
    this->seaImage = new QPixmap(":/Images/Terrain/sea.png");
    this->woodImage = new QPixmap(":/Images/Terrain/wood.png");

    this->riverImageEW = new QPixmap(":/Images/Terrain/riverEW.png");
    this->riverImageNS = new QPixmap(":/Images/Terrain/riverNS.png");
    this->riverImageES = new QPixmap(":/Images/Terrain/riverES.png");
    this->riverImageNW= new QPixmap(":/Images/Terrain/riverNW.png");
    this->riverImageNE= new QPixmap(":/Images/Terrain/riverNE.png");
    this->riverImageSW = new QPixmap(":/Images/Terrain/riverSW.png");
    this->roadEW= new QPixmap(":/Images/Terrain/roadEW.png");
    this->roadNS= new QPixmap(":/Images/Terrain/roadNS.png");
    this->roadES= new QPixmap(":/Images/Terrain/roadES.png");
    this->roadSW= new QPixmap(":/Images/Terrain/roadSW.png");
    this->roadNW= new QPixmap(":/Images/Terrain/roadNW.png");
    this->roadNE= new QPixmap(":/Images/Terrain/roadNE.png");
    this->road3S= new QPixmap(":/Images/Terrain/road3S.png");
    this->road3W= new QPixmap(":/Images/Terrain/road3W.png");
    this->road3N= new QPixmap(":/Images/Terrain/road3N.png");
    this->road3E= new QPixmap(":/Images/Terrain/road3E.png");


    this->pipeNS= new QPixmap(":/Images/Terrain/pipeNS.png");
    this->pipeEW= new QPixmap(":/Images/Terrain/pipeEW.png");
    this->pipeES= new QPixmap(":/Images/Terrain/pipeES.png");
    this->pipeNW= new QPixmap(":/Images/Terrain/pipeNW.png");
    this->pipe2N= new QPixmap(":/Images/Terrain/pipe2N.png");
    this->pipe2E= new QPixmap(":/Images/Terrain/pipe2E.png");
    this->pipe2S= new QPixmap(":/Images/Terrain/pipe2S.png");
    this->pipe2W= new QPixmap(":/Images/Terrain/pipe2W.png");

    this->bridgeNS = new QPixmap(":/Images/Terrain/bridgeNS.png");
    this->bridgeEW = new QPixmap(":/Images/Terrain/bridgeEW.png");


    // Units
    this->infanteryB = new QPixmap(":/Images/Units/infanteryB.png");
    this->infanteryR = new QPixmap(":/Images/Units/infanteryR.png");

    this->bazookaB = new QPixmap(":/Images/Units/bazookaB.png");
    this->bazookaB = new QPixmap(":/Images/Units/bazookaR.png");

	this->reconB = new QPixmap(":/Images/Units/reconB.png");
	this->reconR = new QPixmap(":/Images/Units/reconR.png");

	this->tankB = new QPixmap(":/Images/Units/tankB.png");
	this->tankR = new QPixmap(":/Images/Units/tankR.png");

	this->megatankB = new QPixmap(":/Images/Units/megatankB.png");
	this->megatankR = new QPixmap(":/Images/Units/megatankR.png");

	this->mdtankR = new QPixmap(":/Images/Units/mdtankR.png");
	this->mdtankB = new QPixmap(":/Images/Units/mdtankB.png");

	this->neotankR = new QPixmap(":/Images/Units/neotankR.png");
	this->neotankB = new QPixmap(":/Images/Units/neotankB.png");

	this->bcopterB = new QPixmap(":/Images/Units/bcopterB.png");
	this->bcopterR = new QPixmap(":/Images/Units/bcopterR.png");

	this->bomberB = new QPixmap(":/Images/Units/bomberB.png");
	this->bomberR = new QPixmap(":/Images/Units/bomberR.png");

	this->fighterB = new QPixmap(":/Images/Units/fighterB.png");
	this->fighterR = new QPixmap(":/Images/Units/fighterR.png");

	this->antiairB = new QPixmap(":/Images/Units/antiairB.png");
	this->antiairR = new QPixmap(":/Images/Units/antiairR.png");

	//buildings
	this->cityB = new QPixmap(":/Images/Buildings/cityB.png");
	this->cityR = new QPixmap(":/Images/Buildings/cityR.png");
	this->city = new QPixmap(":/Images/Buildings/city.png");
	this->factoryB = new QPixmap(":/Images/Buildings/factoryB.png");
	this->factoryR = new QPixmap(":/Images/Buildings/factoryR.png");
	this->factory = new QPixmap(":/Images/Buildings/factory.png");
    this->airportB = new QPixmap(":/Images/Buildings/airportB.png");
    this->airportR = new QPixmap(":/Images/Buildings/airportR.png");
    this->airport = new QPixmap(":/Images/Buildings/airport.png");


}

QPixmap* ImageHolder::getGrassImage() {
    return this->grassImage;
}

QPixmap* ImageHolder::getCursorImage() {
    return this->cursorImage;
}

QPixmap* ImageHolder::getUnitImage(int id, char teamColor) {
    /*
     * Id is holded in the unit class, it is used to return the right image
     */
    if (id == 1) { // infantery
        if (teamColor == 'B') {
            return this->infanteryB;
        } else {
            return this->infanteryR;
        }
    } else if (id == 2) { // bazooka
        if (teamColor == 'B') {
            return this->bazookaB;
        } else {
            return this->bazookaR;
        }
	} else if (id == 3) { // recon
		if (teamColor == 'B') {
			return this->reconB;
		} else {
			return this->reconR;
		}
	} else if (id == 4) { // antiair
		if (teamColor == 'B') {
			return this->antiairB;
		} else {
			return this->antiairR;
		}
	} else if (id == 5) { // tank
		if (teamColor == 'B') {
			return this->tankB;
		} else {
			return this->tankR;
		}
	} else if (id == 6) { // mdtank
		if (teamColor == 'B') {
			return this->mdtankB;
		} else {
			return this->mdtankR;
		}
	} else if (id == 7) { // megatank
		if (teamColor == 'B') {
			return this->megatankB;
		} else {
			return this->megatankR;
		}
	} else if (id == 8) { // neotank
		if (teamColor == 'B') {
			return this->neotankB;
		} else {
			return this->neotankR;
		}
	} else if (id == 9) { // bcopter
		if (teamColor == 'B') {
			return this->bcopterB;
		} else {
			return this->bcopterR;
		}
	} else if (id == 10) { // fighter
		if (teamColor == 'B') {
			return this->fighterB;
		} else {
			return this->fighterR;
		}
	} else if (id == 11) { // bomber
		if (teamColor == 'B') {
			return this->bomberB;
		} else {
			return this->bomberR;
		}
	}
}
QPixmap* ImageHolder::getBuildingImage(int id, char teamColor) {

    if (id == 1) { // Factory
        if (teamColor == 'B') {
            return this->factoryB;
		} else if (teamColor == 'R') {
            return this->factoryR;
		} else {
			return this->factory;
		}

	} else if (id == 2) { //City
		if (teamColor == 'B') {
			return this->cityB;
		} else if (teamColor == 'R') {
			return  this->cityR;
		} else {
			return this->city;
		}
	}
    else if (id == 3) { //Airport
            if (teamColor == 'B') {
                return this->airportB;
            } else if (teamColor == 'R') {
                return  this->airportR;
            } else {
                return this->airport;
            }
        }
}
QPixmap* ImageHolder::getTerrainImage(int id) {
    switch(id) {
        case 2: return this->mountainImage;
        case 3: return this->woodImage;
        case 4: return this->riverImageEW;
        case 5: return this->riverImageNS;
        //case 6: return this->riverImage;
        case 7: return this->riverImageES;
        case 8: return this->riverImageSW;
        case 9: return this->riverImageNW;
        case 10: return this->riverImageNE;
        case 15: return this->roadEW;
        case 16: return this->roadNS;
        case 18: return this->roadES;
        case 19: return this->roadSW;
        case 20: return this->roadNW;
        case 21: return this->roadNE;
        case 22: return this->road3S;
        case 23: return this->road3W;
        case 24: return this->road3N;
        case 25: return this->road3E;
        case 26: return this->bridgeEW;
        case 27: return this->bridgeNS;
        case 29:return this->seaImage;
        case 30:return this->seaImage;

        case 33: return this->reefImage;
        case 101: return this->pipeNS;
        case 102: return this->pipeEW;
        case 104: return this->pipeES;
        case 106:return this->pipeNW;
        case 107:return this->pipe2N;
        case 108:return this->pipe2E;
        case 109:return this->pipe2S;
        case 110:return this->pipe2W;
   }

    return this->grassImage;

}
