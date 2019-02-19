#include "stdafx.h"
#include "Sceen3.h"


Sceen3::Sceen3()
{
}


Sceen3::~Sceen3()
{
}

HRESULT Sceen3::initialize(int playerNum)
{

	for (int i = 0; i < 10; i++)
	{
		_ladderNum[i] = i;
	}

	for (int j = 0; j < 20; j++)
	{
		//사다리 섞음
		for (int i = 1; i < playerNum; i++)
		{
			if (j != 0 && j != 19 && RANDOM->getInt(4) == 0)
			{
				int temp = _ladderNum[i - 1];
				_ladderNum[i - 1] = _ladderNum[i];
				_ladderNum[i] = temp;

				i++;
			}
		}
		//사다리 넣음
		for (int i = 0; i < playerNum; i++)
		{
			_ladder[i][j] = _ladderNum[i];
			cout << _ladderNum[i] << endl;
		}

	}


	int distance = (WIN_SIZE_X - 100) / playerNum;
	for (int i = 0; i < playerNum; i++)
	{
		_prevPoint[i] = i;
		_point[i] = i;
	}

	_button = CreateWindow("button", "확인", WS_VISIBLE | WS_CHILD | BS_USERBUTTON, WIN_SIZE_X - 60, WIN_SIZE_Y / 2 - 10, 50, 20, _hWnd, HMENU(5), _hInstance, NULL);
	_isOpen = false;

	return S_OK;
}
void Sceen3::release(void)
{

}
void Sceen3::update(void)
{
	//InvalidateRect(_hWnd, NULL, false);
}
void Sceen3::render(void)
{
	int distance = (WIN_SIZE_X - 100) / _playerNum;

	for (int i = 0; i < _playerNum; i++)
	{
		_prevPoint[i] = i;
		_point[i] = i;
	}

	for (int i = 0; i < _playerNum; i++)
	{
		_selectImage[i]->render(getMemDC(), 50 + i * distance + distance / 2 - _selectImage[i]->getWidth() / 2, 50);
		TextOut(getMemDC(), 50 + i * distance + distance / 2 - _selectImage[i]->getWidth() / 2, 10, _playerName[i], strlen(_playerName[i]));
	}

	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < _playerNum; i++)
		{
			HPEN p = NULL, op = NULL;
			if (_isOpen)
			{
				p = CreatePen(PS_SOLID, 1, RGB(((float)_ladder[i][j] / (_playerNum - 1.0f) * 255), 255 - ((float)_ladder[i][j] / (_playerNum - 1.0f) * 255), 0));
				op = (HPEN)SelectObject(getMemDC(), p);

				_point[_ladder[i][j]] = i;

				drawLine(getMemDC(),
					POINT{ 50 + _prevPoint[_ladder[i][j]] * distance + distance / 2, 150 + 20 * (j - 1) },
					POINT{ 50 + _prevPoint[_ladder[i][j]] * distance + distance / 2, 150 + 20 * j });


				drawLine(getMemDC(),
					POINT{ 50 + _prevPoint[_ladder[i][j]] * distance + distance / 2, 150 + 20 * j },
					POINT{ 50 + _point[_ladder[i][j]] * distance + distance / 2, 150 + 20 * j });

				_prevPoint[_ladder[i][j]] = _point[_ladder[i][j]];

				SelectObject(getMemDC(), op);
				DeleteObject(p);
			}
			else
			{
				_point[_ladder[i][j]] = i;

				drawLine(getMemDC(),
					POINT{ 50 + _prevPoint[_ladder[i][j]] * distance + distance / 2, 150 + 20 * (j - 1) },
					POINT{ 50 + _prevPoint[_ladder[i][j]] * distance + distance / 2, 150 + 20 * j });


				drawLine(getMemDC(),
					POINT{ 50 + _prevPoint[_ladder[i][j]] * distance + distance / 2, 150 + 20 * j },
					POINT{ 50 + _point[_ladder[i][j]] * distance + distance / 2, 150 + 20 * j });

				_prevPoint[_ladder[i][j]] = _point[_ladder[i][j]];
			}
		}
	}
	if (_isOpen)
	{
		for (int i = 0; i < _playerNum; i++)
		{
			_selectImage[_ladderNum[i]]->render(getMemDC(), 50 + i * distance + distance / 2 - _selectImage[i]->getWidth() / 2, WIN_SIZE_Y - 100);
		}
	}

}

void Sceen3::controlMessage(int message)
{
	if (message == 5)
	{
		_isOpen = true;
	}
}

