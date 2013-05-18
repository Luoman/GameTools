#pragma once

#include	<SFML/Graphics.hpp>
#include	<SFML/Audio.hpp>

#include	<iostream>
#include	"Enums.h"

#define			RESOLUTION_X 800.f
#define			RESOLUTION_Y 600.f

class		AState
{

protected:
	sf::RenderWindow	*_window;
	sf::Font			_font;
	sf::Music			_music;
	e_state				*_state;

protected:
	AState(sf::RenderWindow *window, e_state *state)
	{
		_window = window;
		_state = state;
		_font.loadFromFile("Ressources/Font/Triforce.ttf");
	}

public:
	virtual void	display(float elapsedTime) = 0;
	virtual void	keyPressed(sf::Keyboard::Key const & key, float elapsedTime) = 0;
	virtual void	close(void) = 0;

	void			playMusic(){this->_music.play();}
	void			stopMusic(){this->_music.stop();}
	bool			musicIsPlaying(){if (_music.getStatus() == 2) return (true); return(false);}
};