#pragma once
#include "GameObject.h"
#include "Missile.h"
#include "GuideMissile.h"

//game value define
#define PLAYER_SPEED 5
#define PLAYER_HP 100

#define MAX_MISSILE 100
#define MAX_BASIC 10
#define MAX_SPECIAL_1 15
#define MAX_SPECIAL_2 10
#define MAX_SPECIAL_3 4

#define COOLTIME_BASIC 50
#define COOLTIME_SPECIAL_1 100
#define COOLTIME_SPECIAL_2 70
#define COOLTIME_SPECIAL_3 70

#define SPECIAL_2_COOLTIME 3000

#define SPEED_BASIC 10
#define SPEED_SPECIAL_1 7
#define SPEED_SPECIAL_2 8
#define SPEED_SPECIAL_3 12

#define SHIELD_HP 200
#define SHIELD_COOLTIME 2000

class Player : public GameObject
{
private:
	int _speed = PLAYER_SPEED;
	float _hp = PLAYER_HP;
	bool _isDead = false;

	int _weaponMode = 0;

	int _maxBasic = MAX_BASIC;
	int _maxSpecial1 = MAX_SPECIAL_1;
	int _maxSpecial2 = MAX_SPECIAL_2;
	int _maxSpecial3 = MAX_SPECIAL_3;

	int _cooltimeBasic = COOLTIME_BASIC;
	int _cooltimeSpecial1 = COOLTIME_SPECIAL_1;
	int _cooltimeSpecial2L = COOLTIME_SPECIAL_2;
	int _cooltimeSpecial2R = COOLTIME_SPECIAL_2;
	int _cooltimeSpecial3 = COOLTIME_SPECIAL_3;
	
	Missile _basicBullets[MAX_BASIC];
	Missile _special1Bullets[MAX_SPECIAL_1];

	float _smallLeftHp = 100;
	float _smallRightHp = 100;
	GameObject _smallLeft;
	GameObject _smallRight;
	Missile _special2LBullets[MAX_SPECIAL_2];
	Missile _special2RBullets[MAX_SPECIAL_2];

	GuideMissile _special3Bullets[MAX_SPECIAL_3];

	int _special2Cooltime = 0;

	int _shieldCooltime = 0;
	int _shieldHp = 0;

public:
	Player();
	~Player();

	void setSpeed(int speed){ _speed = speed; }
	int getSpeed(){ return _speed;}
	bool getIsDead(){ return _isDead; }

	void damageHp();
	void recoveryHp();
	int getHp(){ return _hp; }

	void setMode(int);

	void printBullet(HDC);

	bool fire(Enemy* = NULL);

	bool fireBasic();
	bool fireSpecial1();
	bool fireSpecial2();
	bool fireSpecial3(Enemy*);

	void shield();
	void shieldDamage();

	void update();

	void move(int, int);

	bool collision(RECT);
};

