#include "stdafx.h"
#include "Button.h"

Button::Button()
{
	
}


Button::~Button()
{
}
HRESULT Button::initialize(Image* image, float x, float y, CallbackFunc callback)
{
	_image = image->createSprite(3, 1);
	_x = x;
	_y = y;
	_downCallback = callback;

	_image->setCenter(_x, _y);
	_state = BUTTON_UP;

	return S_OK;
}
void Button::release()
{
	SAFE_RELEASE(_image);
}
void Button::update()
{
	GameNode::update();
	_image->setCenter(_x, _y);

	switch (_state)
	{
	case BUTTON_DOWN_START:
		_state = BUTTON_DOWN;
		break;
	case BUTTON_DOWN:
		_image->setFrameX(1);
		if (!_leftButtonDown)
		{
			_state = BUTTON_UP_START;
		}
		if (!PtInRect(&_image->getRect(), _mousePt))
		{
			_state = BUTTON_UP;
		}
		break;
	case BUTTON_UP_START:
		if (_downCallback != NULL) _downCallback();
		_state = BUTTON_UP;
		break;
	case BUTTON_UP: case BUTTON_NONE:
		_image->setFrameX(0);
		if (PtInRect(&_image->getRect(), _mousePt) && _leftButtonDown)
		{
			_state = BUTTON_DOWN_START;
		}
		break;
	}
}
void Button::render()
{
	_image->render(getMemDC());
}