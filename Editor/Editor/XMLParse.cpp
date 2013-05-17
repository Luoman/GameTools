#include "mainwindow.h"
#include "XMLParse.hh"

#include <sstream>
#include <fstream>

XMLParse::XMLParse()
{
}

int		strToInt(std::string str)
{
    int		number;

    std::istringstream(str) >> number;
    return (number);
}

bool                XMLParse::serialize_background(const std::string &path, const std::string &fileName, Map *map)
{
    std::ofstream   out;
    int             x, y;

    out.open(path + fileName + ".background");
    if (out.is_open() == true)
    {
        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
        out << " <dungeon_background>" << std::endl;
        out << "  <width>" << map->getWidth() << "</width>" << std::endl;
        out << "  <height>" << map->getHeight() << "</height>" << std::endl;
        std::map<int, std::map<int, Room *> >::iterator itX;
        std::map<int, Room *>::iterator itY;

        for (itX = map->getRooms().begin(); itX != map->getRooms().end(); ++itX)
            for (itY = itX->second.begin(); itY != itX->second.end(); ++itY)
            {
                if (itY->second != NULL)
                {
                    out << "  <room>" << std::endl;
                    out << "    <posX>" << itY->second->getPosX() << "</posX>" << std::endl;
                    out << "    <posY>" << itY->second->getPosY() << "</posY>" << std::endl;
                    out << "    <pictures>" << std::endl;
                    for (x = 0; x < ROOM_WIDTH; ++x)
                        for (y = 0; y < ROOM_HEIGHT; ++y)
                        {
                            MapBox          &box = itY->second->getBox(x, y);

                            if (box.getFirstImage()->m_sName != QString("default"))
                            {
                                out << "       <picture>" << std::endl;
                                out << "           <posX>" << x << "</posX>" << std::endl;
                                out << "           <posY>" << y << "</posY>" << std::endl;
                                out << "           <texture>" << box.getFirstImage()->m_sName.toStdString() << "</texture>" << std::endl;
                                out << "       </picture>" << std::endl;
                            }
                        }
                    out << "    </pictures>" << std::endl;
                    out << "  </room>" << std::endl;
                }
            }
        out << " </dungeon_background>" << std::endl;
        out.close();
        return (true);
    }
    return (false);
}

bool                XMLParse::serialize(const std::string &path, const std::string &fileName, Map *map)
{
    std::ofstream   out;
    int             x, y;

    serialize_background(path, fileName, map);
    out.open(path + fileName);
    if (out.is_open() == true)
    {
        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
        out << " <dungeon>" << std::endl;
        out << "  <width>" << map->getWidth() << "</width>" << std::endl;
        out << "  <height>" << map->getHeight() << "</height>" << std::endl;
        std::map<int, std::map<int, Room *> >::iterator itX;
        std::map<int, Room *>::iterator itY;
        Monster         monster;
        Object          object;
        Event           event;

        for (itX = map->getRooms().begin(); itX != map->getRooms().end(); ++itX)
            for (itY = itX->second.begin(); itY != itX->second.end(); ++itY)
            {
                std::map<char, Door *>::iterator  itDoor;
                if (itY->second != NULL)
                {
                    out << "  <room>" << std::endl;
                    out << "  <posX>" << itY->second->getPosX() << "</posX>" << std::endl;
                    out << "  <posY>" << itY->second->getPosY() << "</posY>" << std::endl;
                    out << "   <doors>" << std::endl;
                    itDoor = itY->second->getDoors().begin();
                    for (; itDoor != itY->second->getDoors().end(); ++itDoor)
                        out << "    <" << itDoor->first << ">" << itDoor->second->getState() << "</" << itDoor->first << ">" << std::endl;
                    out << "   </doors>" << std::endl;
                    out << "   <objects>" << std::endl;
                    for (x = 0; x < ROOM_WIDTH; ++x)
                        for (y = 0; y < ROOM_HEIGHT; ++y)
                        {
                            if (itY->second->getState(x, y) == "object")
                            {
                                object = itY->second->getObject(x, y);
                                out << "    <" << object.getType() << ">" << std::endl;
                                out << "     <posX>" << x << "</posX>" << std::endl;
                                out << "     <posY>" << y << "</posY>" << std::endl;
                                if (object.getType() == "chest")
                                {
                                    out << "     <item>" << object.getItem() << "</item>" << std::endl;
                                    out << "     <visible>" << object.getVisible() << "</visible>"  << std::endl;
                                }
                                else if (object.getType() == "key")
                                    out << "     <visible>" << object.getVisible() << "</visible>"  << std::endl;
                                out << "    </" << object.getType() << ">" << std::endl;
                            }
                        }
                    out << "   </objects>" << std::endl;
                    out << "   <monster>" << std::endl;
                    for (x = 0; x < ROOM_WIDTH; ++x)
                        for (y = 0; y < ROOM_HEIGHT; ++y)
                        {
                            if (itY->second->getState(x, y) == "monster")
                            {
                                monster = itY->second->getMonster(x, y);
                                out << "    <" << monster.getName() << ">" << std::endl;
                                out << "     <posX>" << x << "</posX>" << std::endl;
                                out << "     <posY>" << y << "</posY>" << std::endl;
                                out << "    </" << monster.getName() << ">" << std::endl;
                            }
                        }
                    out << "   </monster>" << std::endl;
                    out << "   <event>" << std::endl;
                    if (itY->second->getPosEvent().x() != -1)
                    {
                        std::list<char>::iterator   itEventDoor;

                        event = itY->second->getEvent();
                        out << "    <" << event.getName() << ">" << std::endl;
                        if (event.getName() == "switch")
                            out << "    <condition>" << event.getCondition() << "</condition>" << std::endl;
                        if (event.getDoors().size() > 0)
                        {
                            itEventDoor = event.getDoors().begin();
                            for (; itEventDoor != event.getDoors().end(); ++itEventDoor)
                                out << "    <" << *itEventDoor << ">" << "</" << *itEventDoor << ">" << std::endl;
                        }
                        else
                        {
                            out << "    <posX>" << event.getPosX() << "</posX>" << std::endl;
                            out << "    <posY>" << event.getPosY() << "</posY>" << std::endl;
                        }
                        out << "    </" << event.getName() << ">" << std::endl;
                    }
                    out << "   </event>" << std::endl;
                    out << "   </room>" << std::endl;
                }
            }
        out << " </dungeon>" << std::endl;
        out.close();
        return (true);
    }
    return (false);
}

Map                 *XMLParse::unserialize(const std::string &path, const std::string &fileName)
{
    Map             *map = NULL;

    if (!m_xDoc.LoadFile(std::string(path + fileName).c_str()))
    {
        std::cout << "XML File loading fail : error = "  << m_xDoc.ErrorDesc() << std::endl;
        return (map);
    }
    std::cout << "XML File loading success" << std::endl;
    TiXmlElement* root = this->m_xDoc.FirstChildElement();
    if(root == NULL)
    {
        std::cout << "Failed to load file: No root element."
                  << std::endl;
        this->m_xDoc.Clear();
        return (map);
    }
    map = new Map;
    // DUNGEON
    TiXmlElement	*elementDungeon;
    elementDungeon = root->FirstChildElement();
    //    // DUNGEON : With
    map->setWidth(strToInt(elementDungeon->GetText()));
    elementDungeon = elementDungeon->NextSiblingElement();
    // DUNGEON : Height
    map->setHeight(strToInt(elementDungeon->GetText()));
    elementDungeon = elementDungeon->NextSiblingElement();
    map->createMap(map->getWidth(), map->getHeight());
    // DUNGEON : Rooms
    TiXmlElement	*elementRoom;

    // DUNGEON : Room
    for (bool roomOk = true; roomOk && elementDungeon; elementDungeon = elementDungeon->NextSiblingElement())
    {
        elementRoom = elementDungeon->FirstChildElement();
        Room	*room = new Room(0, 0);
        // DUNGEON : Room : posX
        room->setPosX(strToInt(elementRoom->GetText()));
        elementRoom = elementRoom->NextSiblingElement();
        // DUNGEON : Room : posY
        room->setPosY(strToInt(elementRoom->GetText()));
        elementRoom = elementRoom->NextSiblingElement();

        // DUNGEON : Room : Door
        TiXmlElement	*elementDoor = elementRoom->FirstChildElement();
        for (bool ok = true; ok && elementDoor; elementDoor = elementDoor->NextSiblingElement())
        {
            // DUNGEON : Room : Door : all the door
            if (elementDoor->ValueTStr().at(0) == 'n')
                room->setState("door", 9, 0);
            if (elementDoor->ValueTStr().at(0) == 's')
                room->setState("door", 9, 12);
            if (elementDoor->ValueTStr().at(0) == 'w')
                room->setState("door", 0, 6);
            if (elementDoor->ValueTStr().at(0) == 'e')
                room->setState("door", 17, 6);
            room->setDoor(elementDoor->ValueTStr().at(0), new Door(elementDoor->ValueTStr().at(0), elementDoor->GetText()));
            if (elementDoor == elementDoor->Parent()->LastChild())
                ok = false;

        }
        elementRoom = elementRoom->NextSiblingElement();

        // DUNGEON : Room : Object
        TiXmlElement	*elementObject = elementRoom->FirstChildElement();
        for (bool ok = true; ok && elementObject; elementObject = elementObject->NextSiblingElement())
        {
            // DUNGEON : Room : Object : all the objects
            Object		object;

            object.setType(elementObject->Value());
            TiXmlElement	*elementTypeObject = elementObject->FirstChildElement();
            for (bool objOk = true; objOk && elementTypeObject; elementTypeObject = elementTypeObject->NextSiblingElement())
            {
                // DUNGEON : Room : Object : Type Object : all the attribut of the object
                std::string	attribut(elementTypeObject->Value());
                if (attribut == "posX")
                    object.setPosX(strToInt(elementTypeObject->GetText()));
                else if (attribut == "posY")
                    object.setPosY(strToInt(elementTypeObject->GetText()));
                else if (attribut == "type")
                    object.setName(elementTypeObject->GetText());
                else if (attribut == "item")
                    object.setItem(elementTypeObject->GetText());
                else if (attribut == "visible")
                    object.setVisibleTxt(elementTypeObject->GetText());
                if (elementTypeObject == elementTypeObject->Parent()->LastChild())
                    objOk = false;
            }
            room->setState("object", object.getPosX(), object.getPosY());
            room->setObject(object.getPosX(), object.getPosY(), object);
            if (elementObject == elementObject->Parent()->LastChild())
                ok = false;
        }
        elementRoom = elementRoom->NextSiblingElement();

        // DUNGEON : Room : Monster
        TiXmlElement	*elementMonster = elementRoom->FirstChildElement();
        for (bool ok = true; ok && elementMonster; elementMonster = elementMonster->NextSiblingElement())
        {
            // DUNGEON : Room : Monster : all the monster
            Monster	monster;

            monster.setName(elementMonster->Value());
            TiXmlElement	*elementTypeMonster = elementMonster->FirstChildElement();
            for (bool monsterOk = true; monsterOk && elementTypeMonster; elementTypeMonster = elementTypeMonster->NextSiblingElement())
            {
                // DUNGEON : Room : Monster : TypeMonster : all the attribute of the monster
                std::string	attribut(elementTypeMonster->Value());
                if (attribut == "posX")
                    monster.setPosX(strToInt(elementTypeMonster->GetText()));
                else if (attribut == "posY")
                    monster.setPosY(strToInt(elementTypeMonster->GetText()));
                if (elementTypeMonster == elementTypeMonster->Parent()->LastChild())
                    monsterOk = false;
            }
            room->setMonster(monster.getPosX(), monster.getPosY(), monster);
            room->setState("monster", monster.getPosX(), monster.getPosY());
            if (elementMonster == elementMonster->Parent()->LastChild())
                ok = false;
        }
        elementRoom = elementRoom->NextSiblingElement();

        // DUNGEON : Room : Event
        TiXmlElement	*elementEvent = elementRoom->FirstChildElement();
        for (bool ok = true; ok && elementEvent; elementEvent = elementEvent->NextSiblingElement())
        {
            Event	myEvent;
            myEvent.setName(elementEvent->Value());
            TiXmlElement	*elementTypeEvent = elementEvent->FirstChildElement();
            for (bool eventOk = true; eventOk && elementTypeEvent; elementTypeEvent = elementTypeEvent->NextSiblingElement())
            {
                std::string	attribut = elementTypeEvent->Value();
                if (attribut == "condition")
                    myEvent.setCondition(elementTypeEvent->GetText());
                else if (attribut == "posX")
                    myEvent.setPosX(strToInt(elementTypeEvent->GetText()));
                else if (attribut == "posY")
                    myEvent.setPosY(strToInt(elementTypeEvent->GetText()));
                else if (attribut == "n" || attribut == "s" || attribut == "e" || attribut == "w")
                    myEvent.setDoor(attribut.at(0));
                if (elementTypeEvent == elementTypeEvent->Parent()->LastChild())
                    eventOk = false;
            }
            //            std::cout << *myEvent << std::endl;
            if (myEvent.getPosX() != -1)
                room->setState("event", myEvent.getPosX(), myEvent.getPosY());
            room->setEvent(myEvent.getPosX(), myEvent.getPosY(), myEvent);
            if (elementEvent == elementEvent->Parent()->LastChild())
                ok = false;
        }

        // DUNGEON : AddRoom
        Room    *tmp = map->getRoom(room->getPosX(), room->getPosY());

        delete tmp;
        map->setRoom(room->getPosX(), room->getPosY(), room);
        // TEST LAST ROOM
        if (elementDungeon == elementDungeon->Parent()->LastChild())
            roomOk = false;
    }
    unserialize_background(path, fileName, map);
    return (map);
}

bool                XMLParse::unserialize_background(const std::string &path, const std::string &fileName, Map *map)
{
    if (!m_xDoc.LoadFile(std::string(path + fileName + ".background").c_str()))
    {
        std::cout << "XML File loading fail : error = "  << m_xDoc.ErrorDesc() << std::endl;
        return (false);
    }
    std::cout << "XML File loading success" << std::endl;
    TiXmlElement* root = this->m_xDoc.FirstChildElement();
    if(root == NULL)
    {
        std::cout << "Failed to load file: No root element."
                  << std::endl;
        this->m_xDoc.Clear();
        return (false);
    }
    int             roomPosX, roomPosY;

    // DUNGEON
    TiXmlElement	*elementDungeon;
    elementDungeon = root->FirstChildElement();
    // DUNGEON : With
    elementDungeon = elementDungeon->NextSiblingElement();
    // DUNGEON : Height
    elementDungeon = elementDungeon->NextSiblingElement();
    // DUNGEON : Rooms
    TiXmlElement	*elementRoom;

    // DUNGEON : Room
    for (bool roomOk = true; roomOk && elementDungeon; elementDungeon = elementDungeon->NextSiblingElement())
    {
        elementRoom = elementDungeon->FirstChildElement();
        roomPosX = (strToInt(elementRoom->GetText()));
        elementRoom = elementRoom->NextSiblingElement();
        roomPosY = (strToInt(elementRoom->GetText()));
        elementRoom = elementRoom->NextSiblingElement();

        int             x, y;
        std::string     texture;

        TiXmlElement	*elementPicture = elementRoom->FirstChildElement();
        for (bool ok = true; ok && elementPicture; elementPicture = elementPicture->NextSiblingElement())
        {
            TiXmlElement	*elementTexture = elementPicture->FirstChildElement();

            for (bool textOk = true; textOk && elementTexture; elementTexture = elementTexture->NextSiblingElement())
            {
                std::string         attribut = elementTexture->Value();

                if (attribut == "posX")
                    x = strToInt(elementTexture->GetText());
                if (attribut == "posY")
                    y = strToInt(elementTexture->GetText());
                if (attribut == "texture")
                    texture = elementTexture->GetText();
                if (elementTexture == elementTexture->Parent()->LastChild())
                    textOk = false;
            }
            Room            *room = map->getRoom(roomPosX, roomPosY);
            MapBox          &box = room->getBox(x, y);

            box.setFirstImage(ImageManager::getSingleton()->getImageByName(QString(texture.c_str())));
            if (elementPicture == elementPicture->Parent()->LastChild())
                ok = false;
        }
        if (elementDungeon == elementDungeon->Parent()->LastChild())
            roomOk = false;
    }
    return (false);
}

