#include "Intro.hh"

#include <iostream>

Intro::Intro(sf::RenderWindow *window, e_state *state) : AState(window, state)
{
	_music.openFromFile("Ressources/Musics/theme.ogg");
	
	this->_txBackground.loadFromFile("Ressources/Pictures/TitleScreen/Background.png");
	this->_txCloud.loadFromFile("Ressources/Pictures/TitleScreen/Cloud.png");
	this->_txFront.loadFromFile("Ressources/Pictures/TitleScreen/Front.png");
	this->_background.setTexture(_txBackground);
	this->_cloud.setTexture(_txCloud);
	this->_front.setTexture(_txFront);

	this->_textPress = new sf::Text("Press 'enter' to start the game", _font);
	sf::FloatRect textRect = this->_textPress->getLocalBounds();
	this->_textPress->setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
	this->_textPress->setPosition((RESOLUTION_X / 2.f), (RESOLUTION_Y / 2.f));

	this->_listInput[sf::Keyboard::Return] = &Intro::runGame;
	this->_listInput[sf::Keyboard::Escape] = &Intro::close;
}


Intro::~Intro(void)
{
}

void		Intro::textTwinkle(float elapsedTime)
{
	static	float time = 0;

	time += elapsedTime;
	if ((time) > 0.5f)
	{
		if (this->_textPress->getColor().a == 255)
			this->_textPress->setColor(sf::Color(255, 255, 255, 0));
		else
			this->_textPress->setColor(sf::Color::White);
		time = 0;
	}
	this->_window->draw(*this->_textPress);
}


void		Intro::display(float elapsedTime)
{
	if (_cloud.getPosition().x > -RESOLUTION_X)
		_cloud.move(-0.1f, 0);
	else
		_cloud.setPosition(0, 0);

	this->_window->draw(this->_background);
	this->_window->draw(this->_cloud);
	this->_window->draw(this->_front);
	this->textTwinkle(elapsedTime);
	
	
}

void		Intro::keyPressed(sf::Keyboard::Key const & key, float elapsedTime)
{
	if (this->_listInput.find(key) != this->_listInput.end())
		(this->*_listInput[key])();
}

void		Intro::runGame()
{
	_music.stop();
	*(this->_state) = GAME;
}

void		Intro::close()
{
	*(this->_state) = NONE;
}