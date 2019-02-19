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
	//_pattern = NULL;
}
void Enemy::update(void)
{
	//printf("%d, ", );
	if (_pattern != NULL) _pattern(this, GetTickCount() - _createTickTime);
	move();

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
