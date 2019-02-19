#pragma once
#include "SceneManager.h"
class EndingScene :
	public Scene
{
private:
	Image* _background;
public:
	EndingScene();
	~EndingScene();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
};

