#include "stdafx.h"
#include "HPBar.h"


HPBar::HPBar()
{
}


HPBar::~HPBar()
{
}

HRESULT HPBar::initialize(Image* image, Image* backImage, float* x, float* y, int* hp, int maxHp, float dx, float dy)
{
	_image = image;
	_backImage = backImage;
	_x = x;
	_y = y;
	_hp = hp;

	_maxHp = maxHp;
	_diffX = dx;
	_diffY = dy;

	return S_OK;
}
void HPBar::release(void)
{

}
void HPBar::update(void)
{
	
}
void HPBar::render(void)
{
	float ratio = static_cast<float>(*_hp) / _maxHp;
	float imageWidth = _image->getWidth();
	float imageHeight = _image->getHeight();

	_backImage->render(getMemDC(), (*_x + _diffX) - imageWidth / 2, (*_y + _diffY) - imageHeight / 2, 0, 0, imageWidth, imageHeight);
	_image->render(getMemDC(), (*_x + _diffX) - imageWidth / 2, (*_y + _diffY) - imageHeight / 2, 0, 0, imageWidth * ratio, imageHeight);
}