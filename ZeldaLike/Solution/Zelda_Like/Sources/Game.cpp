#include "Game.hh"


Game::Game(sf::RenderWindow *window, e_state *state) : AState(window, state)
{
	_pause = false;

	_music.openFromFile("Ressources/Musics/gerudo.ogg");
	this->_txMap1.loadFromFile("Ressources/Pictures/map01.png");
	this->_txMap2.loadFromFile("Ressources/Pictures/map02.png");
	this->_txMap3.loadFromFile("Ressources/Pictures/map03.png");
	this->_map.setTexture(_txMap1);
	this->_map.setScale(2.5f, 2.5f);
	this->_map.move(40, 20);

	this->_txLifeBar.loadFromFile("Ressources/Pictures/GameInterface/LifeBar.png");
	this->_LifeBar.setTexture(_txLifeBar);
	this->_LifeBar.setPosition((RESOLUTION_X / 2) - (_LifeBar.getTextureRect().width / 2), 25);

	this->_txLife.loadFromFile("Ressources/Pictures/GameInterface/Life.png");
	this->_Life.setTexture(_txLife);
	this->_Life.setPosition(_LifeBar.getPosition());

	this->_txPause.loadFromFile("Ressources/Pictures/GameInterface/pause.png");
	this->_Pause.setTexture(_txPause);

	this->_txDead.loadFromFile("Ressources/Pictures/GameInterface/dead.png");
	this->_Dead.setTexture(_txDead);

	this->_txLink.loadFromFile("Ressources/Pictures/Link.png");
	this->_Link = new Personnage("Link", this->_txLink, 9, 10);
	
	this->_listInput[sf::Keyboard::P] = &Game::pause;
	this->_listInput[sf::Keyboard::D] = &Game::lifeControl;
	this->_listInput[sf::Keyboard::Escape] = &Game::close;
}


Game::~Game(void)
{
	delete (this->_Link);
}

void		Game::display(float elapsedTime)
{
	if (_room != _Link->_room && !_Link->_isDead)
	{
		_room = _Link->_room;
		if (_Link->_room == 1)
			_map.setTexture(_txMap1);
		else if (_Link->_room == 2)
			_map.setTexture(_txMap2);
		else if (_Link->_room == 3)
			_map.setTexture(_txMap3);
	}
	if (!_pause && !_Link->_isDead)
	{
		float	l = this->_Link->getLife();
		this->_Link->draw(elapsedTime);
		if (l != this->_Link->getLife())
			lifeControl();
	}
	_window->draw(this->_map);
	_window->draw(this->_Link->getApparence());
	_window->draw(this->_LifeBar);
	_window->draw(this->_Life);
	if (_pause)
		_window->draw(this->_Pause);
	if (_Link->_isDead)
		_window->draw(this->_Dead);


}

void		Game::keyPressed(sf::Keyboard::Key const & key, float elapsedTime)
{
	if (this->_listInput.find(key) != this->_listInput.end())
		(this->*_listInput[key])();
	else
		_Link->keyPressed(key, elapsedTime);
}

void		Game::lifeControl()
{
	if (this->_Link->getLife() > 0)
		this->_Life.setTextureRect(sf::IntRect(0, 0, _Life.getTextureRect().width - 10, _Life.getTextureRect().height));
	else
	{
		this->_music.stop();
		_music.openFromFile("Ressources/Musics/fairy.ogg");
		this->_music.play();
		this->_Link->_isDead = true;
	}
}

void		Game::pause()
{
	if (_pause == true)
		_pause = false;
	else
		_pause = true;
}

void		Game::close()
{
	_music.stop();
	_music.openFromFile("Ressources/Musics/gerudo.ogg");
	delete(_Link);
	this->_Life.setTextureRect(sf::IntRect(0, 0, _Life.getTextureRect().width + 50, _Life.getTextureRect().height));
	this->_Link = new Personnage("Link", this->_txLink, 9, 10);
	*(this->_state) = INTRO;
}