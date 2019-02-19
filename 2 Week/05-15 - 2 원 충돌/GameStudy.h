#pragma once
#include "GameNode.h"

#define MAX_ENEMY 20

using namespace std;

class GameStudy :
	public GameNode
{
private:
	POINTRECT _ellipse;
	POINTRECT _rectangle;
	POINTRECT _rectangleS;

	bool _isClick = false, _isClickS = false;
	int dx, dy;

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

