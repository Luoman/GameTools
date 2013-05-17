//
// Singleton.hh for  in /home/romuald/Projects/moulitriche
// 
// Made by romuald scharre
// Login   <scharr_r@epitech.net>
// 
// Started on  Tue Jun 19 10:00:35 2012 romuald scharre
// Last update Tue Jun 19 10:00:36 2012 romuald scharre
//

#ifndef			__SINGLETON_HH__
# define		__SINGLETON_HH__

#include		<iostream>

template<typename T>
class			Singleton
{
protected:
  Singleton() {}
  ~Singleton() {}

public:
  static void		initialize()
  {
    _instance = new T;
  }

  static T		*getSingleton()
  {
    if (!_instance)
      _instance = new T ;
    return (static_cast<T*>(_instance));
  }

  static void		dispose()
  {
    if (_instance)
      delete _instance;
    _instance = NULL;
  }


private:
  static T		*_instance;
};

template<typename T>
T				*Singleton<T>::_instance = NULL;

#endif
