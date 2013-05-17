#include "Room.hh"
#include "mainwindow.h"

Room::Room(int x, int y) : m_iX(x), m_iY(y)
{
    initialize(x, y);
    m_pPosEvent = QPoint(-1, -1);
}

int             Room::getPosX() const
{
    return (m_iX);
}

int             Room::getPosY() const
{
    return (m_iY);
}

std::map<int, std::map<int, MapBox> > &Room::getBoxes()
{
    return (m_mBoxes);
}

std::map<int, std::map<int, std::string> > &Room::getStates()
{
    return (m_mStates);
}

std::map<int, std::map<int, Object> > &Room::getObjects()
{
    return (m_mObjects);
}

std::map<int, std::map<int, Monster> > &Room::getMonsters()
{
    return (m_mMonsters);
}

std::map<char, Door *>     &Room::getDoors()
{
    return (m_mDoors);
}

Object          &Room::getObject(int x, int y)
{
    return (m_mObjects[x][y]);
}

Monster          &Room::getMonster(int x, int y)
{
    return (m_mMonsters[x][y]);
}

Door            *Room::getDoor(char loc)
{
    return (m_mDoors[loc]);
}

Event           &Room::getEvent()
{
    return (m_cEvent);
}

const QPoint    &Room::getPosEvent() const
{
    return (m_pPosEvent);
}

void            Room::setPosEvent(int x, int y)
{
    m_pPosEvent = QPoint(x, y);
}

const std::string   &Room::getState(int x, int y)
{
    return (m_mStates[x][y]);
}

void            Room::setState(const std::string &state, int x, int y)
{
    m_mStates[x][y] = state;
}

void            Room::setDoor(char loc, Door *door)
{
    m_mDoors[loc] = door;
}

void            Room::initialize(int x, int y)
{
    int posX = 0, posY = 0;

    m_mBoxes.clear();
    m_iX = x;
    m_iY = y;
    for (posX = 0; posX < ROOM_WIDTH; posX++)
        for (posY = 0; posY < ROOM_HEIGHT; posY++)
        {
            m_mBoxes[posX][posY].setPos(posX, posY);
            m_mStates[posX][posY] = "none";
        }
}

void            Room::setPosX(int x)
{
    m_iX = x;
}

void            Room::setPosY(int y)
{
    m_iY = y;
}

void            Room::setObject(int x, int y, Object obj)
{
    m_mObjects[x][y] = obj;
}

void            Room::setMonster(int x, int y, Monster monster)
{
    m_mMonsters[x][y] = monster;
}

void            Room::setEvent(int x, int y, Event event)
{
    m_cEvent = event;
    m_pPosEvent = QPoint(x, y);
}

MapBox          &Room::getBox(int x, int y)
{
    return (m_mBoxes[x][y]);
}

void                Room::removeDoor(char loc)
{
    Door            *door;

    door = m_mDoors[loc];
    if (door != NULL)
        delete door;
    m_mDoors.erase(loc);
}
