#include "stdafx.h"
#include "PieceBullet.h"


PieceBullet::PieceBullet()
{
}


PieceBullet::~PieceBullet()
{
}
HRESULT PieceBullet::initialize(int max, float range, int damage, Image* mImage, Image* image, int mFrameCol, int mFrameRow, int pFrameCol, int pFrameRow)
{
	_bImage = image;
	_pFrameCol = pFrameCol;
	_pFrameRow = pFrameRow;
	return Bullet::initialize(max, range, damage, mImage, mFrameCol, mFrameRow);
}
void PieceBullet::release()
{
	Bullet::release();
}
void PieceBullet::update()
{
	Bullet::update();
}
void PieceBullet::render()
{
	Bullet::render();
}

void PieceBullet::move()
{
	for (_viMB = _vMB.begin(); _viMB != _vMB.end();)
	{
		(*_viMB)->update();
		if (_range < myUtil::getDistanceByTwoPoint((*_viMB)->getStartX(), (*_viMB)->getStartY(), (*_viMB)->getX(), (*_viMB)->getY()))
		{
			for (int i = 0; i < 8; i++)
			{
				Bullet::BulletObject* bullet = new BulletObject;
				SpriteImage* image = _bImage->getSpriteImage(_pFrameCol, _pFrameRow);
				bullet->initialize((*_viMB)->getX(), (*_viMB)->getY(), image);
				bullet->setDamage(_damage);
				bullet->setAngleR(float(i) / 8 * 2 * M_PI);
				bullet->setSpeed(5);

				bullet->setSize(image->getFrameWidth(), image->getFrameHeight());

				_vBullet.push_back(bullet);
			}

			_viMB = _vMB.erase(_viMB);
		}
		else
			_viMB++;
	}

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		(*_viBullet)->update();
		if ((_range / 4 * 3) < myUtil::getDistanceByTwoPoint((*_viBullet)->getStartX(), (*_viBullet)->getStartY(), (*_viBullet)->getX(), (*_viBullet)->getY()))
			_viBullet = _vBullet.erase(_viBullet);
		else
			_viBullet++;
	}
}
void PieceBullet::draw()
{
	for (_viMB = _vMB.begin(); _viMB != _vMB.end(); _viMB++)
	{
		(*_viMB)->render();
	}

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		(*_viBullet)->render();
	}
}
void PieceBullet::fire(float startX, float startY, float angleR, float speed)
{
	if (_vMB.size() < _max)
	{
		Bullet::BulletObject* bullet = new BulletObject;
		SpriteImage* image = _image->getSpriteImage(_frameCol, _frameRow);
		bullet->initialize(startX, startY, image);
		bullet->setDamage(_damage);
		bullet->setAngleR(angleR);
		bullet->setSpeed(speed);

		bullet->setSize(image->getFrameWidth(), image->getFrameHeight());

		_vMB.push_back(bullet);
	}
}

void PieceBullet::popBullet()
{
	for (_viMB = _vMB.begin(); _viMB != _vMB.end();)
	{
		for (int i = 0; i < 8; i++)
		{
			Bullet::BulletObject* bullet = new BulletObject;
			SpriteImage* image = _bImage->getSpriteImage(_pFrameCol, _pFrameRow);
			bullet->initialize((*_viMB)->getX(), (*_viMB)->getY(), image);
			bullet->setDamage(_damage);
			bullet->setAngleR(float(i) / 8 * 2 * M_PI);
			bullet->setSpeed(5);

			bullet->setSize(image->getFrameWidth(), image->getFrameHeight());

			_vBullet.push_back(bullet);
		}

		_viMB = _vMB.erase(_viMB);
	}
}
