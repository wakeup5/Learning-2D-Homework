#pragma once
#include "GameNode.h"
#include "Rocket.h"

class GameStudy :
	public GameNode
{
private:
	Rocket* _rocket;

public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
};
