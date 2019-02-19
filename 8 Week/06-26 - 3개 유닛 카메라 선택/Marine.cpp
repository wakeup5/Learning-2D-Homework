#include "stdafx.h"
#include "Marine.h"


Marine::Marine()
{
}


Marine::~Marine()
{
}


HRESULT Marine::initialize(float x, float y, float angleD, float speed)
{
	Image* marineImage = IMAGEMANAGER->addImage("marine", "resource/starcraft/marine.bmp", 1024, 832, TRUE, RGB(255, 1, 255));
	if (!marineImage) return E_FAIL;

	Unit::initialize(marineImage->createSprite(16, 13), x, y, 20, 20, angleD, speed);

	_unitName = "marine";

	Image* hpBar = IMAGEMANAGER->addImage("hp bar", "resource/starcraft/hp_bar.bmp", 50, 5);
	Image* hpBarB = IMAGEMANAGER->addImage("hp bar back", "resource/starcraft/hp_bar_back.bmp", 50, 5);
	Image* mpBar = IMAGEMANAGER->addImage("mp bar", "resource/starcraft/mp_bar.bmp", 50, 5);
	Image* mpBarB = IMAGEMANAGER->addImage("mp bar back", "resource/starcraft/mp_bar_back.bmp", 50, 5);

	_hpBar->initialize(hpBar, hpBarB, 0, 20);
	_mpBar->initialize(mpBar, mpBarB, 0, 27);

	return S_OK;
}
void Marine::release(void)
{
	SAFE_RELEASE(_image);
}

void Marine::move()
{
	
}
void Marine::frame()
{
	if (getSpeed() == 0)
	{
		_image->setFrameY(0);
	}
	else
	{
		if (_image->getFrameY() == 0) _image->setFrameY(4);
	}
}
void Marine::draw(HDC hdc)
{
	
}