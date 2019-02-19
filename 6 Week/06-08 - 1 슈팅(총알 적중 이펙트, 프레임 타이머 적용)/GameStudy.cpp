#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);
	IMAGEMANAGER->addImage("mapImage", "resource/mapBlack.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	IMAGEMANAGER->addImage("background", "resource/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	imageLoad();

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
	static int time = 0;
	time++;
	IMAGEMANAGER->render("mapImage", getMemDC());
	IMAGEMANAGER->render("background", getMemDC(), 0, time % WIN_SIZE_Y);
	IMAGEMANAGER->render("background", getMemDC(), 0, time % WIN_SIZE_Y - WIN_SIZE_Y);

	_playerManager->render();
	_enemyManager->render();

	TIMEMANAGER->render(getMemDC());
	GameNode::render();
}

void GameStudy::imageLoad()
{
	IMAGEMANAGER->addImage("missile down effect", "resource/missile_hit.bmp", 960, 63, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bullet up effect", "resource/bullet_hit_up.bmp", 272, 48, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bullet down effect", "resource/bullet_hit_down.bmp", 272, 48, TRUE, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("player bullet", "resource/missile.bmp", 5, 30, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player missile", "resource/missile2.bmp", 390, 61, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player tonado", "resource/player bullet.bmp", 48, 24, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player m bullet", "resource/player m bullet.bmp", 300, 30, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player p bullet", "resource/player bullet.bmp", 48, 24, TRUE, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("enemy bullet", "resource/enemy bullet.bmp", 16, 8, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ufo", "resource/enemy.bmp", 306, 58, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hp bar", "resource/hp bar.bmp", 50, 4);
	IMAGEMANAGER->addImage("hp bar back", "resource/hp bar back.bmp", 50, 4);

	IMAGEMANAGER->addImage("boss", "resource/boss.bmp", 1685, 400, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss hp bar", "resource/hp bar.bmp", 300, 8);
	IMAGEMANAGER->addImage("boss hp bar back", "resource/hp bar back.bmp", 300, 8);
}