#pragma once
#include "SingletonBase.h"
#include "GameNode.h"

class ObjectManager :
	public SingletonBase < ObjectManager >
{
private:
	std::map<std::string, GameNode*> _mNode;
	std::map<std::string, GameNode*>::iterator _miNode;
public:
	ObjectManager();
	~ObjectManager();

	HRESULT initialize();
	void release();
	void update();
	void render();

	bool removeObject(std::string key);
	GameNode* addObject(std::string key, GameNode * node);
	GameNode* findObject(std::string key);
};

