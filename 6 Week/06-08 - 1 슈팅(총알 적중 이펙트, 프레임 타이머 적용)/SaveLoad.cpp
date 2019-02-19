#include "stdafx.h"
#include "SaveLoad.h"


SaveLoad::SaveLoad()
{
}


SaveLoad::~SaveLoad()
{
}


HRESULT SaveLoad::initialize()
{
	GameNode::initialize();

	return S_OK;
}
void SaveLoad::release(void)
{

}
void SaveLoad::update(void)
{
	GameNode::update();
}
void SaveLoad::render()
{

}

void SaveLoad::write()
{
	HANDLE file;
	char str[256];
	DWORD write;

	Player* player = OBJECTMANAGER->findObject<Player>(GUID_PLAYER);

	std::string saveInfo = "hp:" + std::to_string(player->getHp()) + ":hp x:" + std::to_string(player->getX()) + ":x y:" + std::to_string(player->getY()) + ":y";

	memcpy(str, saveInfo.c_str(), strlen(saveInfo.c_str()));

	file = CreateFile("a.save", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	WriteFile(file, str, strlen(saveInfo.c_str()), &write, NULL);

	CloseHandle(file);
}

void SaveLoad::read()
{
	HANDLE file;
	char str[256];
	DWORD read;
	Player* player = OBJECTMANAGER->findObject<Player>(GUID_PLAYER);

	file = CreateFile("a.save", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 256, &read, NULL);
	CloseHandle(file);

	std::string loadInfo(str);

	int hp = atoi(loadInfo.substr(loadInfo.find("hp:") + 3, loadInfo.find(":hp")).c_str());
	int x = atoi(loadInfo.substr(loadInfo.find("x:") + 2, loadInfo.find(":x")).c_str());
	int y = atoi(loadInfo.substr(loadInfo.find("y:") + 2, loadInfo.find(":y")).c_str());

	player->setHp(hp);
	player->setX(x);
	player->setY(y);
}