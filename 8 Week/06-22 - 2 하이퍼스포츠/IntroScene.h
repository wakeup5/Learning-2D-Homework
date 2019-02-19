#pragma once
#include "SceneManager.h"
class IntroScene :
	public Scene
{
private:
	Image* _background;
public:
	IntroScene();
	~IntroScene();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
};

