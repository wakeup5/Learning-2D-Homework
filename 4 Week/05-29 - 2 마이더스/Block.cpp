#include "stdafx.h"
#include "Block.h"


Block::Block()
{

}

Block::~Block()
{

}

void Block::update()
{
	if (_blockKind == 1 && _isGold)
	{
		if (_goldDelay > 0)
		{
			_goldDelay--;
		}
		else
		{
			//¶³¾îÁü
			setSpeedY(getSpeedY() + 0.2);
		}
	}
}

void Block::render(HDC hdc)
{
	HBRUSH hb = NULL, hob;
	HPEN hp = NULL, hop;
	if (_blockKind == 1)
	{
		int colorNum = 255 - (static_cast<float>(_goldDelay) / 50 * 255);
		hb = CreateSolidBrush(RGB(colorNum, colorNum, 0));
	}
	else if (_blockKind == 2)
	{
		hb = CreateSolidBrush(RGB(50, 50, 255));
	}
	hob = (HBRUSH)SelectObject(hdc, hb);

	hp = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	hop = (HPEN)SelectObject(hdc, hp);
	//debugPrintNum(hdc, 10, 10, colorNum);

	drawRectangleCenter(hdc, getPosition(), getWidth(), getHeight());

	SelectObject(hdc, hob);
	DeleteObject(hb);

	SelectObject(hdc, hop);
	DeleteObject(hp);

}