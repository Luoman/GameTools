#include	"Monster.h"

Monster::Monster()
{

}

Monster::~Monster()
{

}

std::string	Monster::getName()
{
	return (this->m_sName);
}

int			Monster::getPosX()
{
	return (this->m_iPosX);
}

int			Monster::getPosY()
{
	return (this->m_iPosY);
}

void		Monster::setName(std::string name)
{
	this->m_sName = name;
}

void		Monster::setPosX(int x)
{
	this->m_iPosX = x;
}

void		Monster::setPosY(int y)
{
	this->m_iPosY = y;
}

std::ostream& operator<< (std::ostream &out, Monster &monster)
{
	out << "(" << monster.getName() << ", " <<
		monster.getPosX() << "," <<
		monster.getPosY() << ")";
    return out;
}
