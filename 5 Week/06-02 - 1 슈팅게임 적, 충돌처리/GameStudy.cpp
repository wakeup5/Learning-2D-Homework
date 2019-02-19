#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);
	IMAGEMANAGER->addImage("mapImage", "resource/mapBlack.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	IMAGEMANAGER->addImage("background", "resource/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_rocket = new Rocket;
	_rocket->initialize();
	OBJECTMANAGER->addObject("player 1 rocket", _rocket);

	_enemy = new Enemy;
	_enemy->initialize();
	OBJECTMANAGER->addObject("enemy 1", _enemy);


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
	OBJECTMANAGER->update();	

	_time += 5;
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("mapImage", getMemDC());
	IMAGEMANAGER->render("background", getMemDC(), 0, _time % WIN_SIZE_Y);
	IMAGEMANAGER->render("background", getMemDC(), 0, (_time % WIN_SIZE_Y) - WIN_SIZE_Y); 
	OBJECTMANAGER->render();
	GameNode::render();
}
