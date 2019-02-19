#pragma once
#include "GameNode.h"
class SaveLodeTest :
	public GameNode
{
public:
	SaveLodeTest();
	virtual ~SaveLodeTest();

	virtual HRESULT initialize();
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	void write();
	void read();
};

