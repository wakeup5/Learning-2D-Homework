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
			IMAGEMANAGER->addImage("hp bar back", "resource/hp bar back.bmp", 50, 4),
			10);
		enemy->setPosition((WIN_SIZE_X / 2) + (j - 2) * 100, 200);
		enemy->setSize(50, 50);
		enemy->setAngleR(0);
		enemy->setSpeed(2);
		enemy->setHp(10);
		enemy->setPattern([enemy](float time)
		{
			if (int(time) % 1000 < 500)
				enemy->setAngleR(enemy->getAngleR() + 0.1);
		});
		_vEnemy.push_back(enemy);
	}

	OBJECTMANAGER->addObject(GUID_ENEMY_MANAGER, this);

	_bullet = new Bullet;
	_bullet->initialize(600, 1000, 1, IMAGEMANAGER->addImage("enemy bullet", "resource/enemy bullet.bmp", 16, 8, TRUE, RGB(255, 0, 255)), 2, 1);

	OBJECTMANAGER->addObject(GUID_ENEMYS_BULLET, _bullet);

	_bulletTimer = new Timer;
	_bulletTimer->initialize(500);

	return S_OK;
}
void EnemyManager::release(void)
{

}
void EnemyManager::update(void)
{
	GameNode::update();

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->update();
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

	Bullet::VPBullet* vBullet = OBJECTMANAGER->findObject<Bullet>(GUID_PLAYER_BULLET)->getBullets();
	Bullet::VPBullet* vMissile = OBJECTMANAGER->findObject<Bullet>(GUID_PLAYER_MISSILE)->getBullets();
	Bullet::VPBullet* vTonado = OBJECTMANAGER->findObject<Bullet>(GUID_PLAYER_TONADO)->getBullets();
	Bullet::VPBullet* vpiece = OBJECTMANAGER->findObject<Bullet>(GUID_PLAYER_PIECE)->getBullets();
	
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		Bullet::collitionCheck<HpEnemy>(vBullet, *_viEnemy, [](HpEnemy* enemy, Bullet::BulletObject* bullet){
			enemy->setHp(enemy->getHp() - bullet->getDamage());
		});

		Bullet::collitionCheck<HpEnemy>(vMissile, *_viEnemy, [](HpEnemy* enemy, Bullet::BulletObject* bullet){
			enemy->setHp(enemy->getHp() - bullet->getDamage());
		});

		Bullet::collitionCheck<HpEnemy>(vTonado, *_viEnemy, [](HpEnemy* enemy, Bullet::BulletObject* bullet){
			enemy->setHp(enemy->getHp() - bullet->getDamage());
		});

		Bullet::collitionCheck<HpEnemy>(vpiece, *_viEnemy, [](HpEnemy* enemy, Bullet::BulletObject* bullet){
			enemy->setHp(enemy->getHp() - bullet->getDamage());
		});

		if ((*_viEnemy)->getHp() <= 0)
		{
			SAFE_DELETE(*_viEnemy);
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else
		{
			_viEnemy++;
		}
	}

	static bool isBossInit = false;
	if (_vEnemy.empty())
	{
		if (!isBossInit)
		{
			HpEnemy* boss = new HpEnemy;
			boss->initialize(
				IMAGEMANAGER->addSpriteImage("boss", "resource/boss.bmp", 1685, 400, 8, 2, TRUE, RGB(255, 0, 255)),
				50,
				IMAGEMANAGER->addImage("boss hp bar", "resource/hp bar.bmp", 300, 8),
				IMAGEMANAGER->addImage("boss hp bar back", "resource/hp bar back.bmp", 300, 8),
				2000);
			boss->setPosition(WIN_SIZE_X / 2, 200);
			boss->setSize(200, 220);
			boss->setAngleR(0);
			boss->setSpeed(0);

			Bullet* bullet = _bullet;

			boss->setPattern([boss, bullet, player](float time)
			{
				int t = (static_cast<int>(time) / 100) % 150;
				
				static int p = 0;
				static bool attack1 = false;
				static bool attack2 = false;
				static bool attack3 = false;

				printf("%d \n", t);

				if (t == 0)
				{
					attack1 = false;
					attack2 = false;
					attack3 = false;
				}

				if (t == 20)
				{
					boss->setSpeed(2);
					boss->setAngleD(0);

					for (int i = 0; i < 30; i++)
					{
						bullet->fire(boss->getX(), boss->getY(), (float(i) / 30) * 2 * M_PI, 3);
					}
				}
				if (t == 30)
				{
					boss->setAngleD(180);

					for (int i = 0; i < 30; i++)
					{
						bullet->fire(boss->getX(), boss->getY(), (float(i) / 30) * 2 * M_PI, 3);
					}
				}
				if (t == 50)
				{
					boss->setAngleD(0);

					for (int i = 0; i < 30; i++)
					{
						bullet->fire(boss->getX(), boss->getY(), (float(i) / 30) * 2 * M_PI, 3);
					}
				}
				if (t == 60)
				{
					boss->setSpeed(0);
				}
				if (t == 70)
				{
					boss->setSpeed(3);
					boss->setAngleD(270);
					if (!attack1)
						for (int i = 0; i < 10; i++)
						{
							bullet->fire(boss->getX(), boss->getY(), 
								myUtil::getGradeRadianByTwoPoint(boss->getX(), boss->getY(), player->getX(), player->getY()) + (i - 5) * 0.2,
								5);
						}
					attack1 = true;
				}
				if (t == 72 || t == 74)
				{
					for (int i = 0; i < 10; i++)
					{
						bullet->fire(boss->getX(), boss->getY(),
							myUtil::getGradeRadianByTwoPoint(boss->getX(), boss->getY(), player->getX(), player->getY()) + (i - 5) * 0.2,
							5);
					}
				}
				if (t == 85)
				{
					boss->setAngleD(90);
				}
				if (t == 100)
				{
					boss->setSpeed(0);
				}
				
				if (t > 100 && t < 150)
				{
					if (t % 5 < 1)
					{
						bullet->fire(boss->getX(), boss->getY(),
							myUtil::getGradeRadianByTwoPoint(boss->getX(), boss->getY(), player->getX(), player->getY()),
							10);
					}
				}

			});

			_vEnemy.push_back(boss);
			isBossInit = true;
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