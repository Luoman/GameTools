
#include		"Personnage.hh"

#define			RESOLUTION_X 800.f
#define			RESOLUTION_Y 600.f

Personnage::Personnage(std::string const &name, sf::Texture const &Texture, float x, float y)
{
	this->_name = name;
	this->_life = 3.f;
	this->_vitesse = 1;
	this->_action.type = RIEN;
	this->_direction = HAUT;
	this->_position.x = x + 0.5f;
	this->_position.y = y + 0.5f;
	this->_apparence.setTexture(Texture);
	this->_apparence.setTextureRect(sf::IntRect(0, 0, 32, 40));
	this->_apparence.setScale(2.5f, 2.5f);
	this->_apparence.setPosition(x * 40 + 20, y * 40 - 20);
	this->_continue = false;
	this->_anim_x = 0;

	this->_timer = 0;
	this->_animStep = 0;
	this->_spawn = _position;

	this->_isDead = false;
	_room = 1;

	initAction();
	initInput();
}

Personnage::~Personnage()
{
}

////////////////////////
// // // // // INIT
////////////////////////////////////////////

void			Personnage::initAction()
{
	s_action	action;

	this->_listAction[RIEN] = action.init(RIEN, 0.2f, 0);
	this->_listAction[MARCHER] = action.init(MARCHER, 0.05f, 1);
	this->_listAction[ROULADE] = action.init(ROULADE, 0.05f, 2);
	this->_listAction[TOMBER] = action.init(TOMBER, 0.10f, 0);
}

void			Personnage::initInput()
{
	this->_listKey[sf::Keyboard::Space] = ROULADE;
	this->_listKey[sf::Keyboard::Q] = TOMBER;
}

////////////////////////
// // // // // GET
////////////////////////////////////////////

std::string const&	Personnage::getName() const
{
	return (this->_name);
}

float				Personnage::getLife() const
{
	return (this->_life);
}

int					Personnage::getVitesse() const
{
	return (this->_vitesse);
}

s_action const &	Personnage::getAction() const
{
	return (this->_action);
}

e_action			Personnage::getPreced() const
{
	return (this->_preced);
}

s_position const &	Personnage::getPosition() const
{
	return (this->_position);
}

e_direction 		Personnage::getDirection() const
{
	return (this->_direction);
}

sf::Sprite const &	Personnage::getApparence() const
{
	return (this->_apparence);
}

bool				Personnage::getContinue() const
{
	return (this->_continue);
}

int					Personnage::getAnim() const
{
	return (this->_anim_x);
}

float					Personnage::getTimer() const
{
	return (this->_timer);
}

/////////////////////////
// // // // // SET
////////////////////////////////////////////

void			Personnage::setName(std::string const & name)
{
	this->_name = name;
}

void			Personnage::setLife(float life)
{
	this->_life = life;
}

void			Personnage::setVitesse(int vitesse)
{
	this->_vitesse = vitesse;
}

void			Personnage::setAction(e_action action)
{
	this->_preced = this->_action.type;
	this->_action = _listAction[action];
}

void			Personnage::setPreced(e_action action)
{
	this->_preced = action;
}

void			Personnage::setPosition(s_position const & position)
{
	this->_position = position;
}

void			Personnage::setDirection(e_direction direction)
{
	this->_direction = direction;
}

void			Personnage::setApparence()
{
	int			anim_y;

	anim_y = this->_action.type + this->_direction;
	this->_apparence.setTextureRect(sf::IntRect(this->_anim_x, anim_y, TAILLE_X, TAILLE_Y));
}

void			Personnage::setContinue(bool booleen)
{
	this->_continue = booleen;
}

void			Personnage::setAnim(int x)
{
	this->_anim_x = x;
}

void			Personnage::setTimer(float time)
{
	this->_timer = time;
}

////////////////////////
// // // // // Actions
/////////////////////////////////////////////////

void			Personnage::move(e_direction direction, float x, float y)
{
	x *= 200;
	y *= 200;
	this->_direction = direction;

	if (x < 0 && (!checkTheMap((int)(this->_position.x - 0.1f), (int)(this->_position.y - 0.1f)) &&
		!checkTheMap((int)(this->_position.x - 0.1f), (int)(this->_position.y + 0.1f))));
	else if (x > 0 && (!checkTheMap((int)(this->_position.x + 0.1f), (int)(this->_position.y + 0.1f)) &&
		!checkTheMap((int)(this->_position.x + 0.1f), (int)(this->_position.y - 0.1f))));
	else
	{
		this->_position.x += (x / 40.f);
		this->_apparence.move(x, 0);
	}
	if (y < 0 && (!checkTheMap((int)(this->_position.x + 0.1f), (int)(this->_position.y - 0.1f)) &&
		!checkTheMap((int)(this->_position.x - 0.1f), (int)(this->_position.y - 0.1f))));
	else if (y > 0 && (!checkTheMap((int)(this->_position.x + 0.1f), (int)(this->_position.y + 0.1f)) &&
		!checkTheMap((int)(this->_position.x - 0.1f), (int)(this->_position.y + 0.1f))));

	else
	{
		this->_position.y += (y / 40.f);
		this->_apparence.move(0, y);
	}
}

char			tab3[13][18] =
{
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},//0
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},//1
	{'b', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//2
	{'b', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//3
	{'b', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//4
	{'b', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//5
	{'b', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//6
	{'b', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//7
	{'b', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//8
	{'b', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//9
	{'b', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//10
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 's', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},//11
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'}//12
};

char			tab2[13][18] =
{
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},//0
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'n', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},//1
	{'b', 'b', 'h', 'h', 'h', 'h', 'h', 'h', 'h', ' ', 'h', 'h', 'h', 'h', 'h', 'h', 'b', 'b'},//2
	{'b', 'b', 'h', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'h', ' ', ' ', ' ', ' ', 'h', 'b', 'b'},//3
	{'b', 'b', 'h', ' ', 'b', 'h', 'h', 'h', 'h', 'h', 'h', ' ', 'b', 'b', ' ', 'h', 'b', 'b'},//4
	{'b', 'b', 'h', ' ', ' ', 'h', 'h', 'h', 'h', 'h', 'h', ' ', ' ', 'b', ' ', 'h', 'b', 'b'},//5
	{'b', 'b', 'h', 'b', ' ', 'h', 'h', ' ', ' ', ' ', 'b', 'b', ' ', 'b', ' ', 'h', 'b', 'b'},//6
	{'b', 'b', 'h', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', ' ', ' ', 'h', ' ', 'h', 'b', 'b'},//7
	{'b', 'b', 'h', ' ', 'b', ' ', ' ', ' ', 'b', ' ', ' ', ' ', 'h', 'h', ' ', 'h', 'b', 'b'},//8
	{'b', 'b', 'h', ' ', ' ', ' ', 'h', 'h', 'h', 'h', 'h', 'h', 'h', ' ', ' ', 'h', 'b', 'b'},//9
	{'b', 'b', 'h', 'h', 'h', 'h', 'h', 'h', 'h', ' ', ' ', ' ', ' ', ' ', 'h', 'h', 'b', 'b'},//10
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 's', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},//11
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'}//12
};

char			tab1[13][18] =
{
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},//0
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'n', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},//1
	{'b', 'b', 'h', ' ', ' ', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'h', 'b', 'b'},//2
	{'b', 'b', ' ', ' ', ' ', 'b', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//3
	{'b', 'b', ' ', 'b', ' ', ' ', 'b', 'b', ' ', ' ', ' ', ' ', ' ', 'b', ' ', ' ', 'b', 'b'},//4
	{'b', 'b', ' ', 'b', ' ', ' ', ' ', 'b', ' ', 'h', 'h', 'b', ' ', 'b', 'b', ' ', 'b', 'b'},//5
	{'b', 'b', ' ', 'b', ' ', ' ', ' ', ' ', ' ', 'h', 'h', 'b', ' ', ' ', 'b', 'b', 'b', 'b'},//6
	{'b', 'b', ' ', 'b', 'b', ' ', ' ', ' ', ' ', 'h', 'h', 'b', ' ', ' ', ' ', ' ', 'b', 'b'},//7
	{'b', 'b', ' ', ' ', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//8
	{'b', 'b', ' ', ' ', ' ', ' ', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'b', 'b'},//9
	{'b', 'b', 'h', ' ', ' ', ' ', 'b', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'h', 'b', 'b'},//10
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},//11
	{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'}//12
};

bool			Personnage::checkTheMap(int i, int j)
{
	char c;

	if (_room == 1)
		c = tab1[j][i];
	else if (_room == 2)
		c = tab2[j][i];
	else if (_room == 3)
		c = tab3[j][i];

	switch(c)
	{
		case 'h':
			this->_apparence.setPosition((float) i * 40 + 20 , (float) j * 40);
			this->_position.x = i - 0.1f;
			this->_position.y = j - 0.1f;
			this->_life -= 0.5f;
			this->setAnim(0);
			this->_animStep = 0;
			this->_continue = true;
			this->_action.type =TOMBER;
			return (false);
		case 'b':
			return (false);
		case 'n':
			_room += 1;
			this->_spawn.x = 9.5f;
			this->_spawn.y = 11.5f;
			this->_position = this->_spawn;
			this->_apparence.setPosition(_spawn.x * 40, _spawn.y * 40 - 40);
		case 's':
			if (_direction != BAS)
				return (true);
			_room -= 1;
			this->_spawn.x = 9.5f;
			this->_spawn.y = 2.5f;
			this->_position = this->_spawn;
			this->_apparence.setPosition(_spawn.x * 40, _spawn.y * 40 - 40);
		}
	return (true);
}

void			Personnage::do_action(e_direction direction, float time, e_action action)
{
	float x = 0;
	float y = 0;

	switch (direction)
	{
	case HAUT:
		y = -_listAction[action].speed * time;
		break;
	case BAS:
		y = _listAction[action].speed * time;
		break;
	case GAUCHE:
		x = -_listAction[action].speed * time;
		break;
	case DROITE:
		x = _listAction[action].speed * time;
		break;
	}
	this->setAction(action);
	this->move(direction, x, y);
}

////////////////////////////////////////////////

void			Personnage::draw(float elapsedTime)
{
	if (this->_continue)
		this->do_action(this->getDirection(), elapsedTime, getAction().type);
	keyIsPressed(elapsedTime);	
	animate(elapsedTime);
	setApparence();
}

void		Personnage::keyPressed(sf::Keyboard::Key const &key, float elapsedTime)
{
	if (this->_listKey.find(key) != this->_listKey.end() && !this->_continue)
	{
		this->setAnim(0);
		this->_animStep = 0;
		this->_continue = true;
		this->_action.type = this->_listKey[key];
	}

}

void			Personnage::keyIsPressed(float elapsedTime)
{
	if (!this->getContinue())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->setAction(MARCHER);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				this->move(HAUT, 0, -elapsedTime);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				this->move(BAS, 0, elapsedTime);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				this->move(GAUCHE, -elapsedTime, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				this->move(DROITE, elapsedTime, 0);
		}
		else
			this->setAction(RIEN);
	}
}

void			Personnage::animate(float elapsedTime)
{
	if (this->_timer >= this->getAction().time)
	{
		if (++this->_animStep >= 10 || this->getPreced() != this->getAction().type)
		{
			this->setAnim(0);
			this->_animStep = 0;
			this->setPreced(this->getAction().type);
			this->setContinue(false);

			if (this->getAction().type == TOMBER)
			{
				this->_apparence.setPosition(_spawn.x * 40, _spawn.y * 40 - 40);
				this->_position = this->_spawn;
			}
		}
		else
			this->setAnim(this->_animStep * 32);
		this->_timer = 0;
	}
	else
		this->_timer += elapsedTime;
}