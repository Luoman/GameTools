#include "Map.hh"
#include "mainwindow.h"

Map::Map()
{
    //createMap(20, 15);
}

Map::~Map()
{

}

void                Map::createMap(int width, int height)
{
    m_iWidth = width;
    m_iHeight = height;
    for (int x = 0; x < m_iWidth / ROOM_WIDTH; ++x)
        for (int y = 0; y < m_iHeight / ROOM_HEIGHT; ++y)
            m_mRooms[x][y] = new Room(x, y);
}

void                Map::resetRooms()
{
    std::map<int, std::map<int, Room *> >::iterator   itX;
    std::map<int, Room *>::iterator   itY;

    for (itX = m_mRooms.begin(); itX != m_mRooms.end(); ++itX)
        for (itY = itX->second.begin(); itY != itX->second.end(); ++itY)
            if (itY->second != NULL)
                delete itY->second;
    m_mRooms.clear();
}

int                 Map::getWidth() const
{
    return (m_iWidth);
}

int                 Map::getHeight() const
{
    return (m_iHeight);
}

std::map<int, std::map<int, Room *> >   &Map::getRooms()
{
    return (m_mRooms);
}

Room                *Map::getRoom(int x, int y)
{
    return (m_mRooms[x][y]);
}

void                Map::setWidth(int width)
{
    m_iWidth = width;
}

void                Map::setHeight(int height)
{
    m_iHeight = height;
}

void                Map::setRoom(int x, int y, Room *room)
{
    m_mRooms[x][y] = room;
}
