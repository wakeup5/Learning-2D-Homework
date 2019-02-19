#include "stdafx.h"
#include "GameStudy.h"

using namespace std;

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	IMAGEMANAGER->addImage("mapImage", "resource/mapBlack.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	//->addImage("background", "resource/11.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	//IMAGEMANAGER->addImage("ponpoko bg", "resource/ponpokoBg.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	IMAGEMANAGER->addSpriteImage("image", "resource/ponpoko1.bmp", 200, 360, 5, 9, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("objectImage", "resource/ponpoko1.bmp", 200, 360, TRUE, RGB(255, 0, 255));

	gameInit();

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
	
	static SpriteImage* playerImage = static_cast<SpriteImage*>(_player.getImage());
	static int time = 0;

	if (!_isDead)
	{
		//플레이어 움직이고 충돌처리등등
		if (!(_isJump || _isBigJump)) playerMove();

		//플레이어 점프
		static int spaceDownTime;
		static int jumpTime;
		static float y;
		
		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
			spaceDownTime++;
			if (true)
			{
				if (_isJump && spaceDownTime > 8)
				{
					_isBigJump = true;
					_isJump = false;
					jumpTime = 80;
				}
				else if (!_isBigJump && !_isJump)
				{
					_isJump = true;
					_isBigJump = false;
					jumpTime = 50;
					y = _player.getY();
				}
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
		{
			spaceDownTime = 0;
		}

		if (_isBigJump)
		{
			playerImage->setFrameY(3);
			if (jumpTime < 1)
			{
				_player.setY(y);
			}
			else if (jumpTime > 41)
			{
				_player.setY(_player.getY() - 1);
				playerImage->setFrameX(((_isLeft) ? 0 : 2));
			}
			else if (jumpTime <= 41)
			{
				_player.setY(_player.getY() + 1);
				playerImage->setFrameX(((_isLeft) ? 1 : 3));
			}

			_player.setX(_player.getX() + ((_isLeft) ? -1.2 : 1.2));
		}
		else if (_isJump)
		{
			playerImage->setFrameY(3);
			if (jumpTime < 3)
			{
				_player.setY(y);
			}
			else if(jumpTime > 25)
			{
				_player.setY(_player.getY() - 1);
				playerImage->setFrameX(((_isLeft) ? 0 : 2));
			}
			else if (jumpTime <= 25)
			{
				_player.setY(_player.getY() + 1);
				playerImage->setFrameX(((_isLeft) ? 1 : 3));
			}

			_player.setX(_player.getX() + ((_isLeft) ? -1.2 : 1.2));
		}	
	
		if ((_isJump || _isBigJump) && jumpTime <= 0)
		{
			_isJump = false;
			_isBigJump = false;
			playerImage->setFrameY(((_isLeft) ? 1 : 2));
		}
		else
		{
			jumpTime--;
		}
	}
	else
	{
		if (_player.getRect().top < WIN_SIZE_Y)
		{
			_player.setY(_player.getY() + 1);
		}
		if (time % 5 == 0)
		{
			playerImage->setFrameY(8);

			if (playerImage->getFrameX() >= 3)
			{
				playerImage->setFrameX(0);
			}
			else
			{
				playerImage->setFrameX(playerImage->getFrameX() + 1);
			}

			time = 0;
		}
		time++;
		
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		gameInit();
	}
}

//화면출력
void GameStudy::render(HDC hdc)
{
	HDC backDC = getBackBuffer()->getMemDC();
	IMAGEMANAGER->render("mapImage", backDC);
	//IMAGEMANAGER->render("background", backDC);
	//IMAGEMANAGER->render("ponpoko bg", backDC);

	Image* objectImage = IMAGEMANAGER->findImage("objectImage");

	for (int i = 0; i < 560; i++)
	{
		switch (_block[i].type)
		{
		case TYPE_FLOOR:
			objectImage->render(backDC, _block[i].object.getRect().left, _block[i].object.getRect().top, 0, 40 * 7, 20, 20);
			break;
		case TYPE_THORN:
			objectImage->render(backDC, _block[i].object.getRect().left, _block[i].object.getRect().top, 40, 40 * 7, 20, 20);
			//drawRectangle(backDC, _block[i].object.getRect());
			break;
		case TYPE_FLOOR_LADDER: case TYPE_LADDER:
			objectImage->render(backDC, _block[i].object.getRect().left, _block[i].object.getRect().top, 80, 40 * 7, 20, 20);
			break;
		}

		//drawRectangle(backDC, makeRect(_block[i].object.getRect().left, _block[i].object.getRect().top, _block[i].object.getWidth(), 3));
	}

	IMAGEMANAGER->render("image", backDC, _player.getRect().left - 10, _player.getRect().top - 20);
	//drawRectangle(backDC, _player.getRect());
	//drawRectangle(backDC, makeRect(_player.getRect().left + 2, _player.getRect().bottom, _player.getWidth() - 4, 3));
	getBackBuffer()->render(hdc);
}

//게임 초기화
void GameStudy::gameInit()
{
	int top = 100;
	int left = 125;

	SpriteImage* playerImage = static_cast<SpriteImage*>(IMAGEMANAGER->findImage("image"));
	_player.setImage(playerImage);

	_player.setPosition(500, top + (18 * 20));
	_player.setSize(20, 20);
	playerImage->setFrameY(0);
	playerImage->setFrameX(0);

	int tile[20 * 28] =
	{
		1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 2, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	for (int i = 0; i < 560; i++)
	{
		_block[i].type = OBJECT_TYPE(tile[i]);
		_block[i].object.setPosition(left + (i % 28 * 20), top + (i / 28 * 20));
		_block[i].object.setSize(20, 20);
	}

	_isDead = false;
	_isJump = false;
	_isBigJump = false;
	_isLeft = true;
}

void GameStudy::playerMove()
{
	SpriteImage* playerImage = static_cast<SpriteImage*>(_player.getImage());

	RECT playerBottomSensor = makeRect(_player.getRect().left + 2, _player.getRect().bottom, _player.getWidth() - 4, 3);
	RECT blockTopSensor;
	RECT r;
	//좌측이동
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		for (int i = 0; i < 560; i++)
		{
			blockTopSensor = makeRect(_block[i].object.getRect().left, _block[i].object.getRect().top, _block[i].object.getWidth(), 2);
			if ((_block[i].type == TYPE_FLOOR || _block[i].type == TYPE_FLOOR_LADDER))
			{
				if (IntersectRect(&r, &playerBottomSensor, &blockTopSensor))
				{
					playerImage->setFrameY(1);
					if (playerImage->getFrameX() >= playerImage->getMaxFrameX())
					{
						playerImage->setFrameX(0);
					}
					else
					{
						playerImage->setFrameX(playerImage->getFrameX() + 1);
					}
					_player.setX(_player.getX() - 3);
					break;
				}
			}			
		}
		_isLeft = true;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		playerImage->setFrameY(0);
		playerImage->setFrameX(0);
	}

	//우측이동
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		for (int i = 0; i < 560; i++)
		{
			blockTopSensor = makeRect(_block[i].object.getRect().left, _block[i].object.getRect().top, _block[i].object.getWidth(), 2);
			if ((_block[i].type == TYPE_FLOOR || _block[i].type == TYPE_FLOOR_LADDER))
			{
				if (IntersectRect(&r, &playerBottomSensor, &blockTopSensor))
				{
					playerImage->setFrameY(2);
					if (playerImage->getFrameX() >= playerImage->getMaxFrameX())
					{
						playerImage->setFrameX(0);
					}
					else
					{
						playerImage->setFrameX(playerImage->getFrameX() + 1);
					}
					_player.setX(_player.getX() + 3);
					break;
				}
			}			
		}
		_isLeft = false;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		playerImage->setFrameY(0);
		playerImage->setFrameX(1);
	}

	//위로 이동
	RECT playerLadderRect = makeRectCenter(_player.getPosition(), 2, 20);
	RECT playerLadderDownRect = makeRectCenter(_player.getX(), _player.getY() + 12, 2, 3);
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		for (int i = 0; i < 560; i++)
		{
			if ((_block[i].type == TYPE_LADDER || _block[i].type == TYPE_FLOOR_LADDER) && 
				IntersectRect(&r, &playerLadderRect, &_block[i].object.getRect()))
			{
				playerImage->setFrameY(4);
				if (playerImage->getFrameX() >= 2)
				{
					playerImage->setFrameX(0);
				}
				else
				{
					playerImage->setFrameX(playerImage->getFrameX() + 1);
				}
				_player.setY(_player.getY() - 3);
				break;
			}
		}
	}

	//밑으로 이동
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		for (int i = 0; i < 560; i++)
		{
			
			if ((_block[i].type == TYPE_LADDER || _block[i].type == TYPE_FLOOR_LADDER) &&
				//IntersectRect(&r, &playerLadderRect, &_block[i].object.getRect()) &&
				IntersectRect(&r, &playerLadderDownRect, &_block[i].object.getRect()))
			{
				playerImage->setFrameY(4);
				if (playerImage->getFrameX() >= 2)
				{
					playerImage->setFrameX(0);
				}
				else
				{
					playerImage->setFrameX(playerImage->getFrameX() + 1);
				}
				_player.setY(_player.getY() + 3);
				break;
			}
		}
	}

	playerBottomSensor = makeRect(_player.getRect().left + 3, _player.getRect().bottom, _player.getWidth() - 6, 3);
	bool isDead = true;
	for (int i = 0; i < 560; i++)
	{
		blockTopSensor = makeRect(_block[i].object.getRect().left, _block[i].object.getRect().top, _block[i].object.getWidth(), 2);
		if (((_block[i].type == TYPE_FLOOR || _block[i].type == TYPE_FLOOR_LADDER) &&
			IntersectRect(&r, &playerBottomSensor, &blockTopSensor)) || // 너구리가 땅을 딛고 있을때
			((_block[i].type == TYPE_LADDER || _block[i].type == TYPE_FLOOR_LADDER)
			&& IntersectRect(&r, &playerLadderRect, &_block[i].object.getRect())) || //사다리에 타고 있을때
			((_block[i].type == TYPE_LADDER || _block[i].type == TYPE_FLOOR_LADDER)
			&& IntersectRect(&r, &playerLadderDownRect, &_block[i].object.getRect())) //플레이어 꽁지가 사다리에 있을때
			)
		{
			isDead = false;
			break;
		}

		if (_block[i].type == TYPE_THORN && IntersectRect(&r, &_player.getRect(), &_block[i].object.getRect()))
		{
			isDead = true;
			break;
		}
	}

	if (!(_isJump || _isBigJump) && isDead)
	{
		cout << "죽음" << endl;
		_isDead = true;;
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
