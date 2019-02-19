#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);
	IMAGEMANAGER->addImage("mapImage", "resource/mapBlack.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	IMAGEMANAGER->addImage("background", "resource/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_sl = new SaveLoad;
	_sl->initialize();

	_playerManager = new PlayerManager;
	_playerManager->initialize();

	_enemyManager = new EnemyManager;
	_enemyManager->initialize();

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
	_playerManager->release();
	_enemyManager->release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();
	_sl->update();
	_playerManager->update();
	_enemyManager->update();
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("mapImage", getMemDC());
	IMAGEMANAGER->render("background", getMemDC());

	_playerManager->render();
	_enemyManager->render();

	GameNode::render();
}
