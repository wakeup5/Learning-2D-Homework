#include "stdafx.h"
#include "StarcraftScene.h"

extern Unit* _selectUnit;

StarcraftScene::StarcraftScene()
{
}


StarcraftScene::~StarcraftScene()
{
	
}

HRESULT StarcraftScene::initialize(void)
{
	_background = IMAGEMANAGER->addImage("space", "resource/starcraft/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_map = IMAGEMANAGER->addImage("map", "resource/starcraft/background.bmp", 200, 150);
	IMAGEMANAGER->addImage("map unit", "resource/starcraft/map_unit.bmp", 10, 10);

	vector<string> unitInfo = DATABASE->get("marine");
	
	_unit[0] = new Marine;
	_unit[0]->initialize(RANDOM->getInt(WIN_SIZE_X), RANDOM->getInt(WIN_SIZE_X), RANDOM->getFloat(M_PI * 2), 0);

	_unit[0]->setMaxHP(atoi(unitInfo[1].c_str()));
	_unit[0]->setHP(atoi(unitInfo[2].c_str()));
	_unit[0]->setMaxMP(atoi(unitInfo[3].c_str()));
	_unit[0]->setMP(atoi(unitInfo[4].c_str()));
	_unit[0]->setMaxSpeed(atoi(unitInfo[5].c_str()));
	_unit[0]->setViewAccel(atoi(unitInfo[6].c_str()));

	if (atoi(unitInfo[7].c_str())) _selectNum = 0;

	unitInfo = DATABASE->get("zergling");

	_unit[1] = new Zergling;
	_unit[1]->initialize(RANDOM->getInt(WIN_SIZE_X), RANDOM->getInt(WIN_SIZE_X), RANDOM->getFloat(M_PI * 2), atoi(unitInfo[7].c_str()));

	_unit[1]->setMaxHP(atoi(unitInfo[1].c_str()));
	_unit[1]->setHP(atoi(unitInfo[2].c_str()));
	_unit[1]->setMaxMP(atoi(unitInfo[3].c_str()));
	_unit[1]->setMP(atoi(unitInfo[4].c_str()));
	_unit[1]->setMaxSpeed(atoi(unitInfo[5].c_str()));
	_unit[1]->setViewAccel(atoi(unitInfo[6].c_str()));

	if (atoi(unitInfo[7].c_str())) _selectNum = 1;

	unitInfo = DATABASE->get("scourge");

	_unit[2] = new Scourge;
	_unit[2]->initialize(RANDOM->getInt(WIN_SIZE_X), RANDOM->getInt(WIN_SIZE_X), RANDOM->getFloat(M_PI * 2), atoi(unitInfo[7].c_str()));

	_unit[2]->setMaxHP(atoi(unitInfo[1].c_str()));
	_unit[2]->setHP(atoi(unitInfo[2].c_str()));
	_unit[2]->setMaxMP(atoi(unitInfo[3].c_str()));
	_unit[2]->setMP(atoi(unitInfo[4].c_str()));
	_unit[2]->setMaxSpeed(atoi(unitInfo[5].c_str()));
	_unit[2]->setViewAccel(atoi(unitInfo[6].c_str()));

	if (atoi(unitInfo[7].c_str())) _selectNum = 2;

	_camera = IMAGEMANAGER->addImage("camera", WIN_SIZE_X, WIN_SIZE_Y);
	
	_bullet = new Bullets();
	_bullet->initialize(NULL, 500, 50);
	

	return S_OK;
}
void StarcraftScene::release(void)
{
	SAFE_RELEASE(_unit[0]);
	SAFE_RELEASE(_unit[1]);
	SAFE_RELEASE(_unit[2]);
}
void StarcraftScene::update(void)
{
	//_marine->setAngleR(myUtil::getGradeRadian(_marine->getX(), _marine->getY(), _mousePt.x, _mousePt.y));

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _unit[_selectNum]->setAngleD(_unit[_selectNum]->getAngleD() + 5);
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _unit[_selectNum]->setAngleD(_unit[_selectNum]->getAngleD() - 5);
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _unit[_selectNum]->setAccel(_unit[_selectNum]->getViewAccel());
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _unit[_selectNum]->setAccel(-_unit[_selectNum]->getViewAccel());
	else _unit[_selectNum]->setAccel(0);

	for (int i = 0; i < 3; i++)
	{
		if (_unit[i]->getSpeed() < 0)
		{
			_unit[i]->setAccel(0);
			_unit[i]->setSpeed(0);
		}
		if (_unit[i]->getSpeed() > _unit[i]->getMaxSpeed())
		{
			_unit[i]->setAccel(0);
			_unit[i]->setSpeed(_unit[i]->getMaxSpeed());
		}

		_unit[i]->update();

		if (_unit[i]->getRect().left < 10) _unit[i]->setX(10 + _unit[i]->getWidth() / 2);
		if (_unit[i]->getRect().right > _background->getWidth() - 10) _unit[i]->setX(_background->getWidth() - 10 - _unit[i]->getWidth() / 2);
		if (_unit[i]->getRect().top < 10) _unit[i]->setY(10 + _unit[i]->getHeight() / 2);
		if (_unit[i]->getRect().bottom > _background->getHeight() - 10) _unit[i]->setY(_background->getHeight() - 10 - _unit[i]->getHeight() / 2);
	}

	//_camera->setCenter();

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) _selectNum = 0;
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) _selectNum = 1;
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) _selectNum = 2;

	/*
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SpriteImage* image = IMAGEMANAGER->addImage("overload", "resource/starcraft/overlord.bmp", 1344, 336, TRUE, RGB(0, 255, 0))->createSprite(16, 4);
		_bullet->fire(Bullets::createBullet(image, _unit->getX(), _unit->getY(), _unit->getAngleR(), 1));
	}
	*/

	_bullet->update();
}
void StarcraftScene::render(void)
{
	_background->render(_camera->getMemDC());
	for (int i = 0; i < 3; i++) _unit[i]->render(_camera->getMemDC());
	_camera->render(getMemDC(), -_unit[_selectNum]->getX() + WIN_SIZE_X / 2, -_unit[_selectNum]->getY() + WIN_SIZE_Y / 2, 0, 0, WIN_SIZE_X, WIN_SIZE_Y);
	//_bullet->render();

	IMAGEMANAGER->render("map", getMemDC(), WIN_SIZE_X - _map->getWidth(), 0);

	for (int i = 0; i < 3; i++)
	{
		float ratioX = (float)_map->getWidth() / _background->getWidth();
		float ratioY = (float)_map->getHeight() / _background->getHeight();

		IMAGEMANAGER->render("map unit", getMemDC(), (WIN_SIZE_X - _map->getWidth()) - 5 + (_unit[i]->getX() * ratioX), -5 + (_unit[i]->getY() * ratioY));
	}
}