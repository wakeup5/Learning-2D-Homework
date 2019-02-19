#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();

	int x, y;

	for (int i = 0; i < GAME_LENGTH; i++)
	{
		x = 10 + ((i % GAME_WIDTH) * 48);
		y = 10 + ((i / GAME_WIDTH) * 48);

		_rect[i] = RECT{ x, y, x + 40, y + 40 };
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

	if (!_isOpen && RANDOM->getInt(100) < 2)
	{
		_select = RANDOM->getInt(GAME_LENGTH);
		_isOpen = true;
		_offTime = RANDOM->getIntTo(20, 100);
	}

	if (_isOpen && _offTime <= 0)
	{
		_isOpen = false;
		_isClick = false;
	}

	if (_offTime > 0)
	{
		_offTime--;
	}

	if (!_isClick && _isOpen && KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_rect[_select], _mousePoint))
	{
		_score++;
		//_offTime = 0;
		//_isOpen = false;
		_isClick = true;
	}

}

//화면출력
void GameStudy::render(HDC hdc)
{
	HBRUSH p = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH s = CreateSolidBrush(RGB(100, 0, 100));

	SelectObject(hdc, p);
	for (int i = 0; i < GAME_LENGTH; i++)
	{
		if (_isOpen && i == _select)
		{
			SelectObject(hdc, s);
		}
		else
		{
			SelectObject(hdc, p);
		}

		Rectangle(hdc, _rect[i].left, _rect[i].top, _rect[i].right, _rect[i].bottom);
	}

	TCHAR cool[128];
	sprintf_s(cool, "cooltime : %d", _offTime);
	TextOut(hdc, 10, WIN_SIZE_Y - 60, cool, _tcslen(cool));

	TCHAR score[128];
	sprintf_s(score, "score : %d", _score);
	TextOut(hdc, 10, WIN_SIZE_Y - 30, score, _tcslen(score));
}
