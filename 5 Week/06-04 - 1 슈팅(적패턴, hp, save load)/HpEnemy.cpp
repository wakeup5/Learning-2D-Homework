#include "stdafx.h"
#include "HpEnemy.h"


HpEnemy::HpEnemy()
{
}


HpEnemy::~HpEnemy()
{
}
HRESULT HpEnemy::initialize(SpriteImage* image, float frameTime, Image* hpImage, int maxHp)
{
	Enemy::initialize(image, frameTime);

	_maxHp = maxHp;
	_hp = maxHp;

	_hpBar.initialize(hpImage, &_centerX, &_centerY, &_hp, maxHp);

	return S_OK;
}
void HpEnemy::release(void)
{

}
void HpEnemy::update(void)
{
	Enemy::update();
}
void HpEnemy::render(void)
{
	Enemy::render();

}

void HpEnemy::move()
{
	_hpBar.update();
	_hpBar.setDiff(0, -(getHeight() / 2));
}
void HpEnemy::draw()
{
	Enemy::draw();
	_hpBar.render();
}
