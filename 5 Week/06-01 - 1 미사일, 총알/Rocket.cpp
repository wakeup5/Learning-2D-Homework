#include "stdafx.h"
#include "Rocket.h"


Rocket::Rocket()
{
}


Rocket::~Rocket()
{
}

HRESULT Rocket::initialize()
{
	GameNode::initialize();
	//getInfo()->setPosition(WIN_SIZE_X / 2, WIN_SIZE_Y - 100);
	//getInfo()->setSize(50, 50);

	_info.initialize(WIN_SIZE_X / 2, WIN_SIZE_Y - 100, 50, 50, 0, 0);
	
	_image = IMAGEMANAGER->addImage("rocket", "resource/slug.bmp", 52, 64, TRUE, RGB(255, 0, 255));
	_boostImage = IMAGEMANAGER->addSpriteImage("rocket boost", "resource/boost.bmp", 200, 298, 5, 1, TRUE, RGB(255, 0, 255));

	_missile = new Missile;
	_missile->initialize(10, 400);

	_bullet = new Bullet;
	_bullet->initialize(200, 200);

	return S_OK;
}
void Rocket::release()
{
	_missile->release();
	_bullet->release();
}
void Rocket::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_info.setX(_info.getX() - 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_info.setX(_info.getX() + 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_info.setY(_info.getY() - 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_info.setY(_info.getY() + 3);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missile->fire(_info.getX(), _info.getY() - 50);
	}

	if (KEYMANAGER->isStayKeyDown('1'))
	{
		_bullet->fire(_info.getX(), _info.getY() - 50, M_PI / 2);
		_bullet->fire(_info.getX(), _info.getY() - 50, M_PI * 1 / 4);
		_bullet->fire(_info.getX(), _info.getY() - 50, M_PI * 1.5 / 4);
		_bullet->fire(_info.getX(), _info.getY() - 50, M_PI * 2.5 / 4);
		_bullet->fire(_info.getX(), _info.getY() - 50, M_PI * 3 / 4);
	}

	_image->setCenter(_info.getX(), _info.getY());

	_boostImage->nextFrameX(2);
	_boostImage->setCenter(_info.getX(), _info.getY() + 185);

	_missile->update();
	_bullet->update();
}
void Rocket::render()
{
	_image->render(getMemDC());
	_boostImage->render(getMemDC());

	_missile->render();
	_bullet->render();
}