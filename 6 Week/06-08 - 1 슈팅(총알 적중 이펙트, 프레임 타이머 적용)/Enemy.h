#pragma once
#include "GameNode.h"
#include "ObjectPattern.h"

class Enemy : public GameObject
{
private:
	SpriteImage* _image;
	float _frameTime;

	typedef std::function<void(Enemy*, float)> PatternFunc;
	PatternFunc _pattern;

	DWORD _createTickTime;

	int _patternState;
protected:
	int _hp;
	int _maxHp;

public:
	Enemy();
	virtual ~Enemy();

	virtual HRESULT initialize(SpriteImage* image, float frameTime);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move();
	virtual void draw();

	void setHp(int hp){ _hp = hp; }
	int getHp(){ return _hp; }

	void setPattern(PatternFunc pattern){ _pattern = pattern; }

	void setPatternState(int p){ _patternState = p; }
	int getPatternState(){ return _patternState; }
};

