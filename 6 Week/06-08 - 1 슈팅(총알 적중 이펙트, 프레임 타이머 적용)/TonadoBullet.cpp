#include "stdafx.h"
#include "TonadoBullet.h"


TonadoBullet::TonadoBullet()
{
}


TonadoBullet::~TonadoBullet()
{
}

HRESULT TonadoBullet::initialize(int max, float range, int damage, Image* image, int frameCol, int frameRow)
{
	return Bullet::initialize(max, range, damage, image, frameCol, frameRow);
}
void TonadoBullet::release()
{
	Bullet::release();
}
void TonadoBullet::update()
{
	Bullet::update();
}
void TonadoBullet::render()
{
	Bullet::render();
}

void TonadoBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{	
		(*_viBullet)->setAngleD((*_viBullet)->getAngleD() + 10);
		(*_viBullet)->setSpeed((*_viBullet)->getSpeed() + 0.1);
		(*_viBullet)->setY((*_viBullet)->getY() - 3);
		(*_viBullet)->update();

		if (_range < myUtil::getDistanceByTwoPoint((*_viBullet)->getStartX(), (*_viBullet)->getStartY(), (*_viBullet)->getX(), (*_viBullet)->getY()))
		{
			//SAFE_RELEASE(_viBullet->image);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			_viBullet++;
		}
	}
}


