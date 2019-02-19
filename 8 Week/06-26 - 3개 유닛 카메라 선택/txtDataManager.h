#pragma once

#include "Singletonbase.h"
#include <vector>

class txtDataManager : public SingletonBase <txtDataManager>
{
public:
	HRESULT init(void);
	void release(void);

	//세이브~~
	void txtSave(const char* saveFileName,
		vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	//로드
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);	

	txtDataManager(void);
	~txtDataManager(void);
};
