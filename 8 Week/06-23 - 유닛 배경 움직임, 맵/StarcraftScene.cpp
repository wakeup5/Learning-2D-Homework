#include "stdafx.h"
#include "StarcraftScene.h"


StarcraftScene::StarcraftScene()
{
}


StarcraftScene::~StarcraftScene()
{
}

HRESULT StarcraftScene::initialize(void)
{
	_background = IMAGEMANAGER->addImage("space", "resource/starcraft/background.bmp", 1500, 300);
	_map = IMAGEMANAGER->addImage("map", "resource/starcraft/background.bmp", 200, 150);
	IMAGEMANAGER->addImage("map unit", "resource/starcraft/map_unit.bmp", 10, 10);

	_marine = new Marine;
	_marine->initialize();

	return S_OK;
}
void StarcraftScene::release(void)
{
	_marine->release();
}
void StarcraftScene::update(void)
{
	//_marine->setAngleR(myUtil::getGradeRadian(_marine->getX(), _marine->getY(), _mousePt.x, _mousePt.y));

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _marine->setAngleD(_marine->getAngleD() + 5);
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _marine->setAngleD(_marine->getAngleD() - 5);
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _marine->setSpeed(_marine->getSpeed() + 0.1);
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _marine->setSpeed(_marine->getSpeed() - 0.1);
	
	if (_marine->getSpeed() < 0) _marine->setSpeed(0);
	if (_marine->getSpeed() > 10) _marine->setSpeed(10);

	_marine->update();

	if (_marine->getRect().left < 0) _marine->setX(_marine->getWidth() / 2);
	if (_marine->getRect().right  > _background->getWidth()) _marine->setX(_background->getWidth() - _marine->getWidth() / 2);
	if (_marine->getRect().top < 0) _marine->setY(_marine->getHeight() / 2);
	if (_marine->getRect().bottom > _background->getHeight()) _marine->setY(_background->getHeight() - _marine->getHeight() / 2);
}
void StarcraftScene::render(void)
{
	IMAGEMANAGER->render("space", getMemDC(), -_marine->getX() + WIN_SIZE_X / 2, -_marine->getY() + WIN_SIZE_Y / 2);
	_marine->render(getMemDC());
	IMAGEMANAGER->render("map", getMemDC(), WIN_SIZE_X - _map->getWidth(), 0);

	float ratioX = (float)_map->getWidth() / _background->getWidth();
	float ratioY = (float)_map->getHeight() / _background->getHeight();

	IMAGEMANAGER->render("map unit", getMemDC(), (WIN_SIZE_X - _map->getWidth()) - 5 + (_marine->getX() * ratioX), -5 + (_marine->getY() * ratioY));
}