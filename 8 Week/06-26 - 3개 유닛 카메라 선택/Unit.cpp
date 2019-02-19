#include "stdafx.h"
#include "Unit.h"


Unit::Unit()
{
}


Unit::~Unit()
{
}

HRESULT Unit::initialize(SpriteImage* image, float centerX, float centerY, int width, int height, float angleD, float speed)
{
	GameObject::initialize(centerX, centerY, width, height, angleD, speed);

	_image = image;
	_image->setCenter(centerX, centerY);

	_hpBar = new ProgressBar;
	_mpBar = new ProgressBar;

	_walkTimer = TIMEMANAGER->addTimer();
	_walkTime = 2000;

	return S_OK;
}
void Unit::release(void)
{
	SAFE_RELEASE(_hpBar);
	SAFE_RELEASE(_mpBar);
}
void Unit::update(void)
{
	//물리 값 업데이트
	GameObject::activate();
	//움직임
	move();
	//프레임 적용
	frame();

	float insideAngle = 180 / (_image->getMaxFrameX() + 1);
	_image->setFrameX((getAngleD() + insideAngle) / 360 * (_image->getMaxFrameX() + 1));
	_image->setCenter(getX(), getY());

	if (getSpeed() != 0 && _walkTimer->checkTime(_walkTime / getSpeed())) _image->nextFrameY();

	//프로그레스 바 적용
	_hpBar->update();
	_hpBar->setCenter(getX(), getY());
	_hpBar->setInfo(_maxHP, _HP);
	
	_mpBar->update();
	_mpBar->setCenter(getX(), getY());
	_mpBar->setInfo(_maxMP, _MP);
}
void Unit::render(HDC hdc)
{
	draw(hdc);
	_hpBar->render(hdc);
	_mpBar->render(hdc);

	_image->render(hdc);
}

void Unit::move()
{
	
}
void Unit::frame()
{

}
void Unit::draw(HDC hdc)
{
	
}
