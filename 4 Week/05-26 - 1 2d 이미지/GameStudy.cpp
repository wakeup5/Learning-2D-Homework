#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	_mapImage = new Image();
	_mapImage->initialize("map.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	gameInit();

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	_image->release();
	GameNode::release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

	if (_timer % _spriteSpeed == 0)
	{
		_spriteView++;
		if (_spriteView > 29) _spriteView = 0;

		_sx = (_spriteView % 6) * 32.5;
		_sy = (_spriteView / 6) * 40;
	}

	_timer++;
	if (_timer > 1000)_timer = 0;
}

//화면출력
void GameStudy::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	_mapImage->render(backDC, 0, 0);

	_image->render(backDC, _mousePoint.x, _mousePoint.y, 0, 50, 100, 100);

	for (int i = 0; i < 10; i++)
	{
		_character[i]->render(backDC, (i % 4) * 150, (i / 4) * 150);
	}

	_sprite->render(backDC, _mousePoint.x, _mousePoint.y, _sx, _sy, _sWidth, _sHeight);

	this->getBackBuffer()->render(hdc, 0, 0);
}

//게임 초기화
void GameStudy::gameInit()
{
	_image = new Image;
	_image->initialize("panda.bmp", 300, 200, TRUE, RGB(255, 255, 255));

	TCHAR imageNum[128];
	for (int i = 0; i < 10; i++)
	{
		sprintf_s(imageNum, "resource/%d.bmp", i + 1);
		_character[i] = new Image;
		_character[i]->initialize(imageNum, 100, 100, TRUE, RGB(255, 255, 255));
	}

	_sprite = new Image;
	_sprite->initialize("sp.bmp", 195, 200, TRUE, RGB(0, 0, 255));
	_timer = 0;
	_sWidth = 32;
	_sHeight = 40;

	_spriteSpeed = 3;
}

//숙제
//1. 36초 정도 render함수 이미지 클래스에 하나 더 만듬
//이미지를 뿌리는데 원본이 있다.
//원하는 위치와 크기만을 뿌린다. 잘라서 그린다

//2. 화면에 10개 정도 그림. 케릭터를 그림
//(트랜스 색상을 넣으면 될듯)

//3. 에니메이션 케릭터 넣기