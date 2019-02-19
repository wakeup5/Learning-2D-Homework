#include "stdafx.h"
#include "GameStudy.h"
#include "iconScene.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);

	imageLoad();

	SCENEMANAGER->addScene("icon 1", new IconScene1);
	SCENEMANAGER->addScene("icon 2", new IconScene2);
	SCENEMANAGER->addScene("icon 3", new IconScene3);
	SCENEMANAGER->addScene("icon 4", new IconScene4);
	SCENEMANAGER->addScene("icon 5", new IconScene5);
	SCENEMANAGER->addScene("icon 6", new IconScene6);
	SCENEMANAGER->addScene("icon 7", new IconScene7);
	SCENEMANAGER->addScene("icon 8", new IconScene8);
	SCENEMANAGER->addScene("icon 9", new IconScene9);
	SCENEMANAGER->addScene("icon 10", new IconScene10);

	SCENEMANAGER->changeScene("icon " + to_string(RANDOM->getInt(10)));

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

	EFFECTMANAGER->update();
	SCENEMANAGER->update();
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("backMap", getMemDC());

	SCENEMANAGER->render();
	GameNode::render();
}

void GameStudy::imageLoad()
{
	IMAGEMANAGER->addImage("backMap", "resource/backMap.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	IMAGEMANAGER->addImage("janggi back", "resource/back.bmp", 500, 500);
	IMAGEMANAGER->addImage("janggi mal", "resource/jang_gi.bmp", 385, 110, true, RGB(255, 0, 255));
}