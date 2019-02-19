#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();

	srand(time(NULL));

	
	// 플레이어 셋업
	
	_One_Player.angle =  0;								// 1P 플레이어가 2P 플레이어를 보는 기본 각도 0도
	_One_Player.radius = PLAYER_SIZE;					// 1P 플레이어 포탑 크기
	_One_Player.center.x = WIN_SIZE_X / 6;				// 1P 플레이어 포탑 위치 가로(X 축)
	_One_Player.center.y = WIN_SIZE_Y / 2;				// 1P 플레이어 포탑 위치 세로(Y축)


	
	_Two_Player.angle = PI;								// 2P 플레이어가 1P 플레이어를 바라보는 기본 각도 180도
	_Two_Player.radius = PLAYER_SIZE;					// 2P 플레이어 포탑 크기
	_Two_Player.center.x = WIN_SIZE_X / 6 * 5;			// 2P 플레이어 포탑 위치 가로(X 축)
	_Two_Player.center.y = WIN_SIZE_Y / 2;				// 2P 플레이어 포탑 위치 세로(Y축)

	

	// 각각 플레이어 들의 포신 셋팅
	
	_One_Player_Barrel.angel = _One_Player.angle;
	_One_Player_Barrel.barrel_radius = BARREL_SIZE;
	_One_Player_Barrel.center.x = _One_Player.center.x + (_One_Player.radius / 2) + (_One_Player_Barrel.barrel_radius / 2);		// 포탑의 반지름하고 포신의 반지름 더한 위치 값(1P 는 오른쪽을 봐야하니까)
	_One_Player_Barrel.center.y = WIN_SIZE_Y / 2;

	_Two_Player_Barrel.angel = _Two_Player.angle;
	_Two_Player_Barrel.barrel_radius = BARREL_SIZE;
	_Two_Player_Barrel.center.x = _Two_Player.center.x  - ((_Two_Player.radius / 2) + (_Two_Player_Barrel.barrel_radius / 2));	// 포탑의 반지름하고 포신의 반지름 더한 위치 값(2P 는 왼쪽을 봐야하니까)
	_Two_Player_Barrel.center.y = WIN_SIZE_Y / 2;
	
	

	Player_One_destance = 0;			// 1P 총알 간격 초기화

	Player_Two_destance = 0;			// 2P 총알 간격 초기화


	crush_check = false;
	

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

	if (Player_One_destance > 0)			// 1P 의 총알간 간격 5  
	{
		Player_One_destance--;
	}

	if (Player_Two_destance > 0)			// 2P 의 총알간 간격 5
	{
		Player_Two_destance--;
	}



	One_Player_Move();						// 1P 이동 호출
	Two_Player_Move();						// 2P 이동 호출

	Player_One_Bullet_Make();				// 1P 의 총알 생성
	Player_One_Bullet_Shot();				// 1P 의 총알 발사, 삭제

	Player_Two_Bullet_Make();				// 2P 의 총알 생성
	Player_Two_Bullet_Shot();				// 2P 의 총알 발사, 삭제

	Bullet_Crush();							// 총알 충돌 처리 (HELP 받을거)
	
	Defence();								// 각각의 플레이어 들의 총알과 포신충돌 처리

	Plus_Score();							// 점수 처리 함수
		

	
	// 라디안 구하는 공식 (각도 -> 라디안) #define ToRadian(degree)    ((degree)*(PI/180.0f))

	
	// 디그리(도) 구하는 공식 (라디안 -> 각도 변환) #define ToDegree(radian)    ((radian)*(180.0f/PI))

	//_cannon.degree = (_cannon.angle * (180.0f / PI));
}

//화면출력
void GameStudy::render(HDC hdc)
{

	
	// 1P 플레이어 그리기
	//MyBrush = CreateSolidBrush(RGB(0, 0, 255));
	//OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
	EllipseMakeCenter(hdc, _One_Player.center.x, _One_Player.center.y,
		_One_Player.radius, _One_Player.radius);
	//SelectObject(hdc, OldBrush);
	//DeleteObject(MyBrush);


	// 1P 플레이어 포신
	//MyBrush = CreateSolidBrush(RGB(0, 255, 255));
	//OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

	EllipseMakeCenter(hdc, _One_Player_Barrel.center.x, _One_Player_Barrel.center.y,
		_One_Player_Barrel.barrel_radius, _One_Player_Barrel.barrel_radius);

	//SelectObject(hdc, OldBrush);
	//DeleteObject(MyBrush);

	//LineMake(hdc, _One_Player.center.x, _One_Player.center.y, _One_Player_Barrel.center.x, _One_Player_Barrel.center.y);
	

	// 2P 플레이어 그리기

	//MyBrush = CreateSolidBrush(RGB(255, 0, 0));
	//OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
	EllipseMakeCenter(hdc, _Two_Player.center.x, _Two_Player.center.y,
		_Two_Player.radius, _Two_Player.radius);
	//SelectObject(hdc, OldBrush);
	//DeleteObject(MyBrush);


	// 2P 플레이어 포신
	//MyBrush = CreateSolidBrush(RGB(255, 128, 0));
	//OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

	EllipseMakeCenter(hdc, _Two_Player_Barrel.center.x, _Two_Player_Barrel.center.y,
		_Two_Player_Barrel.barrel_radius, _Two_Player_Barrel.barrel_radius);

	//SelectObject(hdc, OldBrush);
	//DeleteObject(MyBrush);
	

	// 1P의 총알 출력

	for (int i = 0; i < MAXBULLET; i++)
	{
		if (player_one_bullet[i] != NULL)
		{

			MyBrush = CreateSolidBrush(RGB(0, 0, 255));
			OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

			EllipseMakeCenter(hdc, player_one_bullet[i]->Center.x, player_one_bullet[i]->Center.y,
				player_one_bullet[i]->radius, player_one_bullet[i]->radius);

			SelectObject(hdc, OldBrush);
			DeleteObject(MyBrush);
		}
	}

	// 2P의 총알 출력

	for (int i = 0; i < MAXBULLET; i++)
	{
		if (player_Two_bullet[i] != NULL)
		{

			MyBrush = CreateSolidBrush(RGB(255, 0, 0));
			OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

			EllipseMakeCenter(hdc, player_Two_bullet[i]->Center.x, player_Two_bullet[i]->Center.y,
				player_Two_bullet[i]->radius, player_Two_bullet[i]->radius);

			SelectObject(hdc, OldBrush);
			DeleteObject(MyBrush);
		}
	}

		
	// 각각 플레이어들의 점수를 출력하기 

	hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	OldFont = (HFONT)SelectObject(hdc, hFont);

	TCHAR str[MAX_CHAR];
	sprintf_s(str, "%d",One_Player_Score);
    TextOut(hdc, _One_Player.center.x - 20, _One_Player.center.y - 25, str, _tcslen(str));


	sprintf_s(str, "%d",Two_Player_Score);
    TextOut(hdc, _Two_Player.center.x - 20, _Two_Player.center.y - 25, str, _tcslen(str));

		
	SelectObject(hdc, OldFont);
	DeleteObject(hFont);
	
	


}


void GameStudy::One_Player_Move()					// 플레이어 1의 이동처리
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_One_Player.angle -= 0.04f;
		_One_Player_Barrel.angel = _One_Player.angle;
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_One_Player.angle += 0.04;
		_One_Player_Barrel.angel = _One_Player.angle;
	}

	
	
	// 각도에 따라 플레이어 1의 포신 이동

	_One_Player_Barrel.center.x = cosf(_One_Player.angle) * 
		((_One_Player_Barrel.barrel_radius / 2) + (_One_Player.radius / 2)) + 
		_One_Player.center.x;

	_One_Player_Barrel.center.y = -sinf(_One_Player.angle) * 
		((_One_Player_Barrel.barrel_radius / 2) + (_One_Player.radius / 2)) +
		_One_Player.center.y;
	

}


void GameStudy::Two_Player_Move()						// 플레이어 2의 이동처리
{
	



	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_Two_Player.angle -= 0.04f;
		_Two_Player_Barrel.angel = _Two_Player.angle;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_Two_Player.angle += 0.04f;
		_Two_Player_Barrel.angel = _Two_Player.angle;
	}

	_Two_Player_Barrel.center.x = cosf(_Two_Player.angle) *
		((_Two_Player_Barrel.barrel_radius / 2) + (_Two_Player.radius / 2)) +
		_Two_Player.center.x;

	_Two_Player_Barrel.center.y = -sinf(_Two_Player.angle) *
		((_Two_Player_Barrel.barrel_radius / 2) + (_Two_Player.radius / 2)) +
		_Two_Player.center.y;
}


void GameStudy::Player_One_Bullet_Make()							// 1P 의 총알 생성
{

	if (KEYMANAGER->isOnceKeyDown('J') || KEYMANAGER->isStayKeyDown('J') && Player_One_destance == 0)
	{
		for (int i = 0; i < MAXBULLET; i++)
		{
			if (player_one_bullet[i] == NULL)
			{
				player_one_bullet[i] = new Bullet;

				// 1P의 총알 중앙 = { 1P의 포신 x축 중앙 + (1P의 포신 반지름 + 10) * cosf(1P의 각도(라디안)), 1P의 포신 y축 중앙 + (1P의 포신 반지름 + 10) * -sinf(1P의 각도(라디안)) }
				// 총알의 위치는 각도에따라 포신보다 앞으로 생성되어 발사 해야되기 때문에 10을 더해 주었다.

				player_one_bullet[i]->Center = { _One_Player_Barrel.center.x + 
					((_One_Player_Barrel.barrel_radius / 2 + 10) * 
					cosf(_One_Player.angle)), 
					_One_Player_Barrel.center.y + 
					((_One_Player_Barrel.barrel_radius / 2 + 10) * 
					-sinf(_One_Player.angle)) };

				player_one_bullet[i]->Speed = SPEED;
				player_one_bullet[i]->angle = _One_Player.angle;
				player_one_bullet[i]->radius = BARREL_SIZE;

				Player_One_destance = BULLET_DISTANCE;

				return;

			}
		}
	}
}

void GameStudy::Player_One_Bullet_Shot()									// 1P의 총알 발사(이동, 삭제 처리)	
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (player_one_bullet[i] != NULL)
		{
			player_one_bullet[i]->Center.x = player_one_bullet[i]->Center.x + cosf(player_one_bullet[i]->angle) * player_one_bullet[i]->Speed;
			player_one_bullet[i]->Center.y = player_one_bullet[i]->Center.y - sinf(player_one_bullet[i]->angle) * player_one_bullet[i]->Speed;

		
			// 왼쪽 오른쪽 벽으로 이동햇을때 총알 삭제
			if (player_one_bullet[i]->Center.x < 0 || player_one_bullet[i]->Center.x > WIN_SIZE_X)
			{
				delete player_one_bullet[i];
				player_one_bullet[i] = NULL;
				continue;
			}

			
			// 위 쪽으로 이동했을때 처리
			if (player_one_bullet[i]->Center.y <  player_one_bullet[i]->radius / 2) 
			{
				player_one_bullet[i]->angle = 2 * PI - player_one_bullet[i]->angle;
				player_one_bullet[i]->Center.y = player_one_bullet[i]->radius / 2;
			}

			// 아래 쪽으로 이동했을때 처리

			if (player_one_bullet[i]->Center.y >  WIN_SIZE_Y - (player_one_bullet[i]->radius / 2))
			{
				player_one_bullet[i]->angle = 2 * PI - player_one_bullet[i]->angle;
				player_one_bullet[i]->Center.y = WIN_SIZE_Y - (player_one_bullet[i]->radius / 2);
			}

		}
	}
}

void GameStudy::Player_Two_Bullet_Make()				// 2P 의 총알 생성
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) || KEYMANAGER->isStayKeyDown(VK_SPACE) && Player_Two_destance == 0)
	{
		for (int i = 0; i < MAXBULLET; i++)
		{
			if (player_Two_bullet[i] == NULL)
			{
				player_Two_bullet[i] = new Bullet;

				// 2P의 총알 중앙 = { 2P의 포신 x축 중앙 + (2P의 포신 반지름 + 10) * cosf(2P의 각도(라디안)), 2P의 포신 y축 중앙 + (2P의 포신 반지름 + 10) * -sinf(2P의 각도(라디안)) }
				// 총알의 위치는 각도에따라 포신보다 앞으로 생성되어 발사 해야되기 때문에 10을 더해 주었다.

				player_Two_bullet[i]->Center = { _Two_Player_Barrel.center.x +
					((_Two_Player_Barrel.barrel_radius / 2 + 10) *
					cosf(_Two_Player.angle)),
					_Two_Player_Barrel.center.y +
					((_Two_Player_Barrel.barrel_radius / 2 + 10) *
					-sinf(_Two_Player.angle)) };

				player_Two_bullet[i]->Speed = SPEED;
				player_Two_bullet[i]->angle = _Two_Player.angle;
				player_Two_bullet[i]->radius = BARREL_SIZE;

				Player_Two_destance = BULLET_DISTANCE;

				return;

			}
		}
	}

}

void GameStudy::Player_Two_Bullet_Shot()			// 2P의 총알 발사(이동, 삭제 처리)	
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (player_Two_bullet[i] != NULL)
		{
			player_Two_bullet[i]->Center.x = player_Two_bullet[i]->Center.x + cosf(player_Two_bullet[i]->angle) * player_Two_bullet[i]->Speed;
			player_Two_bullet[i]->Center.y = player_Two_bullet[i]->Center.y - sinf(player_Two_bullet[i]->angle) * player_Two_bullet[i]->Speed;


			// 왼쪽 오른쪽 벽으로 이동햇을때 총알 삭제
			if (player_Two_bullet[i]->Center.x < 0 || player_Two_bullet[i]->Center.x > WIN_SIZE_X)
			{
				delete player_Two_bullet[i];
				player_Two_bullet[i] = NULL;
				continue;
			}


			// 위 쪽으로 이동했을때 처리
			if (player_Two_bullet[i]->Center.y <  player_Two_bullet[i]->radius / 2)
			{
				player_Two_bullet[i]->angle = 2 * PI - player_Two_bullet[i]->angle;
				player_Two_bullet[i]->Center.y = player_Two_bullet[i]->radius / 2;
			}

			// 아래 쪽으로 이동했을때 처리

			if (player_Two_bullet[i]->Center.y >  WIN_SIZE_Y - (player_Two_bullet[i]->radius / 2))
			{
				player_Two_bullet[i]->angle = 2 * PI - player_Two_bullet[i]->angle;
				player_Two_bullet[i]->Center.y = WIN_SIZE_Y - (player_Two_bullet[i]->radius / 2);
			}

		}
	}

}

void GameStudy::Bullet_Crush()																					// 1P 의 총알과 2P의 총알 이 부딪혔을 때 충돌처리 (총알끼리 튕기기)
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		for (int j = 0; j < MAXBULLET; j++)
		{
			if (player_one_bullet[i] != NULL && player_Two_bullet[j] != NULL)									// 1P 총알과 2P 총알이 NULL 이 아닐때 1P 총알과 2P 총알이 부딪혔을때 튕기게 하는 부분
			{
				int width = sqrt(pow((player_one_bullet[i]->Center.x - player_Two_bullet[j]->Center.x), 2) +	// 총알간의 거리 계산
					pow((player_one_bullet[i]->Center.y - player_Two_bullet[j]->Center.y), 2));

				if ((player_one_bullet[i]->radius / 2) + (player_Two_bullet[j]->radius / 2) >= width)			// 총알간의 거리가  width 보다 크거나 같을때
				{
					player_one_bullet[i]->angle = getAngle((float)player_Two_bullet[j]->Center.x, (float)player_Two_bullet[j]->Center.y, player_one_bullet[i]->Center.x, player_one_bullet[i]->Center.y);

					player_Two_bullet[j]->angle = getAngle((float)player_one_bullet[i]->Center.x, (float)player_one_bullet[i]->Center.y, player_Two_bullet[j]->Center.x, player_Two_bullet[j]->Center.y);
				}

			}	
		}

		for (int j = 0; j < MAXBULLET; j++)																		// 1P가 발사한 자기자신의 총알끼의 충돌 처리부분
		{
			if (i == j)continue;																				// 자기 자신 총알 불러오면 생략
			if (player_one_bullet[i] != NULL && player_one_bullet[j] != NULL)
			{
				int width = sqrt(pow((player_one_bullet[i]->Center.x - player_one_bullet[j]->Center.x), 2) +
					pow((player_one_bullet[i]->Center.y - player_one_bullet[j]->Center.y), 2));

				if ((player_one_bullet[i]->radius / 2) + (player_one_bullet[j]->radius / 2) >= width)
				{
					player_one_bullet[i]->angle = getAngle((float)player_one_bullet[j]->Center.x, (float)player_one_bullet[j]->Center.y, player_one_bullet[i]->Center.x, player_one_bullet[i]->Center.y);

					player_one_bullet[j]->angle = getAngle((float)player_one_bullet[i]->Center.x, (float)player_one_bullet[i]->Center.y, player_one_bullet[j]->Center.x, player_one_bullet[j]->Center.y);
				}

			}
		}

		for (int j = 0; j < MAXBULLET; j++)																		// 2P가 발사한 자기자신의 총알끼의 충돌 처리부분
		{
			if (i == j)continue;																				// 자기 자신 총알 불러오면 생략
			if (player_Two_bullet[i] != NULL && player_Two_bullet[j] != NULL)
			{
				int width = sqrt(pow((player_Two_bullet[i]->Center.x - player_Two_bullet[j]->Center.x), 2) +
					pow((player_Two_bullet[i]->Center.y - player_Two_bullet[j]->Center.y), 2));

				if ((player_Two_bullet[i]->radius / 2) + (player_Two_bullet[j]->radius / 2) >= width)
				{
					player_Two_bullet[i]->angle = getAngle((float)player_Two_bullet[j]->Center.x, (float)player_Two_bullet[j]->Center.y, player_Two_bullet[i]->Center.x, player_Two_bullet[i]->Center.y);

					player_Two_bullet[j]->angle = getAngle((float)player_Two_bullet[i]->Center.x, (float)player_Two_bullet[i]->Center.y, player_Two_bullet[j]->Center.x, player_Two_bullet[j]->Center.y);
				}

			}
		}
	}
}

void GameStudy::Defence()													// 1P 포신과 2P 포신에서 총알 막기
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (player_one_bullet[i] != NULL)									// 1P의 총알이 발사 됐을 때 2P 포신에서 방어하는 부분 (1P에서도 2P가 튕긴 자신의 총알을 다시 튕기게 하는 부분) 
		{																	// 즉 포신에서는 내 총알, 적총알 전부 반사
			// 1P에서 발사한 총알과 2P의 포신의 거리 계산 부분
			int width_one_enemy = sqrt(pow((_Two_Player_Barrel.center.x - player_one_bullet[i]->Center.x), 2) +
				pow((_Two_Player_Barrel.center.y - player_one_bullet[i]->Center.y), 2));

			// 1P에서 발사한 총알과 1P의 포신의 거리 계산 부분
			int width_one_my = sqrt(pow((_One_Player_Barrel.center.x - player_one_bullet[i]->Center.x), 2) +
				pow((_One_Player_Barrel.center.y - player_one_bullet[i]->Center.y), 2));


			// 2P가 포신으로 1P 총알을 막았을 때 총알 각도 처리
			if ((_Two_Player_Barrel.barrel_radius / 2) + (player_one_bullet[i]->radius / 2) >= width_one_enemy)
			{
				player_one_bullet[i]->angle = getAngle((float)_Two_Player_Barrel.center.x, (float)_Two_Player_Barrel.center.y, player_one_bullet[i]->Center.x, player_one_bullet[i]->Center.y);
				
			}

			// 2P가 포신으로 막아낸(튕겨낸) 1P 총알을 막았을때 총알 각도 처리
			if ((_One_Player_Barrel.barrel_radius / 2) + (player_one_bullet[i]->radius / 2) >= width_one_my)
			{
				player_one_bullet[i]->angle = getAngle((float)_One_Player_Barrel.center.x, (float)_One_Player_Barrel.center.y, player_one_bullet[i]->Center.x, player_one_bullet[i]->Center.y);

			}

		}

		if (player_Two_bullet[i] != NULL)									// 2P의 총알이 발사 됐을 때 1P 포신에서 방어하는 부분 (2P에서도 1P가 튕긴 자신의 총알을 다시 튕기게 하는 부분) 
		{																	// 즉 포신에서는 내 총알, 적총알 전부 반사
		
			// 2P에서 발사한 총알과 1P의 포신의 거리 계산 부분
			int width_Two_enemy = sqrt(pow((_One_Player_Barrel.center.x - player_Two_bullet[i]->Center.x), 2) +
				pow((_One_Player_Barrel.center.y - player_Two_bullet[i]->Center.y), 2));

			// 2P에서 발사한 총알과 2P의 포신의 거리 계산 부분
			int width_Two_my = sqrt(pow((_Two_Player_Barrel.center.x - player_Two_bullet[i]->Center.x), 2) +
				pow((_Two_Player_Barrel.center.y - player_Two_bullet[i]->Center.y), 2));


			// 1P가 포신으로 2P 총알을 막았을 때 총알 각도 처리
			if ((_One_Player_Barrel.barrel_radius / 2) + (player_Two_bullet[i]->radius / 2) >= width_Two_enemy)
			{
				player_Two_bullet[i]->angle = getAngle((float)_One_Player_Barrel.center.x, (float)_One_Player_Barrel.center.y, player_Two_bullet[i]->Center.x, player_Two_bullet[i]->Center.y);

			}

			// 1P가 포신으로 2P 총알을 막았을 때 총알 각도 처리
			if ((_Two_Player_Barrel.barrel_radius / 2) + (player_Two_bullet[i]->radius / 2) >= width_Two_my)
			{
				player_Two_bullet[i]->angle = getAngle((float)_Two_Player_Barrel.center.x, (float)_Two_Player_Barrel.center.y, player_Two_bullet[i]->Center.x, player_Two_bullet[i]->Center.y);

			}
		}
	}
}

void GameStudy::Plus_Score()
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (player_one_bullet[i] != NULL)									// 1P의 총알이 발사 됐을 때 2P 몸체에서 맞아서 1P의 점수가 올라가는 부분
		{																	// 1P가 발사한 총알은 사라진다.
			// 1P에서 발사한 총알과 2P의 몸체거리 계산 부분
			int width_one_enemy = sqrt(pow((_Two_Player.center.x - player_one_bullet[i]->Center.x), 2) +
				pow((_Two_Player.center.y - player_one_bullet[i]->Center.y), 2));

			// 2P가 1P의 총알을 맞았을 때 점수, 총알처리
			if ((_Two_Player.radius / 2) + (player_one_bullet[i]->radius / 2) >= width_one_enemy)
			{
				delete player_one_bullet[i];
				player_one_bullet[i] = NULL;
				One_Player_Score++;

			}
		}

		if (player_one_bullet[i] != NULL)									// 1P가 자기자신의 총알을 맞았을때 처리하는 부분 2P의 점수가 올라간다.
		{																	// 1P의 총알은 사라진다.
			// 1P에서 발사한 총알과 1P의 몸체거리 계산 부분
			int width_one_my = sqrt(pow((_One_Player.center.x - player_one_bullet[i]->Center.x), 2) +
				pow((_One_Player.center.y - player_one_bullet[i]->Center.y), 2));


			// 1P 총알을 1P가 맞았을때(자기 자신이 쏜 총알을 맞았을때)
			if ((_One_Player.radius / 2) + (player_one_bullet[i]->radius / 2) >= width_one_my)
			{
				delete player_one_bullet[i];
				player_one_bullet[i] = NULL;
				Two_Player_Score++;
			}

		}
		
		if (player_Two_bullet[i] != NULL)									// 2P의 총알이 발사 됐을 때 1P 몸체에서 맞는 부분 2P의 점수가 올라간다. 
		{																	// 2P의 총알은 사라진다.

			// 2P에서 발사한 총알과 1P의 몸체거리 계산 부분
			int width_Two_enemy = sqrt(pow((_One_Player.center.x - player_Two_bullet[i]->Center.x), 2) +
				pow((_One_Player.center.y - player_Two_bullet[i]->Center.y), 2));


			// 1P가 2P 총알을 맞았을 때 총알, 점수 처리
			if ((_One_Player.radius / 2) + (player_Two_bullet[i]->radius / 2) >= width_Two_enemy)
			{
				delete player_Two_bullet[i];
				player_Two_bullet[i] = NULL;
				Two_Player_Score++;

			}

		}

		if (player_Two_bullet[i] != NULL)																// 2P가 자기 자신의의 총알을 맞았을때 1P의 점수가 올라간다.
		{																								// 2P의 총알은 사라진다.
			// 2P에서 발사한 총알과 2P의 몸체거리 계산 부분
			int width_Two_my = sqrt(pow((_Two_Player.center.x - player_Two_bullet[i]->Center.x), 2) +
				pow((_Two_Player.center.y - player_Two_bullet[i]->Center.y), 2));


			// 2P가 자기 자신 총알을 맞았을 때 총알, 점수 처리
			if ((_Two_Player.radius / 2) + (player_Two_bullet[i]->radius / 2) >= width_Two_my)
			{
				delete player_Two_bullet[i];
				player_Two_bullet[i] = NULL;
				One_Player_Score++;
			}
		}
		
	}
}




float GameStudy::getAngle(float x1, float y1, float x2, float y2)					// 충돌계산식...(공부) 
{
	float x = x2 - x1;
	float y = y2 - y1;
	float hypo = sqrt(pow(x, 2) + pow(y, 2));
	float angle = acosf(x / hypo);
	if (y2 > y1)
	{
		angle = 2 * PI - angle;
		if (angle >= 2 * PI) angle -= 2 * PI;
	}
	return angle;
}

