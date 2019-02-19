#pragma once
#include "GameNode.h"
#include "JangGi.h"

class GameStudy : public GameNode
{
private:

public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void imageLoad();

};
