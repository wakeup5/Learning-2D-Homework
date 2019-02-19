#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize(true);

	imageLoad();

	_jg = new JangGi;
	_jg->initialize();

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();

	_jg->release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();
	
	_jg->update();

	EFFECTMANAGER->update();
}

//화면출력
void GameStudy::render()
{
	IMAGEMANAGER->render("backMap", getMemDC());

	_jg->render();

	GameNode::render();
}

void GameStudy::imageLoad()
{
	IMAGEMANAGER->addImage("backMap", "resource/backMap.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	IMAGEMANAGER->addImage("janggi back", "resource/back.bmp", 500, 500);
	IMAGEMANAGER->addImage("janggi mal", "resource/jang_gi.bmp", 385, 110, true, RGB(255, 0, 255));
}