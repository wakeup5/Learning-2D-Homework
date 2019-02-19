#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	IMAGEMANAGER->addImage("mapImage", "map.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	IMAGEMANAGER->addImage("background", "resource/11.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	//게임 이미지 로드
	IMAGEMANAGER->addImage("king gold", "resource/king.bmp", 50, 50, TRUE, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("king normal", "resource/king2.bmp", 50, 50, TRUE, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("queen gold", "resource/q2.bmp", 50, 50, TRUE, RGB(255, 255, 255));
	IMAGEMANAGER->addImage("queen normal", "resource/q1.bmp", 50, 50, TRUE, RGB(255, 255, 255));

	gameInit();
	stage1();

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();
	
	_isLeft = true;
	_isRight = true;

	if (_player.getRect().bottom >= WIN_SIZE_Y)
	{
		_player.setSpeedY(0);
		_player.setY(WIN_SIZE_Y - 25);
	}
	else
	{
		_player.gravity();
	}
	
	playerCollition();

	for (auto iter = _block.begin(); iter != _block.end(); iter++)
	{
		//블록 업데이트
		(*iter)->update();

		//다른 블럭이랑 충돌
		for (auto iter2 = iter; iter2 != _block.end(); iter2++)
		{
			if (iter == iter2) continue;
			RECT rr = (*iter)->getRect();
			rr.bottom++;
			if (IntersectRect(&rr, &rr, &(*iter2)->getRect())) //블럭과 충돌하는데
			{
				if ((*iter)->getRect().bottom >= (*iter2)->getRect().top)//두번째가 첫번째 밑에 있으면
				{
					(*iter)->setSpeedY(0);
					(*iter)->setY((*iter2)->getY() - 50);
				}
			}
		}

		//블럭 움직임
		(*iter)->move();
	}

	//키보드
	//_player.setSpeedX(0);
	if (_isLeft && KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player.setX(_player.getX() - 3);
	}
	if (_isRight && KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player.setX(_player.getX() + 3);
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_player.jump();
	}

	_player.move();

	if (KEYMANAGER->isStayKeyDown('1'))
	{
		stage1();
	}
	if (KEYMANAGER->isStayKeyDown('2'))
	{
		stage2();
	}
	if (KEYMANAGER->isStayKeyDown('3'))
	{
		stage3();
	}
}

//화면출력
void GameStudy::render(HDC hdc)
{
	HDC backDC = getBackBuffer()->getMemDC();
	IMAGEMANAGER->render("mapImage", backDC);
	IMAGEMANAGER->render("background", backDC);

	_player.render(backDC);
	_queen.render(backDC);

	for (auto iter = _block.begin(); iter != _block.end(); iter++)
	{
		(*iter)->render(backDC);
	}

	if (_isGameLose) TextOut(backDC, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, "you lose!", _tcslen("you lose!"));
	if (_isGameWin) TextOut(backDC, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, "you Win!", _tcslen("you Win!"));

	getBackBuffer()->render(hdc);
}

//게임 초기화
void GameStudy::gameInit()
{
	_player.setImage(IMAGEMANAGER->findImage("king gold"));
	_player.setSpeed(0);
	_player.setSize(30, 50);
	_player.setPosition(100, 100);
	_player.initialize();

	_queen.setImage(IMAGEMANAGER->findImage("queen normal"));
	_queen.setSize(30, 50);

	_isGameWin = false;
	_isGameLose = false;
}


void GameStudy::stage1()
{
	gameInit();
	releaseBlock();

	int blockPosition[150] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 4, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	for (int i = 0; i < 150; i++)
	{
		if (blockPosition[i] == 1 || blockPosition[i] == 2)
		{
			Block* block = new Block;
			block->setBlockKind(blockPosition[i]);
			block->setPosition(100 + (i % 15 * 50), 100 + (i / 15 * 50));
			block->setSize(50, 50);
			_block.push_back(block);
		}
		else if (blockPosition[i] == 3)
		{
			_player.setPosition(100 + (i % 15 * 50), 100 + (i / 15 * 50));
		}
		else if (blockPosition[i] == 4)
		{
			_queen.setPosition(100 + (i % 15 * 50), 100 + (i / 15 * 50));
		}
	}
}
void GameStudy::stage2()
{
	gameInit();
	releaseBlock();

	int blockPosition[150] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 4, 1, 1, 0, 3, 0, 1, 1, 2, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	for (int i = 0; i < 150; i++)
	{
		if (blockPosition[i] == 1 || blockPosition[i] == 2)
		{
			Block* block = new Block;
			block->setBlockKind(blockPosition[i]);
			block->setPosition(100 + (i % 15 * 50), 100 + (i / 15 * 50));
			block->setSize(50, 50);
			_block.push_back(block);
		}
		else if (blockPosition[i] == 3)
		{
			_player.setPosition(100 + (i % 15 * 50), 100 + (i / 15 * 50));
		}
		else if (blockPosition[i] == 4)
		{
			_queen.setPosition(100 + (i % 15 * 50), 100 + (i / 15 * 50));
		}
	}
}
void GameStudy::stage3()
{
	gameInit();
	releaseBlock();

	int blockPosition[150] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	for (int i = 0; i < 150; i++)
	{
		if (blockPosition[i] == 1 || blockPosition[i] == 2)
		{
			Block* block = new Block;
			block->setBlockKind(blockPosition[i]);
			block->setPosition(100 + (i % 15 * 50), 100 + (i / 15 * 50));
			block->setSize(50, 50);
			_block.push_back(block);
		}
		else if (blockPosition[i] == 3)
		{
			_player.setPosition(100 + (i % 15 * 50), 100 + (i / 15 * 50));
		}
		else if (blockPosition[i] == 4)
		{
			_queen.setPosition(100 + (i % 15 * 50), 100 + (i / 15 * 50));
		}
	}
}

void GameStudy::releaseBlock()
{
	for (auto iter = _block.begin(); iter != _block.end(); iter++)
	{
		SAFE_DELETE(*iter);
		(*iter) = NULL;
	}

	_block.clear();
}

void GameStudy::playerCollition()
{
	//블록 충돌처리
	RECT playerRect = _player.getRect();
	RECT r;

	//플레이어 상하단 센서
	RECT playerTopSensor = makeRect(playerRect.left + 1, playerRect.top - 1, _player.getWidth() - 2, 1);
	RECT playerBottomSensor = makeRect(playerRect.left + 1, playerRect.bottom + 1, _player.getWidth() - 2, 1);
	//플레이어 측면 센서
	RECT playerLeftSensor = makeRect(playerRect.left - 1, playerRect.top, 1, _player.getHeight());
	RECT playerRightSensor = makeRect(playerRect.right + 1, playerRect.top, 1, _player.getHeight());

	for (auto iter = _block.begin(); iter != _block.end(); iter++)
	{
		//상단 체크
		if (IntersectRect(&r, &playerTopSensor, &(*iter)->getRect()))
		{
			_player.setSpeedY(0);
			_player.setY((*iter)->getY() + 51);
			if (_player.isGoldHand()) (*iter)->setGold();
			if ((*iter)->getBlockKind() == 2) _player.setNormalHand();
		}
		//하단 체크
		if (IntersectRect(&r, &playerBottomSensor, &(*iter)->getRect())) //블럭과 충돌하는데
		{
			_player.setSpeedY(0);
			_player.setY((*iter)->getY() - 50);
			if (_player.isGoldHand()) (*iter)->setGold();
			if ((*iter)->getBlockKind() == 2) _player.setNormalHand();
		}
		//좌측 체크
		if (IntersectRect(&r, &playerLeftSensor, &(*iter)->getRect())) //블럭과 충돌하는데
		{
			_isLeft = false;
			if (_player.isGoldHand()) (*iter)->setGold();
			if ((*iter)->getBlockKind() == 2) _player.setNormalHand();
		}
		//우측 체크
		if (IntersectRect(&r, &playerRightSensor, &(*iter)->getRect())) //블럭과 충돌하는데
		{
			_isRight = false;
			if (_player.isGoldHand()) (*iter)->setGold();
			if ((*iter)->getBlockKind() == 2) _player.setNormalHand();
		}
	}

	if (!_player.isGoldHand())
	{
		_player.setImage(IMAGEMANAGER->findImage("king normal"));
	}

	if (IntersectRect(&r, &_player.getRect(), &_queen.getRect()))
	{
		if (_player.isGoldHand())
		{
			//패배
			_queen.setImage(IMAGEMANAGER->findImage("queen gold"));
			_isGameLose = true;
		}
		else
		{
			_isGameWin = true;
		}
	}
}

//숙제
//1. 알카노이드(벽돌깨기)
//벽돌 배치를 여러 모양으로
//배치 사각형으로
//1방맞으면, 2방, 3방 블럭이 있다.
//플레이어가 있다
//시작하기전에 공이 붙어있다.
//안움직일때 마우스를 누르면 앞으로 나감
//블럭을 깨면 아이템이 천천히 내려옴
//아이템을 먹으면 범위가 커짐, 공이 하나 더 늘어남, 일정시간 총알이 나감(데미지가 공과 같음)

//2. 플래시게임중에 마이더스 구현
//첫번째 스테이지는 빼고 나머지 스테이지 구현

//3. 오락실게임
//오리지널 너구리
//스테이지 하나만 구현
//압정있으면 점프해서 넘어감
//이미지는 자유롭게하나 가능하면 똑같이
