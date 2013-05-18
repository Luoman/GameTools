
#ifndef			__STRUCTURES_H__
# define		__STRUCTURES_H__

typedef	struct		action
{
	action			init(e_action _type, float _time, float _speed)
	{
		action		a;
		a.type = _type;
		a.time = _time;
		a.speed = _speed;

		return (a);
	};
	e_action		type;
	float			time;
	float			speed;
}					s_action;

typedef	struct		position
{
  float			x;
  float			y;
}			s_position;

#endif
