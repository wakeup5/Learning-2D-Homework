#include "stdafx.h"
#include "IconScene.h"

Image* IconScene::_icon[10];
int IconScene::_selectNum;
IconScene::IconScene()
{
	_icon[0] = IMAGEMANAGER->addImage("icon 1", "resource/i1.bmp", 80, 80);
	_icon[1] = IMAGEMANAGER->addImage("icon 2", "resource/i2.bmp", 80, 80);
	_icon[2] = IMAGEMANAGER->addImage("icon 3", "resource/i3.bmp", 80, 80);
	_icon[3] = IMAGEMANAGER->addImage("icon 4", "resource/i4.bmp", 80, 80);
	_icon[4] = IMAGEMANAGER->addImage("icon 5", "resource/i5.bmp", 80, 80);
	_icon[5] = IMAGEMANAGER->addImage("icon 6", "resource/i6.bmp", 80, 80);
	_icon[6] = IMAGEMANAGER->addImage("icon 7", "resource/i7.bmp", 80, 80);
	_icon[7] = IMAGEMANAGER->addImage("icon 8", "resource/i8.bmp", 80, 80);
	_icon[8] = IMAGEMANAGER->addImage("icon 9", "resource/i9.bmp", 80, 80);
	_icon[9] = IMAGEMANAGER->addImage("icon 10", "resource/i10.bmp", 80, 80);

	for (int i = 0; i < 10; i++)
	{
		_icon[i]->setCenter(50 + (i % 5) * 80, 50 + (i / 5) * 80);
	}
}


IconScene::~IconScene()
{

}
void IconScene::update()
{
	renew();
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 10; i++)
		{
			if (PtInRect(&_icon[i]->boundingBox(), _mousePoint))
			{
				std::string str = "icon ";
				str += to_string(i + 1);
				SCENEMANAGER->changeScene(str);
			}
		}
	}
}

void IconScene::render(void)
{
	draw();
	_background->render(getMemDC(), 0, 0);
	for (int i = 0; i < 10; i++)
	{
		_icon[i]->render(getMemDC(), ((_selectNum == i)? 255 : 100));
	}
}

HRESULT IconScene1::initialize(void)
{
	_background = IMAGEMANAGER->addImage("background 1", "resource/b1.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_selectNum = 0;
	return S_OK;
}
void IconScene1::release(void)
{

}
void IconScene1::renew(void)
{

}
void IconScene1::draw(void)
{

}

HRESULT IconScene2::initialize(void)
{
	_background = IMAGEMANAGER->addImage("background 2", "resource/b2.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_selectNum = 1;
	return S_OK;
}
void IconScene2::release(void)
{

}
void IconScene2::renew(void)
{

}
void IconScene2::draw(void)
{

}

HRESULT IconScene3::initialize(void)
{
	_background = IMAGEMANAGER->addImage("background 3", "resource/b3.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_selectNum = 2;
	return S_OK;
}
void IconScene3::release(void)
{

}
void IconScene3::renew(void)
{

}
void IconScene3::draw(void)
{

}

HRESULT IconScene4::initialize(void)
{
	_background = IMAGEMANAGER->addImage("background 4", "resource/b4.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_selectNum = 3;
	return S_OK;
}
void IconScene4::release(void)
{

}
void IconScene4::renew(void)
{

}
void IconScene4::draw(void)
{

}

HRESULT IconScene5::initialize(void)
{
	_background = IMAGEMANAGER->addImage("background 5", "resource/b5.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_selectNum = 4;
	return S_OK;
}
void IconScene5::release(void)
{

}
void IconScene5::renew(void)
{

}
void IconScene5::draw(void)
{

}

HRESULT IconScene6::initialize(void)
{
	_background = IMAGEMANAGER->addImage("background 6", "resource/b6.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_selectNum = 5;
	return S_OK;
}
void IconScene6::release(void)
{

}
void IconScene6::renew(void)
{

}
void IconScene6::draw(void)
{

}

HRESULT IconScene7::initialize(void)
{
	_background = IMAGEMANAGER->addImage("background 7", "resource/b7.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_selectNum = 6;
	return S_OK;
}
void IconScene7::release(void)
{

}
void IconScene7::renew(void)
{

}
void IconScene7::draw(void)
{

}

HRESULT IconScene8::initialize(void)
{
	_background = IMAGEMANAGER->addImage("background 8", "resource/b8.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_selectNum = 7;
	return S_OK;
}
void IconScene8::release(void)
{

}
void IconScene8::renew(void)
{

}
void IconScene8::draw(void)
{

}

HRESULT IconScene9::initialize(void)
{
	_background = IMAGEMANAGER->addImage("background 9", "resource/b9.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_selectNum = 8;
	return S_OK;
}
void IconScene9::release(void)
{

}
void IconScene9::renew(void)
{

}
void IconScene9::draw(void)
{

}

HRESULT IconScene10::initialize(void)
{
	_background = IMAGEMANAGER->addImage("background 10", "resource/b10.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_selectNum = 9;
	return S_OK;
}
void IconScene10::release(void)
{

}
void IconScene10::renew(void)
{

}
void IconScene10::draw(void)
{

}