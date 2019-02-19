#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);
	IMAGEMANAGER->addImage("mapImage", "resource/mapBlack.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	IMAGEMANAGER->addImage("background", "resource/backMap.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_s1 = new Sceen1;
	_s1->initialize();

	_sceenNum = 1;
	_isInit = true;

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
	_s1->release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();
	
	_s1->update();
	
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("mapImage", getMemDC());
	IMAGEMANAGER->render("background", getMemDC());

	_s1->render();
	
	GameNode::render();
}

void GameStudy::controlMessage(int message)
{
	_s1->controlMessage(message);
}
