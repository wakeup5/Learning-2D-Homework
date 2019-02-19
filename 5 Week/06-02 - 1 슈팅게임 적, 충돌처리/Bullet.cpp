#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

HRESULT Bullet::initialize(int max, float range, const char* fileName, int frameCol, int frameRow)
{
	GameNode::initialize();

	_max = max;
	_range = range;

	char a[128];
	static int aa = 0; 
	sprintf_s(a, "bullet %d", aa++);

	_image = IMAGEMANAGER->addImage(a, "resource/enemy bullet.bmp", 16, 8, TRUE, RGB(255, 0, 255));

	_frameCol = frameCol;
	_frameRow = frameRow;

	return S_OK;
}
void Bullet::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet = _vBullet.erase(_viBullet);
	}

	_vBullet.clear();
}

void Bullet::update()
{
	GameNode::update();

	move();
}
void Bullet::render()
{
	draw();
}

void Bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->move();

		float x = _viBullet->getX();
		float y = _viBullet->getY();

		_viBullet->image->setCenter(x, y);
		_viBullet->image->nextFrame(50);

		//라이프 타임
		if (_range < myUtil::getDistanceByTwoPoint(_viBullet->startX, _viBullet->startY, x, y))
		{
			//SAFE_RELEASE(_viBullet->image);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			_viBullet++;
		}
	}
}
void Bullet::draw()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->image->render(getMemDC());
	}
}
void Bullet::fire(float startX, float startY, float angleR, float speed)
{
	if (_vBullet.size() < _max)
	{
		Bullet::BulletObject bullet;
		bullet.image = _image->getSpriteImage(_frameCol, _frameRow);

		bullet.setAngleR(angleR);
		bullet.setSpeed(speed);

		bullet.setSize(bullet.image->getFrameWidth(), bullet.image->getFrameHeight());
		bullet.setPosition(startX, startY);
		bullet.startX = startX;
		bullet.startY = startY;

		_vBullet.push_back(bullet);

	}
}
