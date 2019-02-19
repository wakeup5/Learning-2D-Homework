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
	GameObject::initialize(WIN_SIZE_X / 2, WIN_SIZE_Y - 100, 50, 50, 0, 0);

	_image = IMAGEMANAGER->addImage("rocket", "resource/slug.bmp", 52, 64, TRUE, RGB(255, 0, 255));
	_boostImage = IMAGEMANAGER->addSpriteImage("rocket boost", "resource/boost.bmp", 200, 298, 5, 1, TRUE, RGB(255, 0, 255));

	_missile = new Missile;
	_missile->initialize(100, 600);
	OBJECTMANAGER->addObject("player2 missile", _missile);

	_bullet = new Bullet;
	_bullet->initialize(200, 400, "resource/missile.bmp", 2, 1);
	OBJECTMANAGER->addObject("player3 bullet", _bullet);

	_hp = 200;

	return S_OK;
}
void Rocket::release()
{
	//_missile->release();
	//_bullet->release();
}
void Rocket::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && getRect().left > 0)
	{
		setX(getX() - 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && getRect().right < WIN_SIZE_X)
	{
		setX(getX() + 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && getRect().top > 0)
	{
		setY(getY() - 3);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && getRect().bottom < WIN_SIZE_Y)
	{
		setY(getY() + 3);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missile->fire(getX(), getY() - 50);
	}

	if (KEYMANAGER->isStayKeyDown('1'))
	{
		_bullet->fire(getX(), getY() - 50, RANDOM->getFloatTo(M_PI / 4, M_PI * 3 / 4), RANDOM->getIntTo(5, 15));
		/*
		_bullet->fire(getX(), getY() - 50, M_PI * 1 / 4, RANDOM->getIntTo(2, 10));
		_bullet->fire(getX(), getY() - 50, M_PI * 1.5 / 4, RANDOM->getIntTo(2, 10));
		_bullet->fire(getX(), getY() - 50, M_PI * 2.5 / 4, RANDOM->getIntTo(2, 10));
		_bullet->fire(getX(), getY() - 50, M_PI * 3 / 4, RANDOM->getIntTo(2, 10));
		*/
	}

	_image->setCenter(getX(), getY());
	
	_boostImage->nextFrameX(20);
	_boostImage->setCenter(getX(), getY() + 185);

	//총알로 적 충돌처리 해서 죽이기
	Enemy::VPEnemy* enemys = static_cast<Enemy*>(OBJECTMANAGER->findObject("enemy 1"))->getEnemys();
	Bullet::VPBullet* bullets = _bullet->getBullets();
	RECT r;
	for (Enemy::VIPEnemy viEnemy = enemys->begin(); viEnemy != enemys->end();)
	{
		bool isDead = false;
		for (Bullet::VIPBullet viBullet = bullets->begin(); viBullet != bullets->end();)
		{
			if (IntersectRect(&r, &(*viEnemy)->getRect(), &viBullet->getRect()))
			{
				SAFE_DELETE(*viEnemy);
				isDead = true;
				viEnemy = enemys->erase(viEnemy);
				
				viBullet = bullets->erase(viBullet);
				break;
			}
			else
			{
				viBullet++;
			}
		}
		if (!isDead) viEnemy++;
	}

	Missile::VPMissile* missile = _missile->getMissiles();
	for (Enemy::VIPEnemy viEnemy = enemys->begin(); viEnemy != enemys->end();)
	{
		bool isDead = false;
		for (Missile::VIPMissile vimissile = missile->begin(); vimissile != missile->end();)
		{
			if (IntersectRect(&r, &(*viEnemy)->getRect(), &vimissile->getRect()))
			{
				SAFE_DELETE(*viEnemy);
				isDead = true;
				viEnemy = enemys->erase(viEnemy);

				vimissile = missile->erase(vimissile);
				break;
			}
			else
			{
				vimissile++;
			}
		}
		if (!isDead) viEnemy++;
	}

}
void Rocket::render()
{
	_image->render(getMemDC());
	_boostImage->render(getMemDC());

	//_missile->render();
	//_bullet->render();
}