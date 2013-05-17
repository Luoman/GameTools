#ifndef MAP_HH
#define MAP_HH

#include <map>

#include "Room.hh"

class Map
{
public:
    Map();
    ~Map();

public:
    void                createMap(int width, int height);
    void                resetRooms();

public:
    int                 getWidth() const;
    int                 getHeight() const;
    std::map<int, std::map<int, Room *> >   &getRooms();
    Room                *getRoom(int x, int y);

public:
    void                setWidth(int width);
    void                setHeight(int height);
    void                setRoom(int x, int y, Room *);

private:
    std::map<int, std::map<int, Room *> >   m_mRooms;
    int                 m_iWidth, m_iHeight;
};

#endif // MAP_HH
