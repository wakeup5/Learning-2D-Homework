#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::setAngleD(float angleD)
{
    _angleD = angleD;
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

    _angleD = atan2(_speedY, _speedX);
    _angleR = _angleD * M_PI / 180;

    setSpeed(sqrt(pow(_speedX, 2) + pow(_speedY, 2)));
}
float Bullet::getSpeedX()
{
    return _speedX;
}

void Bullet::setSpeedY(float speedY)
{
    _speedY = speedY;

    _angleD = atan2(_speedY, _speedX);
    _angleR = _angleD * M_PI / 180;

    setSpeed(sqrt(pow(_speedX, 2) + pow(_speedY, 2)));
}
float Bullet::getSpeedY()
{
    return _speedY;
}

void Bullet::setSpeed(float speed)
{
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
    setSpeedY(getSpeedY() + 0.2);

    move();
}