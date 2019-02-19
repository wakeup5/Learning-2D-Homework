#pragma once
#include "Unit.h"

class Zergling : public Unit
{
public:
	Zergling();
	~Zergling();

	virtual HRESULT initialize(float x, float y, float angleD, float speed);
	virtual void release(void);

	virtual void move();
	virtual void draw(HDC);
	virtual void frame();
};

