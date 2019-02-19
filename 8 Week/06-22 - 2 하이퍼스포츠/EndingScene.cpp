#include "stdafx.h"
#include "EndingScene.h"


EndingScene::EndingScene()
{
}


EndingScene::~EndingScene()
{
}

HRESULT EndingScene::initialize(void)
{
	_background = IMAGEMANAGER->addImage("ending", "resource/ending.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	return S_OK;
}
void EndingScene::release(void)
{

}
void EndingScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SCENEMANAGER->changeScene("intro");
	}
}
void EndingScene::render(void)
{
	_background->render(getMemDC());
	TextOut(getMemDC(), WIN_SIZE_X / 2, WIN_SIZE_Y / 2, "이겼다고 한다", strlen("이겼다고 한다"));
}