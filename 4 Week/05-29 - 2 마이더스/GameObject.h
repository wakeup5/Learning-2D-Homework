#pragma once
class GameObject
{
private:
	float _centerX;
	float _centerY;

	int _width;
	int _height;

	float _speedX;
	float _speedY;

	float _angleD;
	float _angleR;

	float _speed;

	Image* _image;
public:
	GameObject();
	~GameObject();

	void setPosition(POINT p) { _centerX = p.x, _centerY = p.y;}
	void setPosition(float x, float y) { _centerX = x, _centerY = y;}
	POINT getPosition(){ return POINT{ _centerX, _centerY }; }

	void setX(float x){ _centerX = x; }
	void setY(float y){ _centerY = y; }
	float getY(){ return _centerY; }
	float getX(){ return _centerX; }

	void setWidth(int width){ _width = width; }
	void setHeight(int height){ _height = height; }
	void setSize(int width, int height){ _width = width; _height = height; }

	int getWidth(){ return _width; }
	int getHeight(){ return _height; }
	RECT getRect(){ return makeRectCenter(_centerX, _centerY, _width, _height); }

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

	virtual void move();

	void setImage(Image* image){ _image = image; }
	Image* getImage(){ return _image; }
	//void initializeImage(std::string key, const char* fileName, int sourX, int sourY, int sourWidth, int sourHeight, bool trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	
	void render(HDC);
	//void spriteRenter(HDC);
};

