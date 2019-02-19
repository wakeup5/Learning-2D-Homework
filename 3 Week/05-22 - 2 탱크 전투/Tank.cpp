#include "stdafx.h"
#include "Tank.h"


Tank::Tank()
{
}


Tank::~Tank()
{
}

void Tank::moveFront()
{
    _x += _speed * cos(_angleR);
    _y -= _speed * sin(_angleR);
}

void Tank::moveBack()
{
    _x -= _speed * cos(_angleR);
    _y += _speed * sin(_angleR);
}

void Tank::printTank(HDC hdc)
{
    //≈ ≈© ∏ˆ≈Î
    float px1, py1, px2, py2, px3, py3, px4, py4, pfx, pfy;
    float pAngle1, pAngle2, pAngle3, pAngle4;

    pAngle1 = _angleR - (30 * M_PI / 180);
    pAngle2 = _angleR + (30 * M_PI / 180);
    pAngle3 = _angleR + (150 * M_PI / 180);
    pAngle4 = _angleR - (150 * M_PI / 180);

    px1 = _x + _size * cos(pAngle1);
    py1 = _y - _size * sin(pAngle1);

    px2 = _x + _size * cos(pAngle2);
    py2 = _y - _size * sin(pAngle2);

    px3 = _x + _size * cos(pAngle3);
    py3 = _y - _size * sin(pAngle3);

    px4 = _x + _size * cos(pAngle4);
    py4 = _y - _size * sin(pAngle4);

    pfx = _x + _size * cos(_angleR);
    pfy = _y - _size * sin(_angleR);

    drawLine(hdc, px1, py1, px2, py2);
    drawLine(hdc, px2, py2, px3, py3);
    drawLine(hdc, px3, py3, px4, py4);
    drawLine(hdc, px4, py4, px1, py1);
    drawLine(hdc, _x, _y, pfx, pfy);

    //≈ ≈© ∆˜≈æ
    float cannonEndX, cannonEndY;

    cannonEndX = _x + _cannonSize * cos(_cannonAngleR);
    cannonEndY = _y - _cannonSize * sin(_cannonAngleR);

    drawLine(hdc, _x, _y, cannonEndX, cannonEndY);
    drawEllipseCenter(hdc, _x, _y, _size / 2, _size / 2);
}