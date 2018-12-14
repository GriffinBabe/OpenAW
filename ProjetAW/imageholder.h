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
    QPixmap* riverImageSW;
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

    QPixmap* bridgeNS;
    QPixmap* bridgeEW;



    //Units
    QPixmap* infanteryB;
    QPixmap* infanteryR;

    QPixmap* bazookaB;
    QPixmap* bazookaR;

	QPixmap* reconB;
	QPixmap* reconR;

	QPixmap* tankB;
	QPixmap* tankR;

	QPixmap* mdtankB;
	QPixmap* mdtankR;

	QPixmap* megatankB;
	QPixmap* megatankR;

	QPixmap* neotankB;
	QPixmap* neotankR;

	QPixmap* bcopterB;
	QPixmap* bcopterR;

	QPixmap* bomberB;
	QPixmap* bomberR;

	QPixmap* fighterB;
	QPixmap* fighterR;

	QPixmap* antiairB;
	QPixmap* antiairR;

	// Buildings
    QPixmap* factoryB;
    QPixmap* factoryR;
	QPixmap* factory;

	QPixmap* cityB;
	QPixmap* cityR;
	QPixmap* city;

    QPixmap* airport;
    QPixmap* airportB;
    QPixmap* airportR;

public:
    ImageHolder();
	~ImageHolder();
    QPixmap* getBuildingImage(int id, char teamColor);
    QPixmap* getUnitImage(int id, char teamColor);
    QPixmap* getGrassImage();
    QPixmap* getCursorImage();
    QPixmap* getTerrainImage(int id);
};

#endif // IMAGEHOLDER_H
