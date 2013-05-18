#include "Renderer.hh"

Renderer::Renderer(void)
{
	this->_state = INTRO;
	this->_elapsedTime = 0;
	_listEvent[sf::Event::Closed] = &Renderer::close;
	_listEvent[sf::Event::KeyPressed] = &Renderer::keyPressed;

	//_listInput[sf::Key::Escape] = &Renderer::close;

	_stateEvent[INTRO] = &Renderer::introKeyPressed;
	_stateEvent[GAME] = &Renderer::gameKeyPressed;

	_stateDisplay[NONE] = &Renderer::close;
	_stateDisplay[INTRO] = &Renderer::introDisplay;
	_stateDisplay[GAME] = &Renderer::gameDisplay;
}


Renderer::~Renderer(void)
{
}

void		Renderer::init(void)
{
	this->_window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Zelda Like");
	//this->_window->Create(sf::VideoMode::GetMode(0), "SFML Window", sf::Style::Fullscreen);
	this->_intro = new Intro(_window, &(this->_state));
	this->_game = new Game(_window, &(this->_state));
}

void		Renderer::run(void)
{
	this->_intro->playMusic();
	while (this->_window->isOpen())
	{
		this->events();
		this->_elapsedTime = this->_clock.restart().asSeconds();
		this->_window->clear();
		this->display();
		this->_window->display();
	}
}

void		Renderer::events(void)
{
	while (this->_window->pollEvent(this->_event))
	{
		if (this->_listEvent.find(this->_event.type) != this->_listEvent.end())
			(this->*_listEvent[this->_event.type])();
	}
}

void		Renderer::keyPressed(void)
{
	if (this->_stateEvent.find(this->_state) != this->_stateEvent.end())
		(this->*_stateEvent[this->_state])();
}

void		Renderer::introKeyPressed(void)
{
	this->_intro->keyPressed(this->_event.key.code, this->_elapsedTime);
}

void		Renderer::gameKeyPressed(void)
{
	this->_game->keyPressed(this->_event.key.code, this->_elapsedTime);
}

void		Renderer::display(void)
{
	if (this->_stateDisplay.find(this->_state) != this->_stateDisplay.end())
		(this->*_stateDisplay[_state])();
}

void		Renderer::introDisplay(void)
{
	if (this->_intro->musicIsPlaying() == false)
		this->_intro->playMusic();
	this->_intro->display(this->_elapsedTime);
}

void		Renderer::gameDisplay(void)
{
	if (this->_game->musicIsPlaying() == false)
		this->_game->playMusic();
	this->_game->display(this->_elapsedTime);
}

void		Renderer::close(void)
{
	this->_window->close();
}