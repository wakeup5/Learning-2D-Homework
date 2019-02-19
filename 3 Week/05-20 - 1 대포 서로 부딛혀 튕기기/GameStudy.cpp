#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();

	_cannon.angle = 90;
	_cannon.length = 70;
	_cannon.radius = 50;
	_cannon.center.x = WIN_SIZE_X / 2;
	_cannon.center.y = WIN_SIZE_Y;

	for (int i = 0; i < MAX_MISSILE; i++)
	{
		_missiles[i].angleRadian = M_PI / 2;
		_missiles[i].speed = MISSILE_SPEED;
		_missiles[i].radius = MISSILE_SIZE;
		_missiles[i].isFire = false;
	}

    //_bullet[0].setPosition(POINT{ WIN_SIZE_X / 2, WIN_SIZE_Y / 2 });
    //_bullet[0].isFire = true;

    /*
    float x;
    float y;
    float size = MISSILE_SIZE + 2;
    //첫번째줄
    for (int i = 0, k = 0; i < 5; i++)
    {
        x = (WIN_SIZE_X / 2) - 2 * size + (i * size / 2);
        y = 200 + (sqrt(3) / 2 * size) * i;
        for (int j = 0; j < 5 - i; j++)
        {
            _bullet[k].setPosition(POINT{ x, y });
            _bullet[k].isFire = true;
            x += size;
            k++;
        }
    }
    */

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

	//대포 각도
	if (_cannon.angle < 170 && KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_cannon.angle += 1;
	}

	if (_cannon.angle > 10 && KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cannon.angle -= 1;
	}

	_cannon.angleRadian = _cannon.angle * M_PI / 180;
	_cannon.cannonEnd.x = _cannon.center.x + _cannon.length * cos(_cannon.angleRadian);
	_cannon.cannonEnd.y = _cannon.center.y - _cannon.length * sin(_cannon.angleRadian);

    /*
	//미사일 발사
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

		for (int i = 0; i < MAX_MISSILE; i++)
		{
			if (!_missiles[i].isFire)
			{
				_missiles[i].px = _cannon.cannonEnd.x;
				_missiles[i].py = _cannon.cannonEnd.y;
				_missiles[i].angle = _cannon.angle;
				_missiles[i].isFire = true;
				break;
			}
		}
	}
	//미사일 움직임
	for (int i = 0; i < MAX_MISSILE; i++)
	{
		if (_missiles[i].isFire)
		{
			_missiles[i].angleRadian = _missiles[i].angle * M_PI / 180;
			_missiles[i].px += _missiles[i].speed * cos(_missiles[i].angleRadian);
			_missiles[i].py -= _missiles[i].speed * sin(_missiles[i].angleRadian);
		}
	}

	//미사일 충돌처리
	for (int i = 0; i < MAX_MISSILE; i++)
	{
		if (_missiles[i].px < 0)// && _missiles[i].angle > 90 && _missiles[i].angle < 270)
		{
			//_missiles[i].isFire = false; //1번숙제
			_missiles[i].angle = 180 - _missiles[i].angle;//(_missiles[i].angle <= 180 ? -180 : 540);
            _missiles[i].px = 0;
		}

		if (_missiles[i].px > WIN_SIZE_X)// && !(_missiles[i].angle > 90 && _missiles[i].angle < 270))
		{
			//_missiles[i].isFire = false; //1번숙제
			_missiles[i].angle = 180 - _missiles[i].angle;//(_missiles[i].angle <= 180 ? 180 : -540);
            _missiles[i].px = WIN_SIZE_X;
		}

		if (_missiles[i].py < 0)
		{
			//_missiles[i].isFire = false; //1번숙제
			_missiles[i].angle = 360 - _missiles[i].angle;
            _missiles[i].py = 0;
		}

		if (_missiles[i].py > WIN_SIZE_Y)
		{
			//_missiles[i].isFire = false; //1번숙제
			_missiles[i].angle = 360 - _missiles[i].angle;
            _missiles[i].py = WIN_SIZE_Y;
		}

		/*
		while (_missiles[i].angle <= 0)
		{
		_missiles[i].angle += 360;
		}
		while (_missiles[i].angle >= 360)
		{
		_missiles[i].angle -= 360;
		}
		*

	}

    
    float temp;
    float px1, px2, py1, py2;
    //공끼리 충돌
    for (int i = 0; i < MAX_MISSILE; i++)
    {
        if (!_missiles[i].isFire) continue;
        px1 = _missiles[i].px + _missiles[i].speed * cos(_missiles[i].angleRadian);
        py1 = _missiles[i].py - _missiles[i].speed * sin(_missiles[i].angleRadian);
        for (int j = i; j < MAX_MISSILE; j++)
        {
            if (i == j) continue;
            if (!_missiles[j].isFire) continue;

            px2 = _missiles[j].px + _missiles[j].speed * cos(_missiles[j].angleRadian);
            py2 = _missiles[j].py - _missiles[j].speed * sin(_missiles[j].angleRadian);

            RECT c1 = makeRectCenter(px1, py1, MISSILE_SIZE, MISSILE_SIZE);
            RECT c2 = makeRectCenter(px2, py2, MISSILE_SIZE, MISSILE_SIZE);

            if (isCollisionCircle(c1, c2))
            {
                //원 충돌 처리
                temp = _missiles[i].angle;
                _missiles[i].angle = _missiles[j].angle;
                _missiles[j].angle = temp;
            }
        }
    }


	if (KEYMANAGER->isStayKeyDown('1'))
	{
		for (int i = 0; i < MAX_MISSILE; i++)
		{
			_missiles[i].isFire = false;
		}
	}
    */

    //미사일 발사
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {

        for (int i = 0; i < MAX_MISSILE; i++)
        {
            if (!_bullet[i].isFire)
            {
                _bullet[i].setPosition(_cannon.cannonEnd);
                _bullet[i].setAngleD(_cannon.angle);
                _bullet[i].setSpeed(MISSILE_SPEED);
                _bullet[i].isFire = true;
                break;
            }
        }
    }
    //미사일 움직임
    for (int i = 0; i < MAX_MISSILE; i++)
    {
        if (_bullet[i].isFire)
        {
            _bullet[i].move();
        }
    }

    //미사일 충돌처리
    for (int i = 0; i < MAX_MISSILE; i++)
    {
        if (_bullet[i].getPositionX() < 0)// && _missiles[i].angle > 90 && _missiles[i].angle < 270)
        {
            //_missiles[i].isFire = false; //1번숙제
            _bullet[i].setAngleD(180 - _bullet[i].getAngleD());//(_missiles[i].angle <= 180 ? -180 : 540);
            //_bullet[i].setSpeedX(_bullet[i].getSpeedX() * -1);
            _bullet[i].setPosition(POINT{ 0, _bullet[i].getPositionY() });
        }

        if (_bullet[i].getPositionX() > WIN_SIZE_X)// && !(_missiles[i].angle > 90 && _missiles[i].angle < 270))
        {
            //_missiles[i].isFire = false; //1번숙제
            _bullet[i].setAngleD(180 - _bullet[i].getAngleD());//(_missiles[i].angle <= 180 ? 180 : -540);
            //_bullet[i].setSpeedX(_bullet[i].getSpeedX() * -1);
            _bullet[i].setPosition(POINT{ WIN_SIZE_X, _bullet[i].getPositionY() });
        }

        if (_bullet[i].getPositionY() < 0)
        {
            //_missiles[i].isFire = false; //1번숙제
            _bullet[i].setAngleD(360 - _bullet[i].getAngleD());
            //_bullet[i].setSpeedY(_bullet[i].getSpeedY() * -1);
            _bullet[i].setPosition(POINT{ _bullet[i].getPositionX(), 0 });
        }

        if (_bullet[i].getPositionY() > WIN_SIZE_Y)
        {
            //_missiles[i].isFire = false; //1번숙제
            _bullet[i].setAngleD(360 - _bullet[i].getAngleD());
            //_bullet[i].setSpeedY(_bullet[i].getSpeedY() * -1);
            _bullet[i].setPosition(POINT{ _bullet[i].getPositionX(),  WIN_SIZE_Y });
        }

        /*
        while (_missiles[i].angle <= 0)
        {
        _missiles[i].angle += 360;
        }
        while (_missiles[i].angle >= 360)
        {
        _missiles[i].angle -= 360;
        }
        */

    }


    float temp;
    float px1, px2, py1, py2;
    //공끼리 충돌
    for (int i = 0; i < MAX_MISSILE; i++)
    {
        if (!_bullet[i].isFire) continue;
        for (int j = i + 1; j < MAX_MISSILE; j++)
        {
            //if (i == j) continue;
            if (!_bullet[j].isFire) continue;

            if (isCollisionCircle(
                makeRectCenter(_bullet[i].getPosition(), MISSILE_SIZE, MISSILE_SIZE), 
                makeRectCenter(_bullet[j].getPosition(), MISSILE_SIZE, MISSILE_SIZE)))
            {

                /*
                newVelX1 = (firstBall.speed.x * (firstBall.mass – secondBall.mass) + (2 * secondBall.mass * secondBall.speed.x)) / (firstBall.mass + secondBall.mass);
                newVelY1 = (firstBall.speed.y * (firstBall.mass – secondBall.mass) + (2 * secondBall.mass * secondBall.speed.y)) / (firstBall.mass + secondBall.mass);
                newVelX2 = (secondBall.speed.x * (secondBall.mass – firstBall.mass) + (2 * firstBall.mass * firstBall.speed.x)) / (firstBall.mass + secondBall.mass);
                newVelY2 = (secondBall.speed.y * (secondBall.mass – firstBall.mass) + (2 * firstBall.mass * firstBall.speed.y)) / (firstBall.mass + secondBall.mass);
                */

                /*
                float x1 = (_bullet[i].getSpeedX() * (_bullet[i].getSpeed() - _bullet[j].getSpeed()) + (2 * _bullet[j].getSpeed() * _bullet[j].getSpeedX()))
                    / (_bullet[i].getSpeed() + _bullet[j].getSpeed());
                float y1 = (_bullet[i].getSpeedY() * (_bullet[i].getSpeed() - _bullet[j].getSpeed()) + (2 * _bullet[j].getSpeed() * _bullet[j].getSpeedY()))
                    / (_bullet[i].getSpeed() + _bullet[j].getSpeed());

                float x2 = (_bullet[j].getSpeedX() * (_bullet[j].getSpeed() - _bullet[i].getSpeed()) + (2 * _bullet[i].getSpeed() * _bullet[i].getSpeedX()))
                    / (_bullet[i].getSpeed() + _bullet[j].getSpeed());
                float y2 = (_bullet[j].getSpeedY() * (_bullet[j].getSpeed() - _bullet[i].getSpeed()) + (2 * _bullet[i].getSpeed() * _bullet[i].getSpeedY()))
                    / (_bullet[i].getSpeed() + _bullet[j].getSpeed());

                _bullet[i].setSpeedX(x1);
                _bullet[i].setSpeedY(y1);
                _bullet[j].setSpeedX(x2);
                _bullet[j].setSpeedY(y2);
                */

                //원 충돌 처리
               


                /*
                vx1 = circle1.vx - p * circle1.mass * n_x; 
                vy1 = circle1.vy - p * circle1.mass * n_y; 
                vx2 = circle2.vx + p * circle2.mass * n_x; 
                vy2 = circle2.vy + p * circle2.mass * n_y;

                circle1.x = midpointx + circle1.radius * (circle1.x - circle2.x) / dist;
                circle1.y = midpointy + circle1.radius * (circle1.y - circle2.y) / dist;
                circle2.x = midpointx + circle2.radius * (circle2.x - circle1.x) / dist;
                circle2.y = midpointy + circle2.radius * (circle2.y - circle1.y) / dist;
                */

                /*
                double d = sqrt(pow(_bullet[i].getPositionX() - _bullet[j].getPositionX(), 2) + pow(_bullet[i].getPositionY() - _bullet[j].getPositionY(), 2));
                double nx = (_bullet[j].getPositionX() - _bullet[i].getPositionX()) / d;
                double ny = (_bullet[j].getPositionY() - _bullet[i].getPositionY()) / d;
                double p = 2 * ((_bullet[i].getSpeedX() * nx) + (_bullet[i].getSpeedY() * ny) - (_bullet[j].getSpeedX() * nx) - (_bullet[j].getSpeedY() * ny)) /
                    (10 + 10);
                

                _bullet[i].setSpeedX(_bullet[i].getSpeedX() - p * 10 * nx);
                _bullet[i].setSpeedY(_bullet[i].getSpeedY() - p * 10 * ny);
                _bullet[j].setSpeedX(_bullet[j].getSpeedX() + p * 10 * nx);
                _bullet[j].setSpeedY(_bullet[j].getSpeedY() + p * 10 * ny);
                
                //temp = _bullet[i].getAngleD();
               // _bullet[i].setAngleD(_bullet[j].getAngleD());
               // _bullet[j].setAngleD(temp);
                */
                
                float mx = (_bullet[i].getPositionX() + _bullet[j].getPositionX()) / 2;
                float my = (_bullet[i].getPositionY() + _bullet[j].getPositionY()) / 2;
                float dist = sqrt((pow(_bullet[i].getPositionX() - _bullet[j].getPositionX(), 2) + pow(_bullet[i].getPositionY() - _bullet[j].getPositionY(), 2)));

                _bullet[i].setPosition(
                    POINT{
                    mx + (MISSILE_SIZE / 2) * (_bullet[i].getPositionX() - _bullet[j].getPositionX()) / dist,
                    my + (MISSILE_SIZE / 2) * (_bullet[i].getPositionY() - _bullet[j].getPositionY()) / dist });

                _bullet[j].setPosition(
                    POINT{
                    mx + (MISSILE_SIZE / 2) * (_bullet[j].getPositionX() - _bullet[i].getPositionX()) / dist,
                    my + (MISSILE_SIZE / 2) * (_bullet[j].getPositionY() - _bullet[i].getPositionY()) / dist });
                

                //_bullet[i].setAngleR(getAngle(_bullet[j].getPositionX(), _bullet[j].getPositionY(), _bullet[i].getPositionX(), _bullet[i].getPositionY()));
                //_bullet[j].setAngleR(getAngle(_bullet[i].getPositionX(), _bullet[i].getPositionY(), _bullet[j].getPositionX(), _bullet[j].getPositionY()));

                /*
                */
                float e = 0.95;
                float as = _bullet[i].getSpeed(), bs = _bullet[j].getSpeed();
                float vax = _bullet[i].getSpeedX(), vay = _bullet[i].getSpeedY(), vbx = _bullet[j].getSpeedX(), vby = _bullet[j].getSpeedY();
                float aR = atan2(_bullet[i].getPositionY() - _bullet[j].getPositionY(), _bullet[i].getPositionX() - _bullet[j].getPositionX()),
                    bR = atan2(_bullet[j].getPositionY() - _bullet[i].getPositionY(), _bullet[j].getPositionX() - _bullet[i].getPositionX());

                float vaxp = (1 - 1 * e) / (1 + 1)*(vax*cos(aR) + vay*sin(aR)) + (1 + 1 * e) / (1 + 1)*(vbx*cos(aR) + vby*sin(aR));
                float vbxp = (1 + 1 * e) / (1 + 1)*(vax*cos(aR) + vay*sin(aR)) + (1 - 1 * e) / (1 + 1)*(vbx*cos(aR) + vby*sin(aR));

                float vayp = vay*cos(aR) - vax*sin(aR);
                float vbyp = vby*cos(aR) - vbx*sin(aR);
          
                _bullet[i].setSpeedX(vaxp*cos(aR) - vayp*sin(aR));
                _bullet[i].setSpeedY(vaxp*sin(aR) + vayp*cos(aR));

                _bullet[j].setSpeedX(vbxp*cos(aR) - vbyp*sin(aR));
                _bullet[j].setSpeedY(vbxp*sin(aR) + vbyp*cos(aR));
            }
        }
    }


    if (KEYMANAGER->isStayKeyDown('1'))
    {
        for (int i = 0; i < MAX_MISSILE; i++)
        {
            _bullet[i].isFire = false;
        }
    }

}

//화면출력
void GameStudy::render(HDC hdc)
{
	drawLine(hdc, _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);
	drawEllipseCenter(hdc, _cannon.center.x, _cannon.center.y, _cannon.radius * 2, _cannon.radius * 2);

	for (int i = 0; i < MAX_MISSILE; i++)
	{
        if (_bullet[i].isFire)
		{
            drawEllipseCenter(hdc, _bullet[i].getPosition(), MISSILE_SIZE, MISSILE_SIZE);
		}
	}

    for (int i = 0; i < MAX_MISSILE; i++)
    {
        float xx = _bullet[i].getPositionX() + cos(_bullet[i].getAngleR()) * _bullet[i].getSpeed() * 10;
        float yy = _bullet[i].getPositionY() - sin(_bullet[i].getAngleR()) * _bullet[i].getSpeed() * 10;
        float xxx = _bullet[i].getPositionX() + cos(_bullet[i].getAngleD() * M_PI / 180) * _bullet[i].getSpeed() * 10;
        float yyy = _bullet[i].getPositionY() - sin(_bullet[i].getAngleD() * M_PI / 180) * _bullet[i].getSpeed() * 10;

        drawLine(hdc, _bullet[i].getPositionX(), _bullet[i].getPositionY(), xx, yy);
        drawLine(hdc, _bullet[i].getPositionX(), _bullet[i].getPositionY(), xxx, yyy);
    }

	TCHAR a[128];
	sprintf_s(a, "degree %.1f, radian %.5f", _cannon.angle, _cannon.angleRadian);
	TextOut(hdc, 10, 10, a, _tcslen(a));

}

float GameStudy::getAngle(float x1, float y1, float x2, float y2)
{
    float x = x2 - x1;
    float y = y2 - y1;
    float hypo = sqrt(x * x + y * y);
    float angle = acosf(x / hypo);
    if (y2 > y1)
    {
        angle = 2 * M_PI - angle;
        if (angle >= 2 * M_PI) angle -= 2 * M_PI;
    }
    return angle;
}


//05-19 숙제

//첫번째 각도에 따라서 총알 쏘고, 라디안, 각도 표시
//정적배열로.

//두번째 총알을 쓰면 벽을 튕겨 방향을 바꾼다.

