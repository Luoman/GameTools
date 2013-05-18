
#ifndef			__ENUMS_H__
# define		__ENUMS_H__

typedef	enum		e_state
{
	NONE,
	INTRO,
	GAME
};

typedef	enum		type_action
  {
    RIEN = 0,
    MARCHER = 200,
    ROULADE = 400,
    ATTAQUER = 600,
	TOMBER = 800,
    PRENDRE,
    PORTER,
    POSER,
    LANCER,
    NAGER,
    PLONGER,
    REMONTER
  }			e_action;

typedef	enum		direction
  {
    HAUT = 120,
    BAS = 0,
    GAUCHE = 40,
    DROITE = 80
  }			e_direction;

#endif
