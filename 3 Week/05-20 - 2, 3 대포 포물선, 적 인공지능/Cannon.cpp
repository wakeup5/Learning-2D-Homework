#include "stdafx.h"
#include "Cannon.h"


Cannon::Cannon()
{
    _position = POINT{100, WIN_SIZE_Y};

    setAngleD(10);

    _size = 70;
    _length = 50;

    setCannonEndPosition();
}


Cannon::~Cannon()
{
}

void Cannon::moveX(int speed)
{
    _position.x += speed;
    setCannonEndPosition();
}
void Cannon::setAngleR(float angleR)
{
    _angleR = angleR;
    _angleD = _angleR * 180 / M_PI;

    setCannonEndPosition();
}
float Cannon::getAngleR()
{
    return _angleR;
}

void Cannon::setAngleD(float angleD)
{
    _angleD = angleD;
    _angleR = _angleD * M_PI / 180;

    setCannonEndPosition();
}
float Cannon::getAngleD()
{
    return _angleD;
}

void Cannon::setCannonEndPosition()
{
    _cannonEndPosition.x = _position.x + _length * cos(_angleR);
    _cannonEndPosition.y = _position.y - _length * sin(_angleR);
}