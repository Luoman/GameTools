#include "MapBox.h"
#include "ImageManager.h"

MapBox::MapBox()
{
    m_pImage = ImageManager::getSingleton()->getDefaultImage();
}

MapBox::MapBox(int x, int y)
{
    m_pPos = QPoint(x, y);
    m_pImage = ImageManager::getSingleton()->getDefaultImage();
}

void MapBox::setPos(int x, int y)
{
    m_pPos = QPoint(x, y);
}

const QPoint &MapBox::getPos() const
{
    return (m_pPos);
}

t_Image *MapBox::getFirstImage() const
{
    return (m_pImage);
}

void MapBox::setFirstImage(t_Image *img)
{
    m_pImage = img;
}
