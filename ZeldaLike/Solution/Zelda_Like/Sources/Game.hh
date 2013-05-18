#pragma once

#include	<SFML/Graphics.hpp>
#include	"Enums.h"

#include	"AState.hh"
#include	"Personnage.hh"

class					Game : public AState
{
private:
	bool				_pause;
	sf::Texture			_txMap1;
	sf::Texture			_txMap2;
	sf::Texture			_txMap3;
	sf::Texture			_txLifeBar;
	sf::Texture			_txLife;
	sf::Texture			_txPause;
	sf::Texture			_txDead;

	sf::Sprite			_map;
	sf::Sprite			_LifeBar;
	sf::Sprite			_Life;
	sf::Sprite			_Pause;
	sf::Sprite			_Dead;

	sf::Texture			_txLink;
	Personnage			*_Link;

	char				_room;
	std::map<sf::Keyboard::Key, void (Game::*)()>	_listInput;

public:
	Game(sf::RenderWindow *window, e_state *state);
	~Game(void);

public:
	virtual void	display(float elapsedTime);
	virtual void	keyPressed(sf::Keyboard::Key const & key, float elapsedTime);
	void			lifeControl(void);
	void			pause(void);

private:
	virtual void	close(void);
};

