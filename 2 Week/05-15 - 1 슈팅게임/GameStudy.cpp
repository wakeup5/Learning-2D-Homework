#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();

	_player.setPosition(makePoint(WIN_SIZE_X / 2, WIN_SIZE_Y - 50));
	_player.setSize(20, 30);
	_player.setSpeed(5);

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		_enemys[i].setIsLive(false);
		_enemys[i].setSize(15, 20);
	}

	_score = 0;

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

	if (_player.getHp() > 0)
	{
		//키 입력
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _player.getSize().bottom < WIN_SIZE_Y)
		{
			_player.moveY(_player.getSpeed());
		}

		if (KEYMANAGER->isStayKeyDown(VK_UP) && _player.getSize().top > 0)
		{
			_player.moveY(-_player.getSpeed());
		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player.getSize().left > 0)
		{
			_player.moveX(-_player.getSpeed());
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player.getSize().right < WIN_SIZE_X)
		{
			_player.moveX(_player.getSpeed());
		}

		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
			Enemy* e = NULL;
			for (int i = 0; i < MAX_ENEMY; i++)
			{
				if (_enemys[i].getIsLive() && RANDOM->getInt(MAX_ENEMY) < 2)
				{
					e = &_enemys[i];
				}
			}

			//if (e != NULL)
			//{
				_player.fire(e);
			//}
		}

		//무기 변경
		if (KEYMANAGER->isOnceKeyDown('1'))
		{
			_player.setMode(0);
		}

		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			_player.setMode(1);
		}

		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			_player.setMode(2);
		}

		if (KEYMANAGER->isOnceKeyDown('4'))
		{
			_player.setMode(3);
		}

		if (KEYMANAGER->isOnceKeyDown('5'))
		{
			_player.shield();
		}
	}

	_player.update();

	//적 생성
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (RANDOM->getInt(20) < 1 && !_enemys[i].getIsLive())
		{
			_enemys[i].setPosition(makePoint(RANDOM->getIntTo(0, WIN_SIZE_X), 0));
			_enemys[i].setSpeed(RANDOM->getIntTo(3, 5));
			_enemys[i].setIsLive(true);
			break;
		}
	}


	//적 움직임
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (_enemys[i].getIsLive())
		{
			_enemys[i].move(RANDOM->getIntTo(-2, 2), _enemys[i].getSpeed());
			
			//충돌처리
			if (_player.collision(_enemys[i].getSize()))
			{
				_enemys[i].setIsLive(false);
				_score++;
			}
		}


		if (_enemys[i].getSize().top > WIN_SIZE_Y)
		{
			_enemys[i].setIsLive(false);
		}
	}

	_player.recoveryHp();
}

//화면출력
void GameStudy::render(HDC hdc)
{
	_player.printBullet(hdc);

	if (_player.getHp() > 0)
	{
		drawEllipse(hdc, _player.getSize());
	}

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (_enemys[i].getIsLive())
		{
			drawRectangle(hdc, _enemys[i].getSize());
		}
	}

	int hpRatio = 100 * _player.getHp() / PLAYER_HP;
	HBRUSH b = (HBRUSH)SelectObject(hdc, CreateSolidBrush(RGB(255 - (100 * hpRatio / 100), 255 * hpRatio / 100, 0)));
	Rectangle(hdc, WIN_SIZE_X - 25, (WIN_SIZE_Y - 30) - hpRatio, WIN_SIZE_X - 10, WIN_SIZE_Y - 30);
	//SelectObject(hdc, b);

	TCHAR hpStr[10];
	sprintf_s(hpStr, "%3d", hpRatio);
	TextOut(hdc, WIN_SIZE_X - 30, WIN_SIZE_Y - 25, hpStr, _tcslen(hpStr));

	TCHAR scoreStr[128];
	sprintf_s(scoreStr, "score : %10d", _score);
	TextOut(hdc, 10, 10, scoreStr, _tcslen(scoreStr));

	if (_player.getHp() <= 0)
	{
		TCHAR deadStr[128] = "게임 오버";
		TextOut(hdc, WIN_SIZE_X / 2 - 42, WIN_SIZE_Y / 2 - 10, deadStr, _tcslen(deadStr));
	}
}
