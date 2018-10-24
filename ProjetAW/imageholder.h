#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H

#include <QPixmap>

class ImageHolder
{
private:
    //UI
    QPixmap* cursorImage;

    //Terrain
    QPixmap* grassImage;
    QPixmap* reefImage;
    QPixmap* woodImage;
    QPixmap* roadImage;
    QPixmap* seaImage;
    QPixmap* mountainImage;
    QPixmap* pipeImage;
    QPixmap* riverImage;

    //Units
    QPixmap* infantery;

public:
    ImageHolder();

    QPixmap* getGrassImage();
    QPixmap* getCursorImage();
    QPixmap* getTerrainImage(int id);
};

#endif // IMAGEHOLDER_H
