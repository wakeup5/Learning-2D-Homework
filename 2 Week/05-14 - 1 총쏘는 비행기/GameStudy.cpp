#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	//_fps = 100;
	GameNode::initialize();


	//_gamePad = makeRect(10, 10, WIN_SIZE_X - 10, WIN_SIZE_Y - 10);
	_player = makePoint(WIN_SIZE_X / 2, WIN_SIZE_Y - 50);

	for (int i = 0; i < _maxBullets; i++)
	{
		_bullets[i] = NULL;
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

	if ((_player.x > 0) && KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player.x -= _speed;
	}

	if ((_player.x < WIN_SIZE_X) && KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player.x += _speed;
	}

	if ((_player.y > 0) && KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_player.y -= _speed;
	}

	if ((_player.y < WIN_SIZE_Y) && KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_player.y += _speed;
	}

	//총알 쏨
	if (_coolTime <= 0)
	{
		if ((KEYMANAGER->isToggleKey('A') || KEYMANAGER->isStayKeyDown(VK_SPACE)) && _bullets[_maxBullets - 1] == NULL)
		{
			//_bullets.push_back(POINT{_player.x, _player.y - 20});
			for (int i = 0; i < _maxBullets; i++)
			{
				if (_bullets[i] == NULL)
				{
					_bullets[i] = new POINT{ _player.x, _player.y - 20 };
					break;
				}
			}
			_coolTime = BULLET_COOLTIME;
		}
	}
	else
	{
		//타이머가 100fps이므로
		_coolTime -= 1000 / _fps;
	}

	//총알 전진
	//vector<POINT>::iterator iter;
	/*
	for (auto iter = _bullets.begin(); iter != _bullets.end();)
	{
		iter->y -= _bulletSpeed;
		if (iter->y < 0) iter = _bullets.erase(iter);
		else iter++;
	}
	*/

	//중간에 총알이 비면 뒤에것을 앞으로 땡기고 뒤를 NULL로 채움.
	for (int i = 0; i < _maxBullets; i++)
	{
		if (_bullets[i] == NULL) break;
		_bullets[i]->y -= _bulletSpeed;
		
		if (_bullets[i]->y < 0)
		{
			SAFE_DELETE(_bullets[i]);
			for (int j = i; j < _maxBullets - 1; j++)
			{
				_bullets[j] = _bullets[j + 1];
				_bullets[j + 1] = NULL;
			}
			i--;
		}
	}
}

//화면출력
void GameStudy::render(HDC hdc)
{
	/*
	for (auto iter = _bullets.begin(); iter != _bullets.end(); iter++)
	{
		drawRectangleCenter(hdc, *iter, 5, 15);
	}
	*/
	for (int i = 0; i < _maxBullets; i++)
	{
		if (_bullets[i] == NULL) break;
		drawRectangleCenter(hdc, *_bullets[i], 5, 15);
	}

	drawEllipse(hdc, makeRectCenter(_player, 20, 30));
}