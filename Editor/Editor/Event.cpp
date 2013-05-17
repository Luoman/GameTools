#include	"Event.h"

Event::Event()
    : m_sName("null"), m_sCondition("null"), m_iPosX(-1), m_iPosY(-1)
{

}

Event::~Event()
{

}

std::string		Event::getCondition()
{
	return (this->m_sCondition);
}

std::string		Event::getName()
{
	return (this->m_sName);
}

int				Event::getPosX()
{
	return (this->m_iPosX);
}

int				Event::getPosY()
{
	return (this->m_iPosY);
}

std::list<char>		&Event::getDoors()
{
    return (this->m_lDoors);
}

void			Event::setCondition(std::string condition)
{
	this->m_sCondition = condition;
}

void			Event::setName(std::string name)
{
	this->m_sName = name;
}

void			Event::setPosX(int x)
{
	this->m_iPosX = x;
}

void			Event::setPosY(int y)
{
	this->m_iPosY = y;
}

void			Event::setDoor(char loc)
{
    this->m_lDoors.push_back(loc);
}

//std::ostream& operator<< (std::ostream &out, Event &myEvent)
//{
//	out << "(" << myEvent.getName() << ", " <<
//		myEvent.getCondition() << "," <<
//		myEvent.getPosX() << "," <<
//		myEvent.getPosY() << ",door(";
//	std::map<char, Door*>::iterator	it = myEvent.getDoors().begin();
//	for (it = myEvent.getDoors().begin(); it != myEvent.getDoors().end(); ++it)
//		out << it->second->getLocalization() << ",";
//	out << "))";
//	return out;
//}
