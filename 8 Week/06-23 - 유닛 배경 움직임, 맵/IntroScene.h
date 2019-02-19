#pragma once
#include "SceneManager.h"
class IntroScene : public Scene
{
private:
	Image* _image[3];
	int _selectNum;
public:
	IntroScene();
	~IntroScene();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
};

