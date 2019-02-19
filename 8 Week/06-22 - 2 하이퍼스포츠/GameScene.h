#pragma once
#include "SceneManager.h"
class GameScene : public Scene
{
private:
	enum TURN_STATE
	{
		TURN_START, TURN_GAME, TURN_AFTER, TURN_END
	};
	Image* _background;
	SpriteImage* _shooter;
	SpriteImage* _aimImage;
	SpriteImage* _circleImage;

	GameObject* _aim[2];
	std::vector<GameObject*> _vCircle;

	int _turnScore;
	int _score[3];
	int _turn;
	int _turnState;
public:
	GameScene();
	~GameScene();
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void game();
	void shoot();
	void move();
};

