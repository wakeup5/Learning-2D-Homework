#include "stdafx.h"
#include "SaveLodeTest.h"


SaveLodeTest::SaveLodeTest()
{
}


SaveLodeTest::~SaveLodeTest()
{
}

HRESULT SaveLodeTest::initialize()
{
	GameNode::initialize();

	return S_OK;
}
void SaveLodeTest::release(void)
{

}
void SaveLodeTest::update(void)
{
	GameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		write();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		read();
	}
}
void SaveLodeTest::render()
{

}

void SaveLodeTest::write()
{
	HANDLE file;
	char str[256] = "gotdamn";
	DWORD write;

	file = CreateFile("gotdamn.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);
	CloseHandle(file);
}

void SaveLodeTest::read()
{
	HANDLE file;
	char str[256];
	DWORD read;

	file = CreateFile("gotdamn.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, NULL, &read, NULL);
	CloseHandle(file);

	std::cout << str << std::endl;
}