#pragma once
#include "GameNode.h"
#include "Bullet.h"

#define MISSILE_SPEED 10
#define MISSILE_SIZE 30
#define MAX_MISSILE 16

#define HOLE_SIZE MISSILE_SIZE * 2

#define GUIDELINE_MAX 200

using namespace std;

class GameStudy :
    public GameNode
{
private:
    struct PointFloat
    {
        float x;
        float y;
        bool isView;
    };
    Bullet _bullet[MAX_MISSILE];
    UINT _colors[8];
    RECT _table;
    POINT _hole[6];

    int _player[2][8];
    bool _isAttack;

    //int _guideLineLength = GUIDELINE_LENGTH;
    PointFloat _guideLine[GUIDELINE_MAX];

    int _turn;

    float _power;
    float _mouseR;
    bool _isClick;

public:
    virtual HRESULT initialize(void);
    virtual void release(void);
    virtual void update(void);
    virtual void render(HDC hdc);

    void gameInit();

    GameStudy(){}
    virtual ~GameStudy(){}
};

