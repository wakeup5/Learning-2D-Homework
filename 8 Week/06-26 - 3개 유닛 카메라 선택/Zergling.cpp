#include "stdafx.h"
#include "Zergling.h"


Zergling::Zergling()
{
}


Zergling::~Zergling()
{
}
HRESULT Zergling::initialize(float x, float y, float angleD, float speed)
{
	Image* image = IMAGEMANAGER->addImage("zergling", "resource/starcraft/zergling.bmp", 2048, 1536, TRUE, RGB(255, 1, 255));
	if (!image) return E_FAIL;

	Unit::initialize(image->createSprite(16, 12), x, y, 20, 20, angleD, speed);

	_unitName = "zergling";

	Image* hpBar = IMAGEMANAGER->addImage("hp bar", "resource/starcraft/hp_bar.bmp", 50, 5);
	Image* hpBarB = IMAGEMANAGER->addImage("hp bar back", "resource/starcraft/hp_bar_back.bmp", 50, 5);
	Image* mpBar = IMAGEMANAGER->addImage("mp bar", "resource/starcraft/mp_bar.bmp", 50, 5);
	Image* mpBarB = IMAGEMANAGER->addImage("mp bar back", "resource/starcraft/mp_bar_back.bmp", 50, 5);

	_hpBar->initialize(hpBar, hpBarB, 0, 20);
	_mpBar->initialize(mpBar, mpBarB, 0, 27);

	_walkTime = 10000;

	return S_OK;
}
void Zergling::release(void)
{
	SAFE_RELEASE(_image);
}
void Zergling::move()
{

}

void Zergling::frame(void)
{
	if (getSpeed() == 0)
	{
		_image->setFrameY(4);
	}
	else
	{
		if (_image->getFrameY() == 0) _image->setFrameY(5);
	}

}
void Zergling::draw(HDC hdc)
{

}