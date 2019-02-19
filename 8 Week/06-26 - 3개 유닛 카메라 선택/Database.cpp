#include "stdafx.h"
#include "Database.h"


Database::Database()
{
}


Database::~Database()
{
}

HRESULT Database::initialize(void)
{
	loadDatabase();

	return S_OK;
}

void Database::release(void)
{

}

void Database::loadDatabase(void)
{
	//데이터 읽는다
	ElementList vTemp;
	vTemp = TXTMANAGER->txtLoad("database.txt");

	string str;

	for (int i = 0; i < vTemp.size(); i++)
	{
		if (vTemp[i] == "|")
		{
			ElementList vElement;
			str = vTemp[i + 1];
			_mElement.insert(make_pair(str, vElement));
			continue;
		}
		ElementMIter mIter = _mElement.find(str);
		mIter->second.push_back(vTemp[i]);
	}
	vTemp.clear();
}

vector<string> Database::get(string key)
{
	loadDatabase();

	ElementList el;

	ElementMIter mIter = _mElement.find(key);

	if (mIter != _mElement.end()) el = mIter->second;

	return el;
}



