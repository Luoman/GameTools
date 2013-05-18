#ifndef			__PERSONNAGE_HH__
# define		__PERSONNAGE_HH__

#include		<iostream>
#include		<SFML/Graphics.hpp>

#include		"Macros.h"
#include		"Enums.h"
#include		"Structures.h"

class			Personnage
{
public:
	   char		_room;
		bool	_isDead;
private:
	std::string	_name;
  float			_life;
  int			_vitesse;
  s_action		_action;
  e_action		_preced;
  s_position	_position;
  e_direction	_direction;
  sf::Sprite	_apparence;
  bool			_continue;
  int			_anim_x;
  float			_timer;

  int			_animStep;
  s_position	_spawn;

  std::map<e_action, s_action>							_listAction;
  std::map<sf::Keyboard::Key, e_action>					_listKey;

public:

  Personnage(std::string const &, sf::Texture const &, float, float);
  ~Personnage(void);

  void					initAction();
  void					initInput();

  std::string const &	getName() const;
  float					getLife() const;
  int					getVitesse() const;
  s_action const &		getAction() const;
  e_action				getPreced() const;
  s_position const &	getPosition() const;
  e_direction			getDirection() const;
  sf::Sprite const &	getApparence() const;
  bool					getContinue() const;
  int					getAnim() const;
  float					getTimer() const;

  void					setName(std::string const &);
  void					setLife(float);
  void					setVitesse(int);
  void					setAction(e_action);
  void					setPreced(e_action);
  void					setPosition(s_position const &);
  void					setDirection(e_direction);
  void					setApparence();
  void					setContinue(bool);
  void					setAnim(int);
  void					setTimer(float);

  void					goUp();
  void					goDown();
  void					goLeft();
  void					goRight();

  void					draw(float);
  void					move(e_direction, float, float);
  void					do_action(e_direction, float, e_action);
  //
  bool					checkTheMap(int, int);
  //
  void					keyPressed(sf::Keyboard::Key const &, float);
  void					keyIsPressed(float);
  void					animate(float);

};

#endif
