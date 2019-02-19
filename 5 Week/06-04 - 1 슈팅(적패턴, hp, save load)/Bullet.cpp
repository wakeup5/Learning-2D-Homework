#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

HRESULT Bullet::BulletObject::initialize(float startX, float startY, SpriteImage* image)
{
	_startX = startX;
	_startY = startY;

	_image = image;

	setPosition(startX, startY);

	return S_OK;
}
void Bullet::BulletObject::release()
{
	
}
void Bullet::BulletObject::update()
{
	GameObject::activate();
	_image->nextFrame(50);
	_image->setCenter(getX(), getY());
}
void Bullet::BulletObject::render()
{
	_image->render(getMemDC());
}

HRESULT Bullet::initialize(int max, float range, Image* image, int frameCol, int frameRow)
{
	GameNode::initialize();

	_max = max;
	_range = range;

	_image = image;

	_frameCol = frameCol;
	_frameRow = frameRow;

	return S_OK;
}
void Bullet::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet = _vBullet.erase(_viBullet);
	}

	_vBullet.clear();
}

void Bullet::update()
{
	GameNode::update();

	move();
}
void Bullet::render()
{
	draw();
}

void Bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		(*_viBullet)->update();

		//라이프 타임
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
void Bullet::draw()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		(*_viBullet)->render();
	}
}
void Bullet::fire(float startX, float startY, float angleR, float speed)
{
	if (_vBullet.size() < _max)
	{
		Bullet::BulletObject* bullet = new BulletObject;
		SpriteImage* image = _image->getSpriteImage(_frameCol, _frameRow);
		bullet->initialize(startX, startY, image);
		bullet->setAngleR(angleR);
		bullet->setSpeed(speed);

		bullet->setSize(image->getFrameWidth(), image->getFrameHeight());

		_vBullet.push_back(bullet);
	}
}
