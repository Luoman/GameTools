#ifndef	OBJECT_H
#define	OBJECT_H

#include	<iostream>
#include	<string>

class		Object
{
private:
	std::string	m_sName;
	int			m_iPosX;
	int			m_iPosY;
	std::string	m_sType;
	std::string	m_sItem;
	bool		m_bVisible;

public:
	Object();
	~Object();
	
	std::string	getName();
	std::string	getType();
	std::string	getItem();
	int			getPosX();
	int			getPosY();
	bool		getVisible();
	std::string	getVisibleTxt();
	void		setName(std::string name);
	void		setType(std::string Type);
	void		setItem(std::string Item);
	void		setPosX(int x);
	void		setPosY(int y);
	void		setVisible(bool visible);
	void		setVisibleTxt(std::string visible);
};

std::ostream& operator<< (std::ostream &out, Object &object);

#endif	/* OBJECT_H */