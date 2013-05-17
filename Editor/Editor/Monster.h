#ifndef	MONSTER_H
#define	MONSTER_H

#include	<iostream>
#include	<string>

class		Monster
{
private:
	std::string	m_sName;
	int			m_iPosX;
	int			m_iPosY;

public:
	Monster();
	~Monster();

	std::string	getName();
	int			getPosX();
	int			getPosY();
	void		setName(std::string name);
	void		setPosX(int x);
	void		setPosY(int y);
};

std::ostream& operator<< (std::ostream &out, Monster &monster);

#endif	/* MONSTER_H */