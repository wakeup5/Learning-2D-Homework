#include "stdafx.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

HRESULT ObjectManager::initialize()
{
	return S_OK;
}

void ObjectManager::release()
{
	for (_miNode = _mNode.begin(); _miNode != _mNode.end();)
	{
		_miNode->second->release();
		SAFE_DELETE(_miNode->second);
		_miNode = _mNode.erase(_miNode);
	}

	_mNode.clear();
}

void ObjectManager::update()
{
	for (_miNode = _mNode.begin(); _miNode != _mNode.end(); _miNode++)
	{
		_miNode->second->update();
	}
}

void ObjectManager::render()
{
	for (_miNode = _mNode.begin(); _miNode != _mNode.end(); _miNode++)
	{
		_miNode->second->render();
	}
}

GameNode* ObjectManager::addObject(std::string key, GameNode* node)
{
	if (node)
	{
		_mNode.insert(std::make_pair(key, node));
	}

	return node;
}
GameNode* ObjectManager::findObject(std::string key)
{
	std::map<std::string, GameNode*>::iterator iter = _mNode.find(key);

	if (iter != _mNode.end())
	{
		return iter->second;
	}

	return NULL;
}

bool ObjectManager::removeObject(std::string key)
{
	std::map<std::string, GameNode*>::iterator iter = _mNode.find(key);

	if (iter != _mNode.end())
	{
		iter->second->release();
		SAFE_DELETE(iter->second);
		_mNode.erase(iter);
		return true;
	}

	return false;
}