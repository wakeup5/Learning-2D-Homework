#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	_mapImage = new Image();
	_mapImage->initialize("map.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_background = new Image;
	_background->initialize("resource/11.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_puzzleImage = new Image;
	_puzzleImage->initialize("resource/puzzle.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	_pieceWidth = WIN_SIZE_X / PUZZLE_COL;
	_pieceHeight = WIN_SIZE_Y / PUZZLE_ROW;

	gameInit();

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	_mapImage->release();
	_background->release();

	_puzzleImage->release();

	GameNode::release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();
	if (!_isGameStart)//게임 시작중이 아니고
	{
		if (isCollisionRectangle(_mousePoint, makeRect(10, 10, 100, 30)) && //마우스가 화면 안에 있고
			KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) //클릭하면
		{
			gameInit();

			_isGameStart = true; //게임 시작

			int length = RANDOM->getIntTo(PUZZLE_COL / 2, PUZZLE_COL);
			int num;
			for (int i = 0; i < length * PUZZLE_LENGTH * PUZZLE_LENGTH; i++)
			{
				num = puzzleSwap(RANDOM->getInt(PUZZLE_LENGTH));
				if (num != -1)
					_memorySwapNum.push_back(num);
				else
					i--;
			}
			_memorySwapNum.push_back(puzzleSwap(((_voidNum / PUZZLE_COL) * PUZZLE_COL) + PUZZLE_COL - 1));
			_memorySwapNum.push_back(puzzleSwap(PUZZLE_LENGTH - 1));
		}

	}
	else
	{
		//퍼즐 자동화
		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
			//퍼즐 자동으로 맞춤
			for (int i = 0; i < (_memorySwapNum.size() / 50) + 1; i++)
			{
				if (_isGameStart && _memorySwapNum.size() > 0)
				{
					puzzleSwap(_memorySwapNum.back());
					_memorySwapNum.pop_back();
				}
			}

		}
		else
		{
			//내가 클릭해서 옮김
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				for (int i = 0; i < PUZZLE_LENGTH; i++)
				{
					if (PtInRect(&_puzzleRect[i], _mousePoint))
					{
						_memorySwapNum.push_back(puzzleSwap(i));
					}
				}
			}
		}

		//다 맞추었는지 확인
		for (int i = 1; i < PUZZLE_LENGTH; i++)
		{
			if (_puzzleNum[i - 1] > _puzzleNum[i]) break;

			if (i == PUZZLE_LENGTH - 1)
			{
				_isGameStart = false;
				gameInit();
			}
		}

		if (KEYMANAGER->isOnceKeyDown('1'))
		{
			gameInit();
		}
	}
	
}

//화면출력
void GameStudy::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	_mapImage->render(backDC, 0, 0);
	_background->render(backDC);

	if (!_isGameStart)
	{
		_puzzleImage->render(backDC);
	}
	else
	{
		
		for (int i = 0; i < PUZZLE_LENGTH; i++)
		{
			drawRectangle(backDC, _puzzleRect[i]);
			
			if (i == _voidNum) continue;

			_puzzleImage->render(backDC, 
				((i % PUZZLE_COL) * _pieceWidth) + 1,
				((i / PUZZLE_COL) * _pieceHeight) + 1,
				((_puzzleNum[i] % PUZZLE_COL) * _pieceWidth) + 1,
				((_puzzleNum[i] / PUZZLE_COL) * _pieceHeight) + 1,
				_pieceWidth - 2, _pieceHeight - 2);
		}

		
		for (int i = 0; i < PUZZLE_LENGTH; i++)
		{
			TCHAR numStr[128];
			sprintf_s(numStr, "%d", _puzzleNum[i]);
			TextOut(backDC, (i % PUZZLE_COL) * _pieceWidth, (i / PUZZLE_COL) * _pieceHeight, numStr, _tcslen(numStr));
		}
		
		
	}
	if (!_isGameStart)
	{
		TCHAR voidNumStr[128] = "섞으려면 클릭!";
		TextOut(backDC, 10, 10, voidNumStr, _tcslen(voidNumStr));
	}

	this->getBackBuffer()->render(hdc, 0, 0);
}

//게임 초기화
void GameStudy::gameInit()
{
	for (int i = 0; i < PUZZLE_LENGTH; i++)
	{
		_puzzleNum[i] = i;
		_puzzleRect[i] = makeRect((i % PUZZLE_COL) * _pieceWidth, (i / PUZZLE_COL) * _pieceHeight, _pieceWidth, _pieceHeight);
	}

	_memorySwapNum.clear();
	_voidNum = RANDOM->getInt(PUZZLE_LENGTH);

}

int GameStudy::puzzleSwap(int clickNum)
{
	if (_voidNum == clickNum || clickNum >= PUZZLE_LENGTH || clickNum < 0) return -1;

	int diff, direction;
	if (clickNum < _voidNum && (clickNum % PUZZLE_COL) == (_voidNum % PUZZLE_COL))//빈 곳 위쪽
	{
		diff = (_voidNum - clickNum) / PUZZLE_COL;
		direction = -PUZZLE_COL;
	}
	else if (clickNum > _voidNum && (clickNum % PUZZLE_COL) == (_voidNum % PUZZLE_COL))//아래쪽
	{
		diff = (clickNum - _voidNum) / PUZZLE_COL;
		direction = PUZZLE_COL;
	}
	else if (clickNum < _voidNum && (clickNum / PUZZLE_COL) == (_voidNum / PUZZLE_COL))//왼쪽
	{
		diff = (_voidNum - clickNum);
		direction = -1;
	}
	else if (clickNum > _voidNum && (clickNum / PUZZLE_COL) == (_voidNum / PUZZLE_COL))//오른쪽
	{
		diff = (clickNum - _voidNum);
		direction = 1;
	}
	else
	{
		return -1;
	}

	int prevVoidNum = _voidNum;

	while (diff-- != 0)
	{
		int temp;
		int swapNum = _voidNum + direction;

		temp = _puzzleNum[_voidNum];
		_puzzleNum[_voidNum] = _puzzleNum[swapNum];
		_puzzleNum[swapNum] = temp;

		_voidNum = swapNum;
	}

	return prevVoidNum;
}
//숙제
// 3 * 3 퍼즐
//기본 3 * 3인데 가로 세로 갯수 자유롭게 설정 가능
//우측 아래에 빈 곳
//섞기전에 그림이 전부 보이고, 섞기 누르면 빈 곳이 생김
//이미지를 실제로 자르면 안되고 통짜 이미지를 넣고 뿌릴때 자름
//맞출수 있어야 한다.
//직선상 어디를 클릭해도 한번에 이동 된다.