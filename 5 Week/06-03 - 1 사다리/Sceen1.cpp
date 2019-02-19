#include "stdafx.h"
#include "Sceen1.h"


Sceen1::Sceen1()
{
}


Sceen1::~Sceen1()
{
}

HRESULT Sceen1::initialize()
{
	GameNode::initialize();
	_sceenNum = 1;
	_textInput = CreateWindow("edit", "2", WS_VISIBLE | WS_CHILD | WS_BORDER, WIN_SIZE_X / 2 - 75, WIN_SIZE_Y / 2 - 10, 150, 20, _hWnd, HMENU(0), _hInstance, NULL);
	_submit = CreateWindow("button", "확인", WS_VISIBLE | WS_CHILD | BS_USERBUTTON, WIN_SIZE_X / 2 + 80, WIN_SIZE_Y / 2 - 10, 50, 20, _hWnd, HMENU(1), _hInstance, NULL);

	_submit2 = CreateWindow("button", "다음", WS_CHILD | BS_USERBUTTON, WIN_SIZE_X - 60, WIN_SIZE_Y / 2 - 10, 50, 20, _hWnd, HMENU(2), _hInstance, NULL);
	for (int i = 0; i < 10; i++)
	{
		_textInput2[i] = CreateWindow("edit", "이름", WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 40.0f + i * 80, 40, 50, 20, _hWnd, HMENU(3 + i), _hInstance, NULL);
	}

	for (int i = 0; i < 10; i++)
	{
		char imageName[128];
		sprintf_s(imageName, "resource/image%d.bmp", i + 1);
		_image[i] = IMAGEMANAGER->addImage(imageName, imageName, 40.0f + i *80, WIN_SIZE_Y - 40.0f, 50, 50);
	}
	for (int i = 0; i < 10; i++)
	{
		_selectImage[i] = NULL;
	}

	return S_OK;
}
void Sceen1::release(void)
{
	
}
void Sceen1::update(void)
{
	GameNode::update();

	if (_sceenNum == 2)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 10; i++)
			{
				if (PtInRect(&makeRectCenter(_image[i]->getX(), _image[i]->getY(), _image[i]->getWidth(), _image[i]->getHeight()), _mousePoint))
				{
					_dragImage = _image[i];
				}
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			for (int i = 0; i < _playerNum; i++)
			{
				RECT r = makeRect(40.0f + i * 80, 100, 50, 50);
				if (PtInRect(&r, _mousePoint))
				{
					_selectImage[i] = _dragImage;
					_dragImage = NULL;
				}
			}
		}

		/*
		if (_dragImage)
		{
			_dragImage->setCenter(_mousePoint.x, _mousePoint.y);
		}
		*/
		InvalidateRect(_hWnd, NULL, false);
	}
	else if (_sceenNum == 3)
	{
		_s3->update();
	}
}
void Sceen1::render(void)
{
	TextOut(getMemDC(), 10, 10, _errorStr, strlen(_errorStr));
	if (_sceenNum == 1)
	{
		TextOut(getMemDC(), WIN_SIZE_X / 2 - 125, WIN_SIZE_Y / 2 - 10, "입력", strlen("입력"));
	}
	else if (_sceenNum == 2)
	{
		for (int i = 0; i < 10; i++)
		{
			_image[i]->render(getMemDC());
		}

		for (int i = 0; i < _playerNum; i++)
		{
			drawRectangle(getMemDC(), makeRect(40.0f + i * 80, 100, 50, 50));
			if (_selectImage[i])_selectImage[i]->render(getMemDC(), 40.0f + i * 80, 100);
		}

		if (_dragImage) _dragImage->render(getMemDC(), _mousePoint.x, _mousePoint.y);
	}
	else if (_sceenNum == 3)
	{
		_s3->render();
	}
}

void Sceen1::controlMessage(int message)
{
	if (_sceenNum == 3)
	{
		DEBUG("11");
		_s3->controlMessage(message);
		return;
	}

	if (message == 1)
	{
		char a[128];
		GetWindowText(_textInput, a, strlen(a));
		int num = atoi(a);

		if (num < 2 || num > 10)
		{
			memcpy(_errorStr, "에러 - 2 ~ 10 사이의 숫자만 넣으셈", sizeof("에러 - 2 ~ 10 사이의 숫자만 넣으셈"));
			SetWindowText(_textInput, "2");
		}
		else
		{
			_playerNum = num;

			_sceenNum = 2;

			DestroyWindow(_textInput);
			DestroyWindow(_submit);

			ShowWindow(_submit2, 1);
			for (int i = 0; i < _playerNum; i++)
			{
				ShowWindow(_textInput2[i], 1);
			}
		}
	}

	if (message == 2)
	{
		bool allInput = false;
		for (int i = 0; i < _playerNum; i++)
		{
			if (!_selectImage[i]) break;
			GetWindowText(_textInput2[i], _playerName[i], 128);
			if (i == _playerNum - 1)
			{
				allInput = true;
			}
		}

		if (allInput)
		{
			for (int i = 0; i < 10; i++)
			{
				DestroyWindow(_textInput2[i]);
			}
			DestroyWindow(_submit2);
			_sceenNum = 3;
			_s3 = new Sceen3;
			_s3->initialize(_playerNum);
			_s3->setGameInfo(_playerNum, _selectImage, _playerName);
		}
	}
}