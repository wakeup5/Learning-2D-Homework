#pragma once
class Bullet
{
private:
	float _positionX;
	float _positionY;
	
	float _speedX;
	float _speedY;

	float _angleD;
	float _angleR;

	float _speed;

public:
	Bullet();
	~Bullet();

	void setPosition(POINT p) { _positionX = p.x, _positionY = p.y; }
	POINT getPosition(){ return POINT{ _positionX, _positionY }; }

	float getPositionY(){ return _positionY; }
	float getPositionX(){ return _positionX; }

	void setAngleD(float angleD);
	float getAngleD();

	void setAngleR(float angleR);
	float getAngleR();

	void setSpeedX(float speedX);
	float getSpeedX();

	void setSpeedY(float speedY);   
	float getSpeedY();

	void setSpeed(float speed);
	float getSpeed();

	void move();
	void moveGravity();

	bool isFire = false;
};

