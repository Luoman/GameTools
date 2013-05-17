#include	"Door.h"

Door::Door()
{

}

Door::Door(char loc, const std::string &state)
    : m_cLocalization(loc), m_sState(state)
{

}

Door::~Door()
{

}

char	&Door::getLocalization()
{
	return (this->m_cLocalization);
}

const std::string	&Door::getState() const
{
    return (this->m_sState);
}

void		Door::setLocalization(char loc)
{
	this->m_cLocalization = loc;
}

void		Door::setState(const std::string &state)
{
    this->m_sState = state;
}
