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

	//미사일 발사
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
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
		}

		if (_missiles[i].px > WIN_SIZE_X)// && !(_missiles[i].angle > 90 && _missiles[i].angle < 270))
		{
			//_missiles[i].isFire = false; //1번숙제
			_missiles[i].angle = 180 - _missiles[i].angle;//(_missiles[i].angle <= 180 ? 180 : -540);
		}

		if (_missiles[i].py < 0)
		{
			//_missiles[i].isFire = false; //1번숙제
			_missiles[i].angle = 360 - _missiles[i].angle;
		}

		if (_missiles[i].py > WIN_SIZE_Y)
		{
			//_missiles[i].isFire = false; //1번숙제
			_missiles[i].angle = 360 - _missiles[i].angle;
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


	if (KEYMANAGER->isStayKeyDown('1'))
	{
		for (int i = 0; i < MAX_MISSILE; i++)
		{
			_missiles[i].isFire = false;
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
		if (_missiles[i].isFire)
		{
			drawEllipseCenter(hdc, _missiles[i].px, _missiles[i].py, _missiles[i].radius, _missiles[i].radius);
		}
	}

	TCHAR a[128];
	sprintf_s(a, "degree %.1f, radian %.5f", _cannon.angle, _cannon.angleRadian);
	TextOut(hdc, 10, 10, a, _tcslen(a));

}

//05-19 숙제

//첫번째 각도에 따라서 총알 쏘고, 라디안, 각도 표시
//정적배열로.

//두번째 총알을 쓰면 벽을 튕겨 방향을 바꾼다.

