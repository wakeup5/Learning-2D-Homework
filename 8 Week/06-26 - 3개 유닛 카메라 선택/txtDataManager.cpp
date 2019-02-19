#include "StdAfx.h"
#include "txtDataManager.h"

txtDataManager::txtDataManager(void)
{
}

txtDataManager::~txtDataManager(void)
{
}

HRESULT txtDataManager::init(void)
{
	return S_OK;
}

void txtDataManager::release(void)
{

}

//세이브
void txtDataManager::txtSave(const char* saveFileName,
		vector<string> vStr)
{
	HANDLE file;
	char str[300];
	DWORD write;

	strncpy_s(str, 300, vectorArrayCombine(vStr), 300);

	file = CreateFile(saveFileName, GENERIC_WRITE, 0,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);
	CloseHandle(file);
}

char* txtDataManager::vectorArrayCombine(vector<string> vArray)
{
	char str[300];

	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 300, vArray[i].c_str(), 300);
		if (i + 1 < vArray.size()) strcat_s(str, ",");
	}

	return str;
}

//로드
vector<string> txtDataManager::txtLoad(const char* loadFileName)
{
	HANDLE file;
	char str[300];
	DWORD read;

	memset(str, 0, 300);
	file = CreateFile(loadFileName, GENERIC_READ, 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, str, 300, &read, NULL);
	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtDataManager::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* temp;
	char* separator = " ,/(&%#@";
	char* token;

	token = strtok_s(charArray, separator, &temp);
	vArray.push_back(token);
	
	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
