#pragma once
class Marine : public GameObject
{
private:
	SpriteImage* _image;
public:
	Marine();
	~Marine();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC);
};

