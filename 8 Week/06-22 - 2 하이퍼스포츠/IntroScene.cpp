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
	_background = IMAGEMANAGER->addImage("intro image", "resource/intro.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	return S_OK;
}
void IntroScene::release(void)
{

}
void IntroScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SCENEMANAGER->changeScene("game");
	}
}
void IntroScene::render(void)
{
	_background->render(getMemDC());
}