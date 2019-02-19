#include "stdafx.h"
#include "Bullets.h"

using namespace myUtil;

Bullets::Bullets()
{
}


Bullets::~Bullets()
{

}

void Bullets::initialize(SpriteImage* image, float range, float max)
{
	_bulletImage = image;
	_range = range;
	_max = max;

	_lBullet = new list<Bullet*>;
}
void Bullets::release()
{
	SAFE_RELEASE(_bulletImage);
	for (_liBullet = _lBullet->begin(); _liBullet != _lBullet->end();)
	{
		SAFE_RELEASE(*_liBullet);
		_liBullet = _lBullet->erase(_liBullet);
	}

	SAFE_DELETE(_lBullet);
}
void Bullets::update()
{
	Bullet* b;
	for (_liBullet = _lBullet->begin(); _liBullet != _lBullet->end();)
	{
		b = (*_liBullet);
		b->update();

		if (getDistance(b->getX(), b->getY(), b->getStartX(), b->getStartY()) > _range)
		{
			_liBullet = _lBullet->erase(_liBullet);
		}
		else
		{
			++_liBullet;
		}
	}
}
void Bullets::render()
{
	for (_liBullet = _lBullet->begin(); _liBullet != _lBullet->end(); ++_liBullet)
	{
		(*_liBullet)->render(getMemDC());
	}
}

void Bullets::fire(float startX, float startY, float angle, float speed, void(*moveFunc)(GameObject*))
{
	Bullet* bullet = new Bullet(_bulletImage, startX, startY, angle, speed, moveFunc);

	_lBullet->push_back(bullet);
}

void Bullets::fire(SpriteImage* image, float startX, float startY, float angle, float speed, void(*moveFunc)(GameObject*))
{
	Bullet* bullet = new Bullet(image, startX, startY, angle, speed, moveFunc);

	_lBullet->push_back(bullet);
}

void Bullets::fire(Bullets::Bullet* bullet)
{
	_lBullet->push_back(bullet);
}

Bullets::Bullet* Bullets::createBullet(SpriteImage* image, float startX, float startY, float angle, float speed, void(*moveFunc)(GameObject*))
{
	return new Bullet(image, startX, startY, angle, speed, moveFunc);
}

Bullets::Bullet::Bullet(SpriteImage* image, float startX, float startY, float angle, float speed, void(*moveFunc)(GameObject*))
{
	_image = new SpriteImage(*image);
	_moveFunc = moveFunc;
	_startX = startX;
	_startY = startY;

	GameObject::initialize(startX, startY, image->getFrameWidth(), image->getFrameHeight(), degFromRad(angle), speed);

	_timer = TIMEMANAGER->addTimer();
}

Bullets::Bullet::~Bullet()
{

}

void Bullets::Bullet::release()
{
	SAFE_RELEASE(_image);
}
void Bullets::Bullet::update()
{
	activate();
	_image->setCenter(getX(), getY());

	float insertAngle = 180.0f / (_image->getMaxFrameX() + 1); // (360 / X) / 2;

	_image->setFrameX((getAngleD() + insertAngle) / 360.0f * (_image->getMaxFrameX() + 1));

	if (_timer->checkTime(100 / getSpeed()))
	{
		if (_image->getFrameY() == _image->getMaxFrameY() - 1) _image->setFrameY(0);
		_image->nextFrameY();
	}
	if (_moveFunc != NULL) _moveFunc(this);
}
void Bullets::Bullet::render(HDC hdc)
{
	_image->render(hdc);
}