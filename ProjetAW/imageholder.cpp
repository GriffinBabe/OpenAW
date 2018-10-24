#include "imageholder.h"

ImageHolder::ImageHolder()
{
    this->cursorImage = new QPixmap(":/Images/cursor.png");
    this->grassImage = new QPixmap(":/Images/Terrain/grass.png");
}

QPixmap* ImageHolder::getCursorImage() {
    return this->cursorImage;
}

QPixmap* ImageHolder::getTerrainImage(int id) {
    if (id == 1) {
        return this->grassImage;
    }
}
