#pragma once
#include "SceneManager.h"
#include "Marine.h"
#include "Zergling.h"
#include "Scourge.h"
#include "Bullets.h"

class StarcraftScene : public Scene
{
private:
	Image* _background;
	Image* _map;
	Unit* _unit[3];
	int _selectNum;

	Image* _camera;

	Bullets* _bullet;
public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	StarcraftScene();
	~StarcraftScene();
};

