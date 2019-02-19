#pragma once
#include "GameNode.h"
class SaveLoad :
	public GameNode
{
public:
	SaveLoad();
	virtual ~SaveLoad();

	virtual HRESULT initialize();
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	void write();
	void read();
};

