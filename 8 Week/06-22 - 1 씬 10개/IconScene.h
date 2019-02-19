#pragma once
#include "SceneManager.h"
class IconScene : public Scene
{
private:
	static Image* _icon[10];
protected:
	static int _selectNum;
	Image* _background;
public:
	IconScene();
	~IconScene();

	virtual HRESULT initialize(void) = 0;
	virtual void release(void) = 0;
	virtual void update(void);
	virtual void render(void);

	virtual void renew(void) = 0;
	virtual void draw(void) = 0;
};

class IconScene1 : public IconScene
{
public:
	IconScene1(){}
	~IconScene1(){}
	virtual HRESULT initialize(void);
	virtual void release(void);

	virtual void renew(void);
	virtual void draw(void);
};
class IconScene2 : public IconScene
{
public:
	IconScene2(){}
	~IconScene2(){}
	virtual HRESULT initialize(void);
	virtual void release(void);

	virtual void renew(void);
	virtual void draw(void);
};
class IconScene3 : public IconScene
{
public:
	IconScene3(){}
	~IconScene3(){}
	virtual HRESULT initialize(void);
	virtual void release(void);

	virtual void renew(void);
	virtual void draw(void);
};
class IconScene4 : public IconScene
{
public:
	IconScene4(){}
	~IconScene4(){}
	virtual HRESULT initialize(void);
	virtual void release(void);

	virtual void renew(void);
	virtual void draw(void);
};
class IconScene5 : public IconScene
{
public:
	IconScene5(){}
	~IconScene5(){}
	virtual HRESULT initialize(void);
	virtual void release(void);

	virtual void renew(void);
	virtual void draw(void);
};
class IconScene6 : public IconScene
{
public:
	IconScene6(){}
	~IconScene6(){}
	virtual HRESULT initialize(void);
	virtual void release(void);

	virtual void renew(void);
	virtual void draw(void);
};
class IconScene7 : public IconScene
{
public:
	IconScene7(){}
	~IconScene7(){}
	virtual HRESULT initialize(void);
	virtual void release(void);

	virtual void renew(void);
	virtual void draw(void);
};
class IconScene8 : public IconScene
{
public:
	IconScene8(){}
	~IconScene8(){}
	virtual HRESULT initialize(void);
	virtual void release(void);

	virtual void renew(void);
	virtual void draw(void);
};
class IconScene9 : public IconScene
{
public:
	IconScene9(){}
	~IconScene9(){}
	virtual HRESULT initialize(void);
	virtual void release(void);

	virtual void renew(void);
	virtual void draw(void);
};
class IconScene10 : public IconScene
{
public:
	IconScene10(){}
	~IconScene10(){}
	virtual HRESULT initialize(void);
	virtual void release(void);

	virtual void renew(void);
	virtual void draw(void);
};
