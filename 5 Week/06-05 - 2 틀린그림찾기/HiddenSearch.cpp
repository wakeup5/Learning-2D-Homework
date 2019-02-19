#include "stdafx.h"
#include "HiddenSearch.h"


HiddenSearch::HiddenSearch()
{
}


HiddenSearch::~HiddenSearch()
{
}


HRESULT HiddenSearch::initialize(Image* original, Image* modify, vector<RECT> vRc, Image* ok)
{
	GameNode::initialize();

	_oImage = original;
	_mImage = modify;
	_ok = ok;

	vector<RECT>::iterator vir;

	for (vir = vRc.begin(); vir != vRc.end(); vir++)
	{
		HSRect r;
		r.left = vir->left;
		r.top = vir->top;
		r.right = vir->right;
		r.bottom = vir->bottom;
		r.find = false;

		_vRc.push_back(r);
	}

	return S_OK;
}
void HiddenSearch::release(void)
{
	for (_viRc = _vRc.begin(); _viRc != _vRc.end();)
	{
		_viRc = _vRc.erase(_viRc);
	}

	_vRc.clear();
}
void HiddenSearch::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (_viRc = _vRc.begin(); _viRc != _vRc.end(); _viRc++)
		{
			RECT r = RECT{ _viRc->left, _viRc->top, _viRc->right, _viRc->bottom };
			if (PtInRect(&r, _mousePoint))
			{
				_viRc->find = true;
			}
		}
	}
}
void HiddenSearch::render(void)
{
	_oImage->render(getMemDC(), 0, 0);
	_mImage->render(getMemDC(), WIN_SIZE_X / 2, 0);
	for (_viRc = _vRc.begin(); _viRc != _vRc.end(); _viRc++)
	{
		//Rectangle(getMemDC(), _viRc->left, _viRc->top, _viRc->right, _viRc->bottom);

		if (_viRc->find)
		{
			_ok->render(getMemDC(), _viRc->left, _viRc->top);
			_ok->render(getMemDC(), _viRc->left - 500, _viRc->top);
		}
	}
}

bool HiddenSearch::isClear()
{
	for (_viRc = _vRc.begin(); _viRc != _vRc.end(); _viRc++)
	{
		if (!_viRc->find)
		{
			return false;
		}
	}

	return true;
}