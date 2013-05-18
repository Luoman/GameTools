
#ifndef			__MACROS_H__
# define		__MACROS_H__

# define		TAILLE_X 32
# define		TAILLE_Y 40

# define		CONTROL			\
  (Input.IsKeyDown(sf::Key::Up)		||	\
   Input.IsKeyDown(sf::Key::Down)	||	\
   Input.IsKeyDown(sf::Key::Left)	||	\
   Input.IsKeyDown(sf::Key::Right))	&&	\
  !(Input.IsKeyDown(sf::Key::Up)	&&	\
    Input.IsKeyDown(sf::Key::Down))	&&	\
  !(Input.IsKeyDown(sf::Key::Left)	&&	\
    Input.IsKeyDown(sf::Key::Right))

# define		CONTINUE		\
  action	==	ROULADE		||	\
  action	==	ATTAQUER

#endif
