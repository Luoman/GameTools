#ifndef         ROOM_HH
#define         ROOM_HH

#include        "MapBox.h"
#include        "Object.h"
#include        "Monster.h"
#include        "Door.h"
#include        "Event.h"

#include        <map>

class           Room
{
public:
    Room(int x, int y);

public:
    void            initialize(int x, int y);

public:
    int             getPosX() const;
    int             getPosY() const;
    std::map<int, std::map<int, MapBox> > &getBoxes();
    std::map<int, std::map<int, std::string> > &getStates();
    std::map<int, std::map<int, Object> > &getObjects();
    std::map<int, std::map<int, Monster> > &getMonsters();
    std::map<char, Door *> &getDoors();
    Object          &getObject(int x, int y);
    Monster         &getMonster(int x, int y);
    Door            *getDoor(char loc);
    Event           &getEvent();
    MapBox          &getBox(int x, int y);
    const QPoint    &getPosEvent() const;
    const std::string &getState(int x, int y);

public:
    void            setPos(int x, int y);
    void            setPosX(int x);
    void            setPosY(int y);
    void            setState(const std::string &state, int x, int y);
    void            setDoor(char loc, Door *door);
    void            setPosEvent(int x, int y);
    void            setObject(int x, int y, Object obj);
    void            setMonster(int x, int y, Monster monster);
    void            setEvent(int x, int y, Event event);
    void            removeDoor(char loc);

private:
    int             m_iX;
    int             m_iY;
    std::map<int, std::map<int, std::string> > m_mStates;
    std::map<int, std::map<int, MapBox> >   m_mBoxes;
    std::map<int, std::map<int, Object> >   m_mObjects;
    std::map<int, std::map<int, Monster> >  m_mMonsters;
    std::map<char, Door *>                m_mDoors;
    std::list<Event>                    m_lEvents;
    Event           m_cEvent;
    QPoint          m_pPosEvent;
};

#endif // ROOM_H
