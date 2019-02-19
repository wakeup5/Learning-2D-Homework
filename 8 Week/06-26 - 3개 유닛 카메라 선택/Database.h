#pragma once
#include "SingletonBase.h"

#include <vector>
#include <map>

class Database : public SingletonBase < Database >
{
private:
	typedef std::vector<std::string> ElementList;
	typedef std::vector<std::string>::iterator ElementLIter;
	typedef std::map<std::string, ElementList> ElementMap;
	typedef std::map<std::string, ElementList>::iterator ElementMIter;
public:
	ElementMap _mElement;

	HRESULT initialize();
	void release();

	void loadDatabase();

	ElementList get(std::string);

	Database();
	~Database();
};

