#include "stdafx.h"
#include "Missile.h"


Missile::Missile()
{
	_width = 10;
	_height = 10;
}


Missile::~Missile()
{
}

void Missile::move()
{
	double radian = _degree * M_PI / 180;
	_point.x = ROUNDING(_point.x - _speed * sin(radian), 0);
	_point.y = ROUNDING(_point.y - _speed * cos(radian), 0);
}
