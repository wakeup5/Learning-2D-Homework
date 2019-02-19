#pragma once
#include "GameNode.h"

#define LENGTH_HOUR 75
#define LENGTH_MINITE 120
#define LENGTH_SECOND 140

#define WATCH_SIZE 300

using namespace std;

class GameStudy :
	public GameNode
{
private:
	time_t timer;
	struct tm t;

	double _hour;
	double _minite;
	double _second;

	POINT _hp;
	POINT _mp;
	POINT _sp;

	POINT _center;

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

