#pragma once

#include	<SFML/Graphics.hpp>

#include	"Enums.h"

#include	"Intro.hh"
#include	"Game.hh"

class Renderer
{
private:
	sf::RenderWindow	*_window;
	sf::Event			_event;
	sf::Clock			_clock;
	float				_elapsedTime;
	e_state				_state;

	std::map<sf::Event::EventType, void (Renderer::*)()>	_listEvent;
	std::map<sf::Keyboard::Key, void (Renderer::*)()>		_listInput;
	std::map<e_state, void (Renderer::*)()>					_stateEvent;
	std::map<e_state, void (Renderer::*)()>					_stateDisplay;

	Intro				*_intro;
	Game				*_game;

public:
	Renderer(void);
	~Renderer(void);

public:
	void	init(void);
	void	run(void);

private:
	void	events(void);
	
	void	keyPressed(void);
	void	introKeyPressed(void);
	void	gameKeyPressed(void);

	void	display(void);
	void	introDisplay(void);
	void	gameDisplay(void);

	void	close(void);
};

