#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Enemy.h"

#define MAX_ENEMY 20

using namespace std;

class GameStudy :
	public GameNode
{
private:
	POINTRECT _ellipse;
	POINTRECT _rectangle;

	Player _player;
	Enemy _enemys[MAX_ENEMY];

	int _score = 0;

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

