#pragma once

#include	<SFML/Graphics.hpp>

#include	"AState.hh"

#include	"Enums.h"

class					Intro : public AState
{
private:
	sf::Texture			_txBackground;
	sf::Texture			_txCloud;
	sf::Texture			_txFront;
	sf::Sprite			_background;
	sf::Sprite			_cloud;
	sf::Sprite			_front;

	sf::Text			*_textPress;

	std::map<sf::Keyboard::Key, void (Intro::*)()>	_listInput;

public:
	Intro(sf::RenderWindow *window, e_state *state);
	~Intro(void);

public:
	virtual void	display(float elapsedTime);
	virtual void	keyPressed(sf::Keyboard::Key const & key, float elapsedTime);

private:
	virtual void	runGame(void);
	virtual void	close(void);

	void			textTwinkle(float elapsedTime);
};

