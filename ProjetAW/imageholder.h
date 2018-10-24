#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H

#include <QPixmap>

class ImageHolder
{
private:
    QPixmap* cursorImage;
    QPixmap* grassImage;

public:
    ImageHolder();

    QPixmap* getCursorImage();
    QPixmap* getTerrainImage(int id);
};

#endif // IMAGEHOLDER_H
