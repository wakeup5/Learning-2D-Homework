#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();
	_mapImage = IMAGEMANAGER->addImage("mapImage", "map.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_background = IMAGEMANAGER->addImage("background", "resource/11.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	//이미지 로드
	_ballImage = IMAGEMANAGER->addImage("ball", "resource/ball.bmp", 20, 20, TRUE, RGB(255, 0, 255));
	_image = IMAGEMANAGER->addImage("image", "resource/arkanoid.bmp", 192, 400, TRUE, RGB(255, 0, 255));
	
	//아이템 셋팅
	for (int i = 0; i < 10; i++)
	{
		_item[i].item.setAngleD(270);
		_item[i].item.setSpeed(2);
		_item[i].isLive = false;
	}

	for (int i = 0; i < 10; i++)
	{
		_ball[i].b.setSpeed(8);
		_ball[i].isFire = false;
	}

	//블럭 배치
	for (int i = 0; i < 30; i++)
	{
		_block[i].setImage(_image);
		_block[i].setColor(i / 5);
		_block[i].setHp((i / 10) + 1);

		_block[i].setPosition(WIN_SIZE_X / 2 + (((i % 5) - 2) * 64), 200 + (i / 5) * 16);
	}

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
	
	//키 입력부분
	if (_player.getRect().left > 0 && KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player.setPosition(_player.getPosition().x - 8, WIN_SIZE_Y - 50);
		_player.setState(Player::STATE_LEFT);
	}

	if (_player.getRect().right < WIN_SIZE_X && KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player.setPosition(_player.getPosition().x + 8, WIN_SIZE_Y - 50);
		_player.setState(Player::STATE_RIGHT);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.setState(Player::STATE_STAY);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isStart = true;
		fireBullet();
	}

	shootTime();
	bulletMove();

	//게임 시작 안했으면 플레이어에게 붙어있음 아니면 움직임
	if (!_isStart)
	{
		_ball[0].b.setPosition(POINT{ _player.getPosition().x, WIN_SIZE_Y - 68 });
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			if (!_ball[i].isFire) continue;
			_ball[i].b.move();

			//공 벽 충돌 튀기기
			if (_ball[i].b.getPositionX() - 10 < 0 || _ball[i].b.getPositionX() + 10 > WIN_SIZE_X)
			{
				_ball[i].b.setAngleD(180 - _ball[i].b.getAngleD());
			}

			if (_ball[i].b.getPositionY() - 10 < 0)
			{
				_ball[i].b.setAngleD(360 - _ball[i].b.getAngleD());
			}

			//바닥에 닿으면 끝
			if (_ball[i].b.getPositionY() + 10 > WIN_SIZE_Y)
			{
				_ball[i].isFire = false;
			}
		}
	}

	//공 갯수 확인 0개면 게임 오버
	for (int i = 0; i < 10; i++)
	{
		if (_ball[i].isFire) break;

		if (i == 9)
		{
			_isStart = false;
			gameInit();
			break;
		}
	}
	
	//공 충돌 처리
	for (int i = 0; i < 10; i++)
	{
		if (isCollisionEllipse(_player.getRect(), makeRectCenter(_ball[i].b.getPosition(), 20, 20)))
		{
			//플레이어가 움직이고 있을때 각도 조절
			if (_ball[i].b.getAngleD() < 340 && _ball[i].b.getAngleD() > 200)
			{
				if(_player.getState() == Player::STATE_LEFT)
					_ball[i].b.setAngleD(_ball[i].b.getAngleD() - 10);
				if (_player.getState() == Player::STATE_RIGHT)
					_ball[i].b.setAngleD(_ball[i].b.getAngleD() + 10);
			}
			_ball[i].b.setAngleD(360 - _ball[i].b.getAngleD());
			_ball[i].b.setPosition(POINT{ _ball[i].b.getPositionX(), WIN_SIZE_Y - 62 });
		}

		for (int j = 0; j < 30; j++)
		{
			if (_block[j].getHp() <= 0) continue;

			bulletCollition();

			if (isCollisionEllipse(_block[j].getRect(), makeRectCenter(_ball[i].b.getPosition(), 20, 20)))
			{
				float ballX = _ball[i].b.getPositionX();
				float ballY = _ball[i].b.getPositionY();
				int blockLeft = _block[j].getRect().left;
				int blockRight = _block[j].getRect().right;
				int blockTop = _block[j].getRect().top;
				int blockBottom = _block[j].getRect().bottom;

				if (ballY < blockTop)
				{
					_ball[i].b.setAngleD(360 - _ball[i].b.getAngleD());
				}
				else if (ballY > blockBottom)
				{
					_ball[i].b.setAngleD(360 - _ball[i].b.getAngleD());
				}
				else if (ballX < blockLeft)
				{
					_ball[i].b.setAngleD(180 - _ball[i].b.getAngleD());
				}
				else if (ballX > blockRight)
				{
					_ball[i].b.setAngleD(180 - _ball[i].b.getAngleD());
				}

				_block[j].setHp(_block[j].getHp() - 1);
				
				dropItem(_block[j].getPosition());
				break;
			}
		}
	}

	//아이템 이동
	for (int i = 0; i < 10; i++)
	{
		if (!_item[i].isLive) continue;
			
		_item[i].item.move();

		//플레이어 충돌
		if (isCollisionRectangle(makeRectCenter(_item[i].item.getPosition(), 32, 16), _player.getRect()))
		{
			_player.setItemState(_item[i].itemNum);
			_item[i].isLive = false;

			if (_item[i].itemNum == Player::ITEM_STATE_TWO)
			{
				Ball* ball = NULL;
				for (int j = 0; j < 10; j++)
				{
					if (_ball[i].isFire)
					{
						ball = &_ball[j];
						break;
					}
				}
				for (int j = 1; j < 10; j++)
				{
					if (ball != NULL && !_ball[j].isFire)
					{
						_ball[j].isFire = true;
						_ball[j].b.setAngleD(ball->b.getAngleD() + RANDOM->getIntTo(-50, 50));
						_ball[j].b.setPosition(ball->b.getPosition());
						break;
					}
				}
				_player.setItemState(Player::ITEM_STATE_BASIC);
			}

			if (_item[i].itemNum == Player::ITEM_STATE_SHOOT)
			{
				_isShoot = true;
				_shootTime = 100;
			}
			else
			{
				_isShoot = false;
			}
		}
		//바닥 충돌
		if (_item[i].item.getPositionY() > WIN_SIZE_Y) _item[i].isLive = false;
	}


	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_player.setItemState(Player::ITEM_STATE_BASIC);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_player.setItemState(Player::ITEM_STATE_LONG);
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_player.setItemState(Player::ITEM_STATE_SHOOT);
		_isShoot = true;
		_shootTime = 1000;
	}

}

//화면출력
void GameStudy::render(HDC hdc)
{
	HDC backDC = getBackBuffer()->getMemDC();
	_mapImage->render(backDC);
	_background->render(backDC);

	for (int i = 0; i < 10; i++)
	{
		if (_ball[i].isFire) 
			_ballImage->render(backDC, _ball[i].b.getPositionX() - 10, _ball[i].b.getPositionY() - 10);
	}

	//_image->render(backDC);
	_player.draw(backDC);
	for (int i = 0; i < 30; i++)
	{
		if (_block[i].getHp() > 0) _block[i].draw(backDC);
		//drawRectangle(backDC, _block[i].getRect());
	}

	for (int i = 0; i < 10; i++)
	{
		if (_item[i].isLive) 
			_image->render(backDC, _item[i].item.getPosition().x - 16, _item[i].item.getPosition().y - 8,
			0, 272 + _item[i].itemNum * 16, 32, 16);
	}

	for (int i = 0; i < 20; i++)
	{
		if (_bullet[i].isFire)
		{
			drawEllipseCenter(backDC, _bullet[i].getPosition(), 10, 10);
		}
	}

	//drawRectangle(backDC, _player.getRect());

	getBackBuffer()->render(hdc);
}

//게임 초기화
void GameStudy::gameInit()
{
	_player.setImage(_image);
	_player.setItemState(Player::ITEM_STATE_BASIC);
	_player.setPosition(WIN_SIZE_X / 2, WIN_SIZE_Y - 50);
	_player.setState(Player::STATE_STAY);
	_ball[0].b.setPosition(POINT{ WIN_SIZE_X / 2, WIN_SIZE_Y - 62 });
	_ball[0].b.setAngleD(90);
	_ball[0].b.setSpeed(8);
	_ball[0].isFire = true;

	_isShoot = false;
	_shootTime = 0;

	for (int i = 0; i < 20; i++)
	{
		_bullet[i].setSpeed(10);
		_bullet[i].setAngleD(90);
		_bullet[i].isFire = false;
	}
}

void GameStudy::fireBullet()
{
	if (_isShoot && _shootTime > 0)
	{
		for (int i = 0; i < 20; i++)
		{
			if (!_bullet[i].isFire)
			{
				_bullet[i].setAngleD(90);
				_bullet[i].setSpeed(10);
				_bullet[i].setPosition(_player.getPosition());
				_bullet[i].isFire = true;
				break;
			}
		}
	}
}

void GameStudy::shootTime()
{
	if (_shootTime > 0)
	{
		_shootTime--;
	}
	else if (_player.getItemState() == Player::ITEM_STATE_SHOOT)
	{
		_isShoot = false;
		_player.setItemState(Player::ITEM_STATE_BASIC);
	}

}

void GameStudy::bulletMove()
{
	//총알 움직임
	for (int i = 0; i < 20; i++)
	{
		if (_bullet[i].isFire)
		{
			_bullet[i].move();
		}
	}
}

void GameStudy::bulletCollition()
{
	for (int j = 0; j < 30; j++)
	{
		if (_block[j].getHp() <= 0) continue;

		for (int i = 0; i < 20; i++)
		{
			if (_bullet[i].isFire)
			{
				if (PtInRect(&_block[j].getRect(), _bullet[i].getPosition()))
				{
					dropItem(_block[j].getPosition());
					_block[j].setHp(_block[j].getHp() - 1);
					_bullet[i].isFire = false;
				}

				if (_bullet[i].getPositionY() < 0)
				{
					_bullet[i].isFire = false;
				}
			}
		}
	}
}

void GameStudy::dropItem(POINT startPosition)
{
	//아이템 떨굼
	if (RANDOM->getInt(10) < 5)
	{
		for (int k = 0; k < 10; k++)
		{
			if (!_item[k].isLive)
			{
				_item[k].item.setPosition(startPosition);
				_item[k].itemNum = Player::PLAYER_ITEM_STATE(RANDOM->getInt(3));
				_item[k].isLive = true;
				break;
			}
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
