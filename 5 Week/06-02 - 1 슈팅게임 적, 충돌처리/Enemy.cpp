#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{

}


Enemy::~Enemy()
{

}

HRESULT Enemy::initialize()
{
	GameNode::initialize();
	Image* image = IMAGEMANAGER->addImage("enemy", "resource/enemy.bmp", 306, 58, TRUE, RGB(255, 0, 255));
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Enemy::Object* enemy = new Enemy::Object;
			enemy->setPosition(WIN_SIZE_X / 2 + 70 * (j - 2), 100 + 50 * i);
			enemy->image = image->getSpriteImage(6, 2);
			enemy->setSize(enemy->image->getFrameWidth(), enemy->image->getFrameHeight());
			enemy->bullet = new Bullet;
			enemy->bullet->initialize(1, 600, "resource/enemy bullet.bmp", 2, 1);

			char str[128];
			sprintf_s(str, "enemy bullet %d", i * 5 + j);
			OBJECTMANAGER->addObject(std::string(str), enemy->bullet);
			
			_vEnemy.push_back(enemy);
		}
	}

	return S_OK;
}
void Enemy::release(void)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		SAFE_DELETE(*_viEnemy);
		_viEnemy = _vEnemy.erase(_viEnemy);
	}

	_vEnemy.clear();
}
void Enemy::update(void)
{
	GameNode::update();
	move();
}
void Enemy::render()
{
	draw();
}

void Enemy::move()
{
	Rocket* player = static_cast<Rocket*>(OBJECTMANAGER->findObject("player 1 rocket"));
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->image->nextFrame(30);
		(*_viEnemy)->image->setCenter((*_viEnemy)->getX(), (*_viEnemy)->getY());
		if (player)
		{
			(*_viEnemy)->bullet->fire(
				(*_viEnemy)->getX(),
				(*_viEnemy)->getY(),
				myUtil::getGradeRadianByTwoPoint((*_viEnemy)->getX(), (*_viEnemy)->getY(), player->getX(), player->getY()),
				10.0f);
		}
	}
	if (player == NULL) return;

	vector<Bullet::BulletObject>* v;
	RECT r;
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		v = (*_viEnemy)->bullet->getBullets();
		for (auto i = v->begin(); i != v->end();)
		{
			if (IntersectRect(&r, &player->getRect(), &i->getRect()))
			{
				player->setHp(player->getHp() - 1);
				i = v->erase(i);
			}
			else
			{
				i++;
			}
		}
	}

	if (player->getHp() <= 0)
	{
		OBJECTMANAGER->removeObject("player 1 rocket");
	}


}
void Enemy::draw()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); _viEnemy++)
	{
		(*_viEnemy)->image->render(getMemDC());
	}
}