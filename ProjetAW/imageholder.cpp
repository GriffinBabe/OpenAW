#include "imageholder.h"

ImageHolder::ImageHolder()
{
    this->cursorImage = new QPixmap(":/Images/cursor.png");
    this->grassImage = new QPixmap(":/Images/Terrain/grass.png");
    this->reefImage = new QPixmap(":/Images/Terrain/reef.png");
    this->roadImage = new QPixmap(":/Images/Terrain/hroad.png");
    this->mountainImage = new QPixmap(":/Images/Terrain/mountain.png");
    this->seaImage = new QPixmap(":/Images/Terrain/sea.png");
    this->woodImage = new QPixmap(":/Images/Terrain/wood.png");
    this->pipeImage = new QPixmap(":/Images/Terrain/hpipe.png");
    this->riverImage = new QPixmap(":/Images/Terrain/river.png");
}

QPixmap* ImageHolder::getGrassImage() {
    return this->grassImage;
}

QPixmap* ImageHolder::getCursorImage() {
    return this->cursorImage;
}

QPixmap* ImageHolder::getTerrainImage(int id) {
    if (id == 1) {
        return this->grassImage;
    } else if (id == 33) {
        return this->reefImage;
    } else if (id == 3) {
        return this->woodImage;
    } else if (id>=15&&id<=25) {
        return this->roadImage;
    } else if (id>=29&&id<=30) {
        return this->seaImage;
    } else if (id==2) {
        return this->mountainImage;
    } else if (id>=101 && id<=110) {
        return this->pipeImage;
    } else if (id>=4&&id<=10) {
        return this->riverImage;
    } else {
        return this->grassImage;
    }
}
