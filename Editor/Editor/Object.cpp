#include	"Object.h"

Object::Object()
    : m_sName("null"), m_iPosX(0), m_iPosY(0), m_sType("block"), m_sItem("null"), m_bVisible(true)
{

}

Object::~Object()
{

}

std::string	Object::getName()
{
    return (this->m_sName);
}

std::string	Object::getType()
{
	return (this->m_sType);
}

std::string	Object::getItem()
{
	return (this->m_sItem);
}

int			Object::getPosX()
{
	return (this->m_iPosX);
}

int			Object::getPosY()
{
	return (this->m_iPosY);
}

bool		Object::getVisible()
{
	return (this->m_bVisible);
}

std::string	Object::getVisibleTxt()
{
	if (this->m_bVisible)
		return ("true");
	else
		return ("false");
}

void		Object::setName(std::string name)
{
	this->m_sName = name;
}

void		Object::setType(std::string type)
{
	this->m_sType = type;
}

void		Object::setItem(std::string item)
{
	this->m_sItem = item;
}

void		Object::setPosX(int x)
{
	this->m_iPosX = x;
}

void		Object::setPosY(int y)
{
	this->m_iPosY = y;
}

void		Object::setVisible(bool visible)
{
	this->m_bVisible = visible;
}

void		Object::setVisibleTxt(std::string visible)
{
	if (visible == "true")
		this->m_bVisible = true;
	else
		this->m_bVisible = false;
}

std::ostream& operator<< (std::ostream &out, Object &object)
{
	out << "(" << object.getName() << ", " <<
		object.getType() << ", " <<
		object.getPosX() << "," <<
		object.getPosY() << "," <<
		object.getItem() << "," <<
		object.getVisibleTxt() << ")";
    return out;
}
