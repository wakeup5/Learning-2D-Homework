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

	_bullet = new Bullet;
	_bullet->initialize(600, 1000, 1, IMAGEMANAGER->findImage("enemy bullet"), 2, 1);

	OBJECTMANAGER->addObject(GUID_ENEMYS_BULLET, _bullet);

	for (int j = 0; j < 5; j++)
	{
		HpEnemy* enemy = new HpEnemy;
		enemy->initialize(
			IMAGEMANAGER->findImage("ufo")->getSpriteImage(6, 2),
			RANDOM->getFloatTo(20, 100),
			IMAGEMANAGER->findImage("hp bar"),
			IMAGEMANAGER->findImage("hp bar back"),
			10);
		enemy->setPosition((WIN_SIZE_X / 2) + (j - 2) * 100, 200);
		enemy->setSize(50, 50);
		enemy->setAngleR(0);
		enemy->setSpeed(2);
		enemy->setHp(10);
		enemy->setPattern([](Enemy* self, float time)
		{
			if (self->getPatternState() == 0 && Pattern::movePattern(self, Pattern::PATTERN_MOVE_LEFT, new int(100))) self->setPatternState(1);
			if (self->getPatternState() == 1 && Pattern::movePattern(self, Pattern::PATTERN_MOVE_RIGHT, new int(WIN_SIZE_X - 100))) self->setPatternState(2);
			if (self->getPatternState() == 2 && Pattern::movePattern(self, Pattern::PATTERN_MOVE_LEFT, new int(WIN_SIZE_X / 2))) self->setPatternState(3);
			if (self->getPatternState() == 3 && Pattern::movePattern(self, Pattern::PATTERN_MOVE_DOWN, NULL, new int(500))) self->setPatternState(4);
			if (self->getPatternState() == 4 && Pattern::movePattern(self, Pattern::PATTERN_MOVE_UP, NULL, new int(200))) self->setPatternState(0);
		});

		_vEnemy.push_back(enemy);
	}

	OBJECTMANAGER->addObject(GUID_ENEMY_MANAGER, this);

	_isBoss = false;

	return S_OK;
}
void EnemyManager::release(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		(*_viEnemy)->release();
		SAFE_DELETE((*_viEnemy));
		_viEnemy = _vEnemy.erase(_viEnemy);
	}

	_vEnemy.clear();
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

	if (player != NULL && !_isBoss && TIMEMANAGER->addTimer("enemy bullet")->checkTime(1000))
	{
		for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
		{
			_bullet->fire((*_viEnemy)->getX(),
				(*_viEnemy)->getY(),
				myUtil::getGradeRadianByTwoPoint((*_viEnemy)->getX(), (*_viEnemy)->getY(), player->getX(), player->getY()),
				RANDOM->getFloatTo(2.0f, 4.1f));
		}
	}

	Bullet::VPBullet* vBullet = OBJECTMANAGER->findObject<Bullet>(GUID_PLAYER_BULLET)->getBullets();
	Bullet::VPBullet* vMissile = OBJECTMANAGER->findObject<Bullet>(GUID_PLAYER_MISSILE)->getBullets();
	Bullet::VPBullet* vTonado = OBJECTMANAGER->findObject<Bullet>(GUID_PLAYER_TONADO)->getBullets();
	Bullet::VPBullet* vPiece = OBJECTMANAGER->findObject<Bullet>(GUID_PLAYER_PIECE)->getBullets();
	
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		Bullet::collitionCheck<HpEnemy>(*_viEnemy, vBullet, [](HpEnemy* enemy, Bullet::BulletObject* bullet){
			enemy->setHp(enemy->getHp() - bullet->getDamage());
			EFFECTMANAGER->addEffect(
				IMAGEMANAGER->findImage("bullet up effect")
				->getSpriteImage(bullet->getX(), bullet->getRect().top, 17, 1));
		});

		Bullet::collitionCheck<HpEnemy>(*_viEnemy, vMissile, [](HpEnemy* enemy, Bullet::BulletObject* bullet){
			enemy->setHp(enemy->getHp() - bullet->getDamage());
			EFFECTMANAGER->addEffect(
				IMAGEMANAGER->findImage("missile down effect")
				->getSpriteImage(bullet->getX(), bullet->getRect().top, 15, 1));
		});

		Bullet::collitionCheck<HpEnemy>(*_viEnemy, vTonado, [](HpEnemy* enemy, Bullet::BulletObject* bullet){
			enemy->setHp(enemy->getHp() - bullet->getDamage());
			EFFECTMANAGER->addEffect(
				IMAGEMANAGER->findImage("bullet up effect")
				->getSpriteImage(bullet->getX(), bullet->getRect().top, 17, 1));
		});

		Bullet::collitionCheck<HpEnemy>(*_viEnemy, vPiece, [](HpEnemy* enemy, Bullet::BulletObject* bullet){
			enemy->setHp(enemy->getHp() - bullet->getDamage());
			EFFECTMANAGER->addEffect(
				IMAGEMANAGER->findImage("bullet up effect")
				->getSpriteImage(bullet->getX(), bullet->getRect().top, 17, 1));
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

	if (_vEnemy.empty())
	{
		if (!_isBoss)
		{
			HpEnemy* boss = new HpEnemy;
			boss->initialize(
				IMAGEMANAGER->findImage("boss")->getSpriteImage(8, 2),
				50,
				IMAGEMANAGER->findImage("boss hp bar"),
				IMAGEMANAGER->findImage("boss hp bar back"),
				2000);
			boss->setPosition(WIN_SIZE_X / 2, 200);
			boss->setSize(200, 220);
			boss->setAngleR(0);
			boss->setSpeed(0);

			Bullet* bullet = _bullet;

			boss->setPattern([boss, bullet, player](Enemy* self, float time)
			{
				boss->activate();

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
			_isBoss = true;
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