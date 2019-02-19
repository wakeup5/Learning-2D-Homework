#include "stdafx.h"
#include "Marine.h"


Marine::Marine()
{
}


Marine::~Marine()
{
}


HRESULT Marine::initialize(void)
{
	GameObject::initialize(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 20, 20, 0, 0);
	Image* marineImage = IMAGEMANAGER->addImage("marine", "resource/starcraft/marine.bmp", 1024, 832, TRUE, RGB(255, 1, 255));
	if (!marineImage) return E_FAIL;

	_image = marineImage->createSprite(16, 13);
	_image->setCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);

	TIMEMANAGER->addTimer("walk");

	return S_OK;
}
void Marine::release(void)
{
	SAFE_RELEASE(_image);
}
void Marine::update(void)
{
	GameObject::activate();

	_image->setFrameX((getAngleD() - 11.25) / 180 * 8);

	if (getSpeed() == 0)
	{
		_image->setFrameY(0);
	}
	else
	{
		if (_image->getFrameY() == 0) _image->setFrameY(4);
		if (TIMEMANAGER->checkTime("walk", 100 / (getSpeed() / 2))) _image->nextFrameY();
	}
}
void Marine::render(HDC hdc) 
{
	_image->render(hdc);
}