#ifndef	EVENT_H
#define	EVENT_H

#include	<iostream>
#include	<string>
#include	<list>

class		Event
{
private:
	std::string	m_sName;
	std::string	m_sCondition;
	int			m_iPosX;
	int			m_iPosY;
    std::list<char>	m_lDoors;

public:
	Event();
	~Event();

	std::string	getName();
	std::string	getCondition();
	int			getPosX();
	int			getPosY();
    std::list<char>	&getDoors();
	void		setCondition(std::string condition);
	void		setName(std::string name);
	void		setPosX(int x);
	void		setPosY(int y);
    void		setDoor(char loc);
};

//std::ostream& operator<< (std::ostream &out, Event &myEvent);

#endif	/* EVENT_H */
