#include "stdafx.h"
#include "EnemyManager.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::initialize()
{
	GameNode::initialize();

	for (int j = 0; j < 5; j++)
	{
		HpEnemy* enemy = new HpEnemy;
		enemy->initialize(
			IMAGEMANAGER->addSpriteImage("ufo", "resource/enemy.bmp", 306, 58, 6, 2, TRUE, RGB(255, 0, 255)),
			RANDOM->getFloatTo(20, 100),
			IMAGEMANAGER->addImage("hp bar", "resource/hp bar.bmp", 50, 4),
			10);
		enemy->setPosition((WIN_SIZE_X / 2) + (j - 2) * 100, 200);
		enemy->setSize(50, 50);
		enemy->setAngleR(0);
		enemy->setSpeed(1);
		enemy->setHp(10);
		_vEnemy.push_back(enemy);
	}

	for (int j = 0; j < 5; j++)
	{
		HpEnemy* enemy = new HpEnemy;
		enemy->initialize(
			IMAGEMANAGER->addSpriteImage("ufo", "resource/enemy.bmp", 306, 58, 6, 2, TRUE, RGB(255, 0, 255)),
			RANDOM->getFloatTo(20, 100),
			IMAGEMANAGER->addImage("hp bar", "resource/hp bar.bmp", 50, 4),
			10);
		enemy->setPosition(WIN_SIZE_X / 2 + (j - 2) * 50, 300);
		enemy->setSize(50, 50);
		enemy->setAngleR(0);
		enemy->setSpeed(1);
		enemy->setHp(10);
		_vEnemy.push_back(enemy);
	}

	for (int j = 0; j < 5; j++)
	{
		HpEnemy* enemy = new HpEnemy;
		enemy->initialize(
			IMAGEMANAGER->addSpriteImage("ufo", "resource/enemy.bmp", 306, 58, 6, 2, TRUE, RGB(255, 0, 255)),
			RANDOM->getFloatTo(20, 100),
			IMAGEMANAGER->addImage("hp bar", "resource/hp bar.bmp", 50, 4),
			10);
		enemy->setPosition(200 + j * 50, 100);
		enemy->setSize(50, 50);
		enemy->setAngleR(0);
		enemy->setSpeed(1.5);
		enemy->setHp(10);
		_vEnemy.push_back(enemy);
	}

	OBJECTMANAGER->addObject(GUID_ENEMY_MANAGER, this);

	_bullet = new Bullet;
	_bullet->initialize(60, 1000, IMAGEMANAGER->addImage("enemy bullet", "resource/enemy bullet.bmp", 16, 8, TRUE, RGB(255, 0, 255)), 2, 1);

	OBJECTMANAGER->addObject(GUID_ENEMYS_BULLET, _bullet);

	_bulletTimer = new Timer;
	_bulletTimer->initialize(1000);

	return S_OK;
}
void EnemyManager::release(void)
{

}
void EnemyManager::update(void)
{
	GameNode::update();

	static int t = 0;
	t++;
	int i = 0;
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++, i++)
	{
		(*_viEnemy)->update();
		if (i < 5)
		{
			if ((*_viEnemy)->getY() > WIN_SIZE_Y - 100 ||
				(*_viEnemy)->getY() < 100 ||
				(*_viEnemy)->getX() > WIN_SIZE_X - 100 ||
				(*_viEnemy)->getX() < 100)
			{
				(*_viEnemy)->setAngleD((*_viEnemy)->getAngleD() + 3);
			}
		}
		else if (i >= 5 && i < 10)
		{
			if (t % 100 < 50)
			{
				(*_viEnemy)->setAngleR(0);
			}
			else
			{
				(*_viEnemy)->setAngleR(M_PI);
			}
			//(*_viEnemy)->setSpeed(t);
		}
		else
		{
			if ((*_viEnemy)->getX() < WIN_SIZE_X / 2)
			{
				if ((*_viEnemy)->getAngleD() != 0)
				{
					(*_viEnemy)->setAngleD((*_viEnemy)->getAngleD() - 0.41);
				}
			}
			else
			{
				if ((*_viEnemy)->getAngleD() != 180)
				{
					(*_viEnemy)->setAngleD((*_viEnemy)->getAngleD() - 0.41);
				}
			}
			//(*_viEnemy)->setAngleD((*_viEnemy)->getAngleD() + 3);
		}

		//충돌처리
	}

	//플레이어 정보
	Player* player = OBJECTMANAGER->findObject<Player>(GUID_PLAYER);

	if (player && _bulletTimer->getTiming())
	{
		for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
		{
			_bullet->fire((*_viEnemy)->getX(),
				(*_viEnemy)->getY(),
				myUtil::getGradeRadianByTwoPoint((*_viEnemy)->getX(), (*_viEnemy)->getY(), player->getX(), player->getY()),
				2);
		}
	}

	Bullet* pBullet = OBJECTMANAGER->findObject<Bullet>(GUID_PLAYER_BULLET);
	Bullet* pMissile = OBJECTMANAGER->findObject<Bullet>(GUID_PLAYER_MISSILE);

	Bullet::VPBullet* vBullet = pBullet->getBullets();
	Bullet::VIPBullet viBullet;

	Bullet::VPBullet* vMissile = pMissile->getBullets();
	Bullet::VIPBullet viMissile;

	RECT r;

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		//플레이어 총과 적 충돌처리
		for (viBullet = vBullet->begin(); viBullet != vBullet->end();)
		{
			if (IntersectRect(&r, &(*_viEnemy)->getRect(), &(*viBullet)->getRect()))
			{
				(*_viEnemy)->setHp((*_viEnemy)->getHp() - 1);
				viBullet = vBullet->erase(viBullet);
				//break;
			}
			else
			{
				viBullet++;
			}
		}

		if ((*_viEnemy)->getHp() <= 0)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else
		{
			_viEnemy++;
		}
	}

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		for (viMissile = vMissile->begin(); viMissile != vMissile->end();)
		{
			if (IntersectRect(&r, &(*_viEnemy)->getRect(), &(*viMissile)->getRect()))
			{
				(*_viEnemy)->setHp((*_viEnemy)->getHp() - 2);
				viMissile = vMissile->erase(viMissile);
				//break;
			}
			else
			{
				viMissile++;
			}
		}

		if ((*_viEnemy)->getHp() <= 0)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else
		{
			_viEnemy++;
		}
	}

	_bullet->update();
}
void EnemyManager::render(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->render();
	}

	_bullet->render();
}