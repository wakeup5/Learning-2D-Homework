#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	_mapImage = new Image();
	_mapImage->initialize("map.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_background = new Image;
	_background->initialize("resource/11.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	gameInit();

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	_mapImage->release();
	_background->release();
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
	HDC backDC = this->getBackBuffer()->getMemDC();
	_mapImage->render(backDC, 0, 0);
	_background->render(backDC);

	HBRUSH p = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH s = CreateSolidBrush(RGB(100, 0, 100));

	SelectObject(backDC, p);
	for (int i = 0; i < GAME_LENGTH; i++)
	{
		if (_isOpen && i == _select)
		{
			//SelectObject(backDC, s);
			_cc->render(backDC, _rect[i].left, _rect[i].top, 0, 0, 40, 40);
		}
		else
		{
			//SelectObject(backDC, p);
			_cc->render(backDC, _rect[i].left, _rect[i].top, 40, 0, 40, 40);
		}

		//Rectangle(backDC, _rect[i].left, _rect[i].top, _rect[i].right, _rect[i].bottom);
	}

	TCHAR cool[128];
	sprintf_s(cool, "cooltime : %d", _offTime);
	TextOut(backDC, 10, 160, cool, _tcslen(cool));

	TCHAR score[128];
	sprintf_s(score, "score : %d", _score);
	TextOut(backDC, 10, 120, score, _tcslen(score));

	this->getBackBuffer()->render(hdc, 0, 0);
}

//게임 초기화
void GameStudy::gameInit()
{
	int x, y;

	for (int i = 0; i < GAME_LENGTH; i++)
	{
		x = 10 + ((i % GAME_WIDTH) * 48);
		y = 10 + ((i / GAME_WIDTH) * 48);

		_rect[i] = RECT{ x, y, x + 40, y + 40 };
	}

	_cc = new Image;
	_cc->initialize("resource/cc.bmp", 80, 40, TRUE, RGB(255, 0, 255));
}

//숙제
//1. 두더지 게임을 이미지를 넣어서

//2. 상하좌우를 누르면 케릭터가 상하좌우를 보며 움직인다.

//3. 마우스 포인터 대신 손가락 이미지
//마우스를 따라다니는 손가락 이미지
//마우스 없앨수 있으면 없애도 된다.
//버튼 같은 이미지가 있는데 마우스로 누르면 버튼 눌러진듯의 이미지로 바뀜
//아무이미지가 오른쪽에 있는데 드래그 가능

//4. 
