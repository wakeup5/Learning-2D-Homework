#pragma once
class GameObject
{
protected:
	POINT _point;
	int _width, _height;

public:
	GameObject();
	virtual ~GameObject();

	virtual void setPosition(POINT p){ _point = p; }
	virtual POINT getPosition(){ return _point; }

	virtual void setSize(int width, int height){ _width = width; _height = height; }
	virtual RECT getSize();

	virtual void move(int x, int y);
	virtual void moveX(int x);
	virtual void moveY(int y);

	virtual void update(){}

};

