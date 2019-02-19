#include "stdafx.h"
#include "IntroScene.h"


IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}

HRESULT IntroScene::initialize(void)
{
	_image[0] = IMAGEMANAGER->addImage("bg_marine", "resource/starcraft/background_marine.bmp", WIN_SIZE_X / 6.0f, WIN_SIZE_Y / 2.0f, WIN_SIZE_X / 3, WIN_SIZE_Y);
	_image[1] = IMAGEMANAGER->addImage("bg_zerg", "resource/starcraft/background_zerg.bmp", WIN_SIZE_X / 2.0f, WIN_SIZE_Y / 2.0f, WIN_SIZE_X / 3, WIN_SIZE_Y);
	_image[2] = IMAGEMANAGER->addImage("bg_scourge", "resource/starcraft/background_scourge.bmp", 5 * WIN_SIZE_X / 6.0f, WIN_SIZE_Y / 2.0f, WIN_SIZE_X / 3, WIN_SIZE_Y);

	_selectNum = 0;

	return S_OK;
}
void IntroScene::release(void)
{

}
void IntroScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_image[i]->boundingBox(), _mousePt))
			{
				_selectNum = i;
				break;
			}
		}
	}
}
void IntroScene::render(void)
{
	for (int i = 0; i < 3; i++)
	{
		_image[i]->render(getMemDC(), (i == _selectNum)? 100 : 255);
	}
}