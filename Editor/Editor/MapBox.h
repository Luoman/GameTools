#ifndef MAPBOX_H
#define MAPBOX_H

#include <QImage>
#include <QPoint>

#include "ImageManager.h"

class MapBox
{
public:
    MapBox();
    MapBox(int x, int y);

public:
    t_Image *getFirstImage() const;
    const QPoint &getPos() const;

public:
    void setFirstImage(t_Image *img);
    void setPos(int x, int y);

public:
    t_Image *m_pImage;
    QPoint m_pPos;
};

#endif // MapBOX_H
