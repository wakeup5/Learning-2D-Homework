#pragma once
#include "GameNode.h"
#include "Bullet.h"

#define PLAYER_SIZE 150
#define BALL_SIZE 100

using namespace std;

class GameStudy :
	public GameNode
{
private:
    POINT _player1, _player2;
    int _score1, _score2;
    RECT _goalpost1, _goalpost2;

    Bullet _ball;

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

