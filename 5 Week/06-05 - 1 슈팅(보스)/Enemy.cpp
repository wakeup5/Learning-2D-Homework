#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{

}
HRESULT Enemy::initialize(SpriteImage* image, float frameTime)
{
	GameNode::initialize();
	GameObject::initialize(0, 0);

	_image = image;
	_frameTime = frameTime;
	_createTickTime = GetTickCount();

	return S_OK;
}
void Enemy::release(void)
{

}
void Enemy::update(void)
{
	if (_pattern != NULL) _pattern(GetTickCount() - _createTickTime);
	move();

	GameObject::activate();

	_image->nextFrame(_frameTime);
	_image->setCenter(getX(), getY());
}
void Enemy::render(void)
{
	draw();
}

void Enemy::move()
{

}
void Enemy::draw()
{
	_image->render(getMemDC());
}
