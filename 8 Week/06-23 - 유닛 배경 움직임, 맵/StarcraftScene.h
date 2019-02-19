#pragma once
#include "SceneManager.h"
#include "Marine.h"

class StarcraftScene :
	public Scene
{
private:
	Image* _background;
	Image* _map;
	Marine* _marine;
public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	StarcraftScene();
	~StarcraftScene();
};

