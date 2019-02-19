#pragma once
#include "SceneManager.h"
#include "Unit.h"
#include "Button.h"

class IntroScene : public Scene
{
private:
	Image* _image[3];
	Button* _buttonU;
	Button* _buttonD;
	Button* _button;

	static Unit* _unit[3];
	static Unit* _view;
	static int _selectNum;
	static int _selectMenu;
public:
	IntroScene();
	~IntroScene();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void viewInfo();

	static void statusUp();
	static void statusDown();
	static void nextScene();
};

