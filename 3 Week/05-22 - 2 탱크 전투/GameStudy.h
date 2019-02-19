#pragma once
#include "GameNode.h"
#include "Bullet.h"
#include "Tank.h"

#define MAX_ENEMY 5
#define MAX_BULLET 100

using namespace std;

class GameStudy :
    public GameNode
{
private:
    Tank _player;
    Bullet _bullet[MAX_BULLET];
    int _playerHp;

    Tank _enemy[MAX_ENEMY];
    Bullet _enemyBullet[MAX_ENEMY];

public:
    virtual HRESULT initialize(void);
    virtual void release(void);
    virtual void update(void);
    virtual void render(HDC hdc);

    void gameInit();

    GameStudy(){}
    virtual ~GameStudy(){}
};

