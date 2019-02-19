#include "stdafx.h"
#include "GuideMissile.h"


GuideMissile::GuideMissile()
{
}


GuideMissile::~GuideMissile()
{
}

void GuideMissile::guideMove()
{
	if (_enemy != NULL && _enemy->getIsLive())
	{
		double radian = atan2(_point.x - _enemy->getPosition().x, _point.y - _enemy->getPosition().y);
		double degree = radian * 180 / M_PI;
		if (radian <= 0)
		{
			if (_degree < degree - 0.001) _degree = degree;
			else _degree -= 20;
		}
		else if (radian > 0)
		{
			if (_degree > degree + 0.001) _degree = degree;
			else _degree += 20;
		}
	}
	
	double mRadian = _degree * M_PI / 180;

	_point.x = ROUNDING(_point.x - _speed * sin(mRadian), 0);
	_point.y = ROUNDING(_point.y - _speed * cos(mRadian), 0);
}