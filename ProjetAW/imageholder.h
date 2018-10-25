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

    QPixmap* riverImageNS;
    // 6: QPixmap* riverImage;
    QPixmap* riverImageES;
    // 8: QPixmap* riverImage;
    QPixmap* riverImageNW;
    QPixmap* riverImageNE;
    QPixmap* riverImageEW;
    QPixmap* roadEW;
    QPixmap* roadNS;
    QPixmap* roadES;
    QPixmap* roadSW;
    QPixmap* roadNW;
    QPixmap* roadNE;
    QPixmap* road3S;
    QPixmap* road3W;
    QPixmap* road3N;
    QPixmap* road3E;
    QPixmap* pipeNS;
    QPixmap* pipeEW;
    QPixmap* pipeES;
    QPixmap* pipeNW;
    QPixmap* pipe2N;
    QPixmap* pipe2E;
    QPixmap* pipe2S;
    QPixmap* pipe2W;


    //Units
    QPixmap* infantery;

public:
    ImageHolder();

    QPixmap* getGrassImage();
    QPixmap* getCursorImage();
    QPixmap* getTerrainImage(int id);
};

#endif // IMAGEHOLDER_H
