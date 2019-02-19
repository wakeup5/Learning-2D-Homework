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
	GameNode::release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_view = VIEW_BACK;
		_sprite->setY(_sprite->getY() - 2);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_view = VIEW_LEFT;
		_sprite->setX(_sprite->getX() - 2);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_view = VIEW_RIGHT;
		_sprite->setX(_sprite->getX() + 2);
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_view = VIEW_FRONT;
		_sprite->setY(_sprite->getY() + 2);
	}

	_spriteRect = makeRectCenter(_sprite->getX(), _sprite->getY(), 66, 64);

	_timer++;

	if (_timer > 100 * _delay)
	{
		_timer = 0;
	}

	if (_timer % _delay == 0)
	{
		if (_backCount)
		{
			_spriteNum--;
		}
		else
		{
			_spriteNum++;
		}

		if (_spriteNum >= 2)
		{
			_backCount = true;
		}
		if (_spriteNum <= 0)
		{
			_backCount = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (isCollisionEllipse(_mousePoint, _buttonRect))
		{
			_isButtonClick = true;
		}

		if (isCollisionRectangle(_mousePoint, _spriteRect))
		{
			_isSpriteClick = true;
			cx = _sprite->getX() - _mousePoint.x;
			cy = _sprite->getY() - _mousePoint.y;
		}

		_cursor->initialize("resource/mc.bmp", 550, 273, TRUE, RGB(255, 0, 255));
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_isButtonClick = false;
		_isSpriteClick = false;

		_cursor->initialize("resource/m.bmp", 550, 273, TRUE, RGB(255, 0, 255));
	}

	if (_isSpriteClick)
	{
		_sprite->setX(_mousePoint.x + cx);
		_sprite->setY(_mousePoint.y + cy);
	}

}

//화면출력
void GameStudy::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	_mapImage->render(backDC, 0, 0);
	_background->render(backDC);

	//_sprite->setCenter(_mousePoint.x, _mousePoint.y);

	if (_isButtonClick)
	{
		_button->render(backDC, 0, 0, 265, 265);
	}
	else
	{
		_button->render(backDC, 265, 0, 265, 265);
	}
	_sprite->render(backDC, 66 * _spriteNum, 64 * _view, 66, 64);

	_cursor->render(backDC, _mousePoint.x - 15, _mousePoint.y - 60);

	this->getBackBuffer()->render(hdc, 0, 0);
}

//게임 초기화
void GameStudy::gameInit()
{
	_sprite = new Image;
	_sprite->initialize("resource/c1.bmp", float(WIN_SIZE_X / 2), float(WIN_SIZE_Y / 2), 198, 256, TRUE, RGB(255, 0, 255));

	_timer = 0, _delay = 15, _spriteNum = 0;

	_button = new Image;
	_button->initialize("resource/button1.bmp", 265.0f, WIN_SIZE_Y / 2.0f, 530, 265, TRUE, RGB(255, 0, 255));
	_isButtonClick = false;
	_buttonRect = makeRectCenter(265, WIN_SIZE_Y / 2, 265, 265);

	_cursor = new Image;
	_cursor->initialize("resource/m.bmp", 550, 273, TRUE, RGB(255, 0, 255));
	ShowCursor(FALSE);
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
