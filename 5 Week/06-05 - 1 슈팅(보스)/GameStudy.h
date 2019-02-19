#pragma once
#include "GameNode.h"
#include "SaveLoad.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

class GameStudy :
	public GameNode
{
private:
	SaveLoad* _sl;

	PlayerManager* _playerManager;
	EnemyManager* _enemyManager;
public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

};
