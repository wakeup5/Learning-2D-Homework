#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	_ellipse = makePointRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 150, 200);
	_rectangle = makePointRectCenter(WIN_SIZE_X, WIN_SIZE_Y, 250, 300);
	_rectangleS = makePointRectCenter(0, WIN_SIZE_Y, 100, 50);

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

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (isCollisionRectangle(_mousePoint, _rectangle.rect))
		{
			dx = _rectangle.point.x - _mousePoint.x;
			dy = _rectangle.point.y - _mousePoint.y;
			_isClick = true;
		}
		else if (isCollisionRectangle(_mousePoint, _rectangleS.rect))
		{
			dx = _rectangleS.point.x - _mousePoint.x;
			dy = _rectangleS.point.y - _mousePoint.y;
			_isClickS = true;
		}
	}

	if (_isClick)
	{
		_rectangle.point.x = _mousePoint.x + dx;
		_rectangle.point.y = _mousePoint.y + dy;
		_rectangle.rect = makeRectCenter(_rectangle.point, 250, 300);
	}

	if (_isClickS)
	{
		_rectangleS.point.x = _mousePoint.x + dx;
		_rectangleS.point.y = _mousePoint.y + dy;
		_rectangleS.rect = makeRectCenter(_rectangleS.point, 100, 50);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_isClick = false;
		_isClickS = false;
	}

}

//화면출력
void GameStudy::render(HDC hdc)
{
	HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));

	if (isCollisionEllipse(_mousePoint, _ellipse.rect) || 
		isCollisionEllipse(_rectangle.rect, _ellipse.rect) ||
		isCollisionEllipse(_rectangleS.rect, _ellipse.rect))
	{
		TCHAR ms[128] = "충돌";
		TextOut(hdc, 10, 10, ms, _tcslen(ms));

		b = CreateSolidBrush(RGB(200, 0, 0));
	}

	drawRectangle(hdc, _rectangleS.rect);
	drawRectangle(hdc, _rectangle.rect);

	b = (HBRUSH)SelectObject(hdc, b);
	drawEllipse(hdc, _ellipse.rect);
	SelectObject(hdc, b);
	DeleteObject(b);


}
