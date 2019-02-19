#include "stdafx.h"
#include "Bullet.h"

#define GRAVITY_ACCEL 0.2

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::setAngleD(float angleD)
{
	_angleD = angleD;
	while (_angleD < 0)
	{
		_angleD += 360;
	}
	while (_angleD > 360)
	{
		_angleD -= 360;
	}

	_angleR = _angleD * M_PI / 180;

	_speedX = _speed * cos(_angleR);
	_speedY = -_speed * sin(_angleR);
}
float Bullet::getAngleD()
{
	return _angleD;
}

void Bullet::setAngleR(float angleR)
{
	_angleR = angleR;
	while (_angleR < 0)
	{
		_angleR += 2 * M_PI;
	}
	while (_angleR > 2 * M_PI)
	{
		_angleR -= 2 * M_PI;
	}

	_angleD = _angleR * 180 / M_PI;

	_speedX = _speed * cos(_angleR);
	_speedY = -_speed * sin(_angleR);
}
float Bullet::getAngleR()
{
	return _angleR;
}

void Bullet::setSpeedX(float speedX)
{
	_speedX = speedX;

	_angleR = atan2(-_speedY, _speedX);
	_angleD = _angleR * 180 / M_PI;

	_speed = (sqrt(pow(_speedX, 2) + pow(_speedY, 2)));
}
float Bullet::getSpeedX()
{
	return _speedX;
}

void Bullet::setSpeedY(float speedY)
{
	_speedY = speedY;

	_angleR = atan2(-_speedY, _speedX);
	_angleD = _angleR * 180 / M_PI;

	_speed = (sqrt(pow(_speedX, 2) + pow(_speedY, 2)));
}
float Bullet::getSpeedY()
{
	return _speedY;
}

void Bullet::setSpeed(float speed)
{
	if (speed < 0)
	{
		speed = speed * -1;
		setAngleD(getAngleD() + 180);
	}

	_speed = speed;

	_speedX = _speed * cos(_angleR);
	_speedY = -_speed * sin(_angleR);
}
float Bullet::getSpeed()
{
	return _speed;
}

void Bullet::move()
{
	_positionX += _speedX;
	_positionY += _speedY;
}

void Bullet::moveGravity()
{
	setSpeedY(getSpeedY() + GRAVITY_ACCEL);

	move();
}