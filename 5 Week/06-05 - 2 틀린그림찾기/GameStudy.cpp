#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);
	IMAGEMANAGER->addImage("mapImage", "resource/mapBlack.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	IMAGEMANAGER->addImage("background", "resource/backMap.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	IMAGEMANAGER->addImage("time bar", "resource/time bar.bmp", WIN_SIZE_X - 20, 20);

	_stage = 1;
	_time = GetTickCount();
	_isGameOver = false;

	_gameTime = 6000;

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
	SAFE_RELEASE(_hs);
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

	if (_hs == NULL)
	{
		if (_stage == 1) init1();
		if (_stage == 2) init2();
		if (_stage == 3) init3();
	}
	else
	{
		if (!_isGameOver && !_hs->isClear()) _hs->update();

		if (_hs->isClear())
		{
			_clearTime++;

			if (_clearTime > 100)
			{
				_stage++;
				SAFE_RELEASE(_hs);
			}
		}
		else
		{
			if (GetTickCount() - _time > _gameTime)
			{
				_isGameOver = true;
			}

			static int go = 0;
			if (_isGameOver)
			{
				if (go > 100)
				{
					SAFE_RELEASE(_hs);

					_isGameOver = false;
					go = 0;
				}
				go++;
			}
		}
	}
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("mapImage", getMemDC());
	IMAGEMANAGER->render("background", getMemDC());

	if (_hs != NULL)
	{
		_hs->render();

		if (_hs->isClear())
		{
			TextOut(getMemDC(), WIN_SIZE_X / 2, WIN_SIZE_Y / 2, "클리어!!", 8);
		}
		else if (_isGameOver)
		{
			TextOut(getMemDC(), WIN_SIZE_X / 2, WIN_SIZE_Y / 2, "게임오버!!", 10);
		}
		else
		{
			float t = GetTickCount() - _time;
			IMAGEMANAGER->render("time bar", getMemDC(), 10.0f, 10.0f, 0, 0, (WIN_SIZE_X - 20) - ((t / _gameTime) * (WIN_SIZE_X - 20)), 20);
		}
	}

	GameNode::render();
}

void GameStudy::init1()
{
	vector<RECT> _vRc1;
	_vRc1.push_back(RECT{ 794, 481, 864, 533 });
	_vRc1.push_back(RECT{ 700, 434, 725, 450 });
	_vRc1.push_back(RECT{ 596, 553, 657, 578 });
	_vRc1.push_back(RECT{ 557, 52, 599, 77 });
	_vRc1.push_back(RECT{ 806, 79, 824, 109 });
	_vRc1.push_back(RECT{ 682, 332, 768, 387 });

	_hs = new HiddenSearch;
	_hs->initialize(
		IMAGEMANAGER->addImage("original 2", "resource/2-1.bmp", 500, 700),
		IMAGEMANAGER->addImage("modify 2", "resource/2-2.bmp", 500, 700),
		_vRc1,
		IMAGEMANAGER->addImage("ok", "resource/ok.bmp", 50, 39, TRUE, RGB(255, 0, 255)));

	_time = GetTickCount();
	_clearTime = 0;
}
void GameStudy::init2()
{
	vector<RECT> _vRc1;
	_vRc1.push_back(RECT{ 171 + 500, 9, 234 + 500, 57 });
	_vRc1.push_back(RECT{ 226 + 500, 443, 250 + 500, 468 });
	_vRc1.push_back(RECT{ 218 + 500, 474, 259 + 500, 544 });
	_vRc1.push_back(RECT{ 355 + 500, 308, 400 + 500, 350 });
	_vRc1.push_back(RECT{ 440 + 500, 449, 481 + 500, 509 });
	_vRc1.push_back(RECT{ 184 + 500, 643, 269 + 500, 684 });

	_hs = new HiddenSearch;
	_hs->initialize(
		IMAGEMANAGER->addImage("original 3", "resource/3-1.bmp", 500, 700),
		IMAGEMANAGER->addImage("modify 3", "resource/3-2.bmp", 500, 700),
		_vRc1,
		IMAGEMANAGER->addImage("ok", "resource/ok.bmp", 50, 39, TRUE, RGB(255, 0, 255)));

	_time = GetTickCount();
	_clearTime = 0;
}
void GameStudy::init3()
{
	vector<RECT> _vRc1;
	_vRc1.push_back(RECT{ 315 + 500, 106, 362 + 500, 147 });
	_vRc1.push_back(RECT{ 396 + 500, 0, 428 + 500, 22 });
	_vRc1.push_back(RECT{ 140 + 500, 266, 262 + 500, 338 });
	_vRc1.push_back(RECT{ 197 + 500, 506, 230 + 500, 536 });
	_vRc1.push_back(RECT{ 466 + 500, 660, 500 + 500, 700 });
	_vRc1.push_back(RECT{ 0 + 500, 581, 73 + 500, 644 });

	_hs = new HiddenSearch;
	_hs->initialize(
		IMAGEMANAGER->addImage("original 1", "resource/1-1.bmp", 500, 700),
		IMAGEMANAGER->addImage("modify 1", "resource/1-2.bmp", 500, 700),
		_vRc1,
		IMAGEMANAGER->addImage("ok", "resource/ok.bmp", 50, 39, TRUE, RGB(255, 0, 255)));

	_time = GetTickCount();
	_clearTime = 0;
}