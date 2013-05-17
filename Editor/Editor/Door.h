#ifndef	DOOR_H
#define	DOOR_H

#include	<iostream>
#include	<string>

class	Door
{
private:
	char		m_cLocalization;
    std::string	m_sState;

public:
    Door();
    Door(char loc, const std::string &state);
	~Door();

    char		&getLocalization();
    const std::string	&getState() const;
	void		setLocalization(char loc);
    void		setState(const std::string &type);
};

#endif /* DOOR_H */
