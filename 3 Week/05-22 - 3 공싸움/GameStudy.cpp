#include "stdafx.h"
#include "GameStudy.h"

//�ʱ�ȭ
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();

	srand(time(NULL));

	
	// �÷��̾� �¾�
	
	_One_Player.angle =  0;								// 1P �÷��̾ 2P �÷��̾ ���� �⺻ ���� 0��
	_One_Player.radius = PLAYER_SIZE;					// 1P �÷��̾� ��ž ũ��
	_One_Player.center.x = WIN_SIZE_X / 6;				// 1P �÷��̾� ��ž ��ġ ����(X ��)
	_One_Player.center.y = WIN_SIZE_Y / 2;				// 1P �÷��̾� ��ž ��ġ ����(Y��)


	
	_Two_Player.angle = PI;								// 2P �÷��̾ 1P �÷��̾ �ٶ󺸴� �⺻ ���� 180��
	_Two_Player.radius = PLAYER_SIZE;					// 2P �÷��̾� ��ž ũ��
	_Two_Player.center.x = WIN_SIZE_X / 6 * 5;			// 2P �÷��̾� ��ž ��ġ ����(X ��)
	_Two_Player.center.y = WIN_SIZE_Y / 2;				// 2P �÷��̾� ��ž ��ġ ����(Y��)

	

	// ���� �÷��̾� ���� ���� ����
	
	_One_Player_Barrel.angel = _One_Player.angle;
	_One_Player_Barrel.barrel_radius = BARREL_SIZE;
	_One_Player_Barrel.center.x = _One_Player.center.x + (_One_Player.radius / 2) + (_One_Player_Barrel.barrel_radius / 2);		// ��ž�� �������ϰ� ������ ������ ���� ��ġ ��(1P �� �������� �����ϴϱ�)
	_One_Player_Barrel.center.y = WIN_SIZE_Y / 2;

	_Two_Player_Barrel.angel = _Two_Player.angle;
	_Two_Player_Barrel.barrel_radius = BARREL_SIZE;
	_Two_Player_Barrel.center.x = _Two_Player.center.x  - ((_Two_Player.radius / 2) + (_Two_Player_Barrel.barrel_radius / 2));	// ��ž�� �������ϰ� ������ ������ ���� ��ġ ��(2P �� ������ �����ϴϱ�)
	_Two_Player_Barrel.center.y = WIN_SIZE_Y / 2;
	
	

	Player_One_destance = 0;			// 1P �Ѿ� ���� �ʱ�ȭ

	Player_Two_destance = 0;			// 2P �Ѿ� ���� �ʱ�ȭ


	crush_check = false;
	

	return S_OK;
}

//����
void GameStudy::release(void)
{
	GameNode::release();
}

//ȭ�鰻��
void GameStudy::update(void)
{
	GameNode::update();

	if (Player_One_destance > 0)			// 1P �� �Ѿ˰� ���� 5  
	{
		Player_One_destance--;
	}

	if (Player_Two_destance > 0)			// 2P �� �Ѿ˰� ���� 5
	{
		Player_Two_destance--;
	}



	One_Player_Move();						// 1P �̵� ȣ��
	Two_Player_Move();						// 2P �̵� ȣ��

	Player_One_Bullet_Make();				// 1P �� �Ѿ� ����
	Player_One_Bullet_Shot();				// 1P �� �Ѿ� �߻�, ����

	Player_Two_Bullet_Make();				// 2P �� �Ѿ� ����
	Player_Two_Bullet_Shot();				// 2P �� �Ѿ� �߻�, ����

	Bullet_Crush();							// �Ѿ� �浹 ó�� (HELP ������)
	
	Defence();								// ������ �÷��̾� ���� �Ѿ˰� �����浹 ó��

	Plus_Score();							// ���� ó�� �Լ�
		

	
	// ���� ���ϴ� ���� (���� -> ����) #define ToRadian(degree)    ((degree)*(PI/180.0f))

	
	// ��׸�(��) ���ϴ� ���� (���� -> ���� ��ȯ) #define ToDegree(radian)    ((radian)*(180.0f/PI))

	//_cannon.degree = (_cannon.angle * (180.0f / PI));
}

//ȭ�����
void GameStudy::render(HDC hdc)
{

	
	// 1P �÷��̾� �׸���
	//MyBrush = CreateSolidBrush(RGB(0, 0, 255));
	//OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
	EllipseMakeCenter(hdc, _One_Player.center.x, _One_Player.center.y,
		_One_Player.radius, _One_Player.radius);
	//SelectObject(hdc, OldBrush);
	//DeleteObject(MyBrush);


	// 1P �÷��̾� ����
	//MyBrush = CreateSolidBrush(RGB(0, 255, 255));
	//OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

	EllipseMakeCenter(hdc, _One_Player_Barrel.center.x, _One_Player_Barrel.center.y,
		_One_Player_Barrel.barrel_radius, _One_Player_Barrel.barrel_radius);

	//SelectObject(hdc, OldBrush);
	//DeleteObject(MyBrush);

	//LineMake(hdc, _One_Player.center.x, _One_Player.center.y, _One_Player_Barrel.center.x, _One_Player_Barrel.center.y);
	

	// 2P �÷��̾� �׸���

	//MyBrush = CreateSolidBrush(RGB(255, 0, 0));
	//OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
	EllipseMakeCenter(hdc, _Two_Player.center.x, _Two_Player.center.y,
		_Two_Player.radius, _Two_Player.radius);
	//SelectObject(hdc, OldBrush);
	//DeleteObject(MyBrush);


	// 2P �÷��̾� ����
	//MyBrush = CreateSolidBrush(RGB(255, 128, 0));
	//OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

	EllipseMakeCenter(hdc, _Two_Player_Barrel.center.x, _Two_Player_Barrel.center.y,
		_Two_Player_Barrel.barrel_radius, _Two_Player_Barrel.barrel_radius);

	//SelectObject(hdc, OldBrush);
	//DeleteObject(MyBrush);
	

	// 1P�� �Ѿ� ���

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

	// 2P�� �Ѿ� ���

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

		
	// ���� �÷��̾���� ������ ����ϱ� 

	hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("����"));
	OldFont = (HFONT)SelectObject(hdc, hFont);

	TCHAR str[MAX_CHAR];
	sprintf_s(str, "%d",One_Player_Score);
    TextOut(hdc, _One_Player.center.x - 20, _One_Player.center.y - 25, str, _tcslen(str));


	sprintf_s(str, "%d",Two_Player_Score);
    TextOut(hdc, _Two_Player.center.x - 20, _Two_Player.center.y - 25, str, _tcslen(str));

		
	SelectObject(hdc, OldFont);
	DeleteObject(hFont);
	
	


}


void GameStudy::One_Player_Move()					// �÷��̾� 1�� �̵�ó��
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

	
	
	// ������ ���� �÷��̾� 1�� ���� �̵�

	_One_Player_Barrel.center.x = cosf(_One_Player.angle) * 
		((_One_Player_Barrel.barrel_radius / 2) + (_One_Player.radius / 2)) + 
		_One_Player.center.x;

	_One_Player_Barrel.center.y = -sinf(_One_Player.angle) * 
		((_One_Player_Barrel.barrel_radius / 2) + (_One_Player.radius / 2)) +
		_One_Player.center.y;
	

}


void GameStudy::Two_Player_Move()						// �÷��̾� 2�� �̵�ó��
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


void GameStudy::Player_One_Bullet_Make()							// 1P �� �Ѿ� ����
{

	if (KEYMANAGER->isOnceKeyDown('J') || KEYMANAGER->isStayKeyDown('J') && Player_One_destance == 0)
	{
		for (int i = 0; i < MAXBULLET; i++)
		{
			if (player_one_bullet[i] == NULL)
			{
				player_one_bullet[i] = new Bullet;

				// 1P�� �Ѿ� �߾� = { 1P�� ���� x�� �߾� + (1P�� ���� ������ + 10) * cosf(1P�� ����(����)), 1P�� ���� y�� �߾� + (1P�� ���� ������ + 10) * -sinf(1P�� ����(����)) }
				// �Ѿ��� ��ġ�� ���������� ���ź��� ������ �����Ǿ� �߻� �ؾߵǱ� ������ 10�� ���� �־���.

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

void GameStudy::Player_One_Bullet_Shot()									// 1P�� �Ѿ� �߻�(�̵�, ���� ó��)	
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (player_one_bullet[i] != NULL)
		{
			player_one_bullet[i]->Center.x = player_one_bullet[i]->Center.x + cosf(player_one_bullet[i]->angle) * player_one_bullet[i]->Speed;
			player_one_bullet[i]->Center.y = player_one_bullet[i]->Center.y - sinf(player_one_bullet[i]->angle) * player_one_bullet[i]->Speed;

		
			// ���� ������ ������ �̵������� �Ѿ� ����
			if (player_one_bullet[i]->Center.x < 0 || player_one_bullet[i]->Center.x > WIN_SIZE_X)
			{
				delete player_one_bullet[i];
				player_one_bullet[i] = NULL;
				continue;
			}

			
			// �� ������ �̵������� ó��
			if (player_one_bullet[i]->Center.y <  player_one_bullet[i]->radius / 2) 
			{
				player_one_bullet[i]->angle = 2 * PI - player_one_bullet[i]->angle;
				player_one_bullet[i]->Center.y = player_one_bullet[i]->radius / 2;
			}

			// �Ʒ� ������ �̵������� ó��

			if (player_one_bullet[i]->Center.y >  WIN_SIZE_Y - (player_one_bullet[i]->radius / 2))
			{
				player_one_bullet[i]->angle = 2 * PI - player_one_bullet[i]->angle;
				player_one_bullet[i]->Center.y = WIN_SIZE_Y - (player_one_bullet[i]->radius / 2);
			}

		}
	}
}

void GameStudy::Player_Two_Bullet_Make()				// 2P �� �Ѿ� ����
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) || KEYMANAGER->isStayKeyDown(VK_SPACE) && Player_Two_destance == 0)
	{
		for (int i = 0; i < MAXBULLET; i++)
		{
			if (player_Two_bullet[i] == NULL)
			{
				player_Two_bullet[i] = new Bullet;

				// 2P�� �Ѿ� �߾� = { 2P�� ���� x�� �߾� + (2P�� ���� ������ + 10) * cosf(2P�� ����(����)), 2P�� ���� y�� �߾� + (2P�� ���� ������ + 10) * -sinf(2P�� ����(����)) }
				// �Ѿ��� ��ġ�� ���������� ���ź��� ������ �����Ǿ� �߻� �ؾߵǱ� ������ 10�� ���� �־���.

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

void GameStudy::Player_Two_Bullet_Shot()			// 2P�� �Ѿ� �߻�(�̵�, ���� ó��)	
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (player_Two_bullet[i] != NULL)
		{
			player_Two_bullet[i]->Center.x = player_Two_bullet[i]->Center.x + cosf(player_Two_bullet[i]->angle) * player_Two_bullet[i]->Speed;
			player_Two_bullet[i]->Center.y = player_Two_bullet[i]->Center.y - sinf(player_Two_bullet[i]->angle) * player_Two_bullet[i]->Speed;


			// ���� ������ ������ �̵������� �Ѿ� ����
			if (player_Two_bullet[i]->Center.x < 0 || player_Two_bullet[i]->Center.x > WIN_SIZE_X)
			{
				delete player_Two_bullet[i];
				player_Two_bullet[i] = NULL;
				continue;
			}


			// �� ������ �̵������� ó��
			if (player_Two_bullet[i]->Center.y <  player_Two_bullet[i]->radius / 2)
			{
				player_Two_bullet[i]->angle = 2 * PI - player_Two_bullet[i]->angle;
				player_Two_bullet[i]->Center.y = player_Two_bullet[i]->radius / 2;
			}

			// �Ʒ� ������ �̵������� ó��

			if (player_Two_bullet[i]->Center.y >  WIN_SIZE_Y - (player_Two_bullet[i]->radius / 2))
			{
				player_Two_bullet[i]->angle = 2 * PI - player_Two_bullet[i]->angle;
				player_Two_bullet[i]->Center.y = WIN_SIZE_Y - (player_Two_bullet[i]->radius / 2);
			}

		}
	}

}

void GameStudy::Bullet_Crush()																					// 1P �� �Ѿ˰� 2P�� �Ѿ� �� �ε����� �� �浹ó�� (�Ѿ˳��� ƨ���)
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		for (int j = 0; j < MAXBULLET; j++)
		{
			if (player_one_bullet[i] != NULL && player_Two_bullet[j] != NULL)									// 1P �Ѿ˰� 2P �Ѿ��� NULL �� �ƴҶ� 1P �Ѿ˰� 2P �Ѿ��� �ε������� ƨ��� �ϴ� �κ�
			{
				int width = sqrt(pow((player_one_bullet[i]->Center.x - player_Two_bullet[j]->Center.x), 2) +	// �Ѿ˰��� �Ÿ� ���
					pow((player_one_bullet[i]->Center.y - player_Two_bullet[j]->Center.y), 2));

				if ((player_one_bullet[i]->radius / 2) + (player_Two_bullet[j]->radius / 2) >= width)			// �Ѿ˰��� �Ÿ���  width ���� ũ�ų� ������
				{
					player_one_bullet[i]->angle = getAngle((float)player_Two_bullet[j]->Center.x, (float)player_Two_bullet[j]->Center.y, player_one_bullet[i]->Center.x, player_one_bullet[i]->Center.y);

					player_Two_bullet[j]->angle = getAngle((float)player_one_bullet[i]->Center.x, (float)player_one_bullet[i]->Center.y, player_Two_bullet[j]->Center.x, player_Two_bullet[j]->Center.y);
				}

			}	
		}

		for (int j = 0; j < MAXBULLET; j++)																		// 1P�� �߻��� �ڱ��ڽ��� �Ѿ˳��� �浹 ó���κ�
		{
			if (i == j)continue;																				// �ڱ� �ڽ� �Ѿ� �ҷ����� ����
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

		for (int j = 0; j < MAXBULLET; j++)																		// 2P�� �߻��� �ڱ��ڽ��� �Ѿ˳��� �浹 ó���κ�
		{
			if (i == j)continue;																				// �ڱ� �ڽ� �Ѿ� �ҷ����� ����
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

void GameStudy::Defence()													// 1P ���Ű� 2P ���ſ��� �Ѿ� ����
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (player_one_bullet[i] != NULL)									// 1P�� �Ѿ��� �߻� ���� �� 2P ���ſ��� ����ϴ� �κ� (1P������ 2P�� ƨ�� �ڽ��� �Ѿ��� �ٽ� ƨ��� �ϴ� �κ�) 
		{																	// �� ���ſ����� �� �Ѿ�, ���Ѿ� ���� �ݻ�
			// 1P���� �߻��� �Ѿ˰� 2P�� ������ �Ÿ� ��� �κ�
			int width_one_enemy = sqrt(pow((_Two_Player_Barrel.center.x - player_one_bullet[i]->Center.x), 2) +
				pow((_Two_Player_Barrel.center.y - player_one_bullet[i]->Center.y), 2));

			// 1P���� �߻��� �Ѿ˰� 1P�� ������ �Ÿ� ��� �κ�
			int width_one_my = sqrt(pow((_One_Player_Barrel.center.x - player_one_bullet[i]->Center.x), 2) +
				pow((_One_Player_Barrel.center.y - player_one_bullet[i]->Center.y), 2));


			// 2P�� �������� 1P �Ѿ��� ������ �� �Ѿ� ���� ó��
			if ((_Two_Player_Barrel.barrel_radius / 2) + (player_one_bullet[i]->radius / 2) >= width_one_enemy)
			{
				player_one_bullet[i]->angle = getAngle((float)_Two_Player_Barrel.center.x, (float)_Two_Player_Barrel.center.y, player_one_bullet[i]->Center.x, player_one_bullet[i]->Center.y);
				
			}

			// 2P�� �������� ���Ƴ�(ƨ�ܳ�) 1P �Ѿ��� �������� �Ѿ� ���� ó��
			if ((_One_Player_Barrel.barrel_radius / 2) + (player_one_bullet[i]->radius / 2) >= width_one_my)
			{
				player_one_bullet[i]->angle = getAngle((float)_One_Player_Barrel.center.x, (float)_One_Player_Barrel.center.y, player_one_bullet[i]->Center.x, player_one_bullet[i]->Center.y);

			}

		}

		if (player_Two_bullet[i] != NULL)									// 2P�� �Ѿ��� �߻� ���� �� 1P ���ſ��� ����ϴ� �κ� (2P������ 1P�� ƨ�� �ڽ��� �Ѿ��� �ٽ� ƨ��� �ϴ� �κ�) 
		{																	// �� ���ſ����� �� �Ѿ�, ���Ѿ� ���� �ݻ�
		
			// 2P���� �߻��� �Ѿ˰� 1P�� ������ �Ÿ� ��� �κ�
			int width_Two_enemy = sqrt(pow((_One_Player_Barrel.center.x - player_Two_bullet[i]->Center.x), 2) +
				pow((_One_Player_Barrel.center.y - player_Two_bullet[i]->Center.y), 2));

			// 2P���� �߻��� �Ѿ˰� 2P�� ������ �Ÿ� ��� �κ�
			int width_Two_my = sqrt(pow((_Two_Player_Barrel.center.x - player_Two_bullet[i]->Center.x), 2) +
				pow((_Two_Player_Barrel.center.y - player_Two_bullet[i]->Center.y), 2));


			// 1P�� �������� 2P �Ѿ��� ������ �� �Ѿ� ���� ó��
			if ((_One_Player_Barrel.barrel_radius / 2) + (player_Two_bullet[i]->radius / 2) >= width_Two_enemy)
			{
				player_Two_bullet[i]->angle = getAngle((float)_One_Player_Barrel.center.x, (float)_One_Player_Barrel.center.y, player_Two_bullet[i]->Center.x, player_Two_bullet[i]->Center.y);

			}

			// 1P�� �������� 2P �Ѿ��� ������ �� �Ѿ� ���� ó��
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
		if (player_one_bullet[i] != NULL)									// 1P�� �Ѿ��� �߻� ���� �� 2P ��ü���� �¾Ƽ� 1P�� ������ �ö󰡴� �κ�
		{																	// 1P�� �߻��� �Ѿ��� �������.
			// 1P���� �߻��� �Ѿ˰� 2P�� ��ü�Ÿ� ��� �κ�
			int width_one_enemy = sqrt(pow((_Two_Player.center.x - player_one_bullet[i]->Center.x), 2) +
				pow((_Two_Player.center.y - player_one_bullet[i]->Center.y), 2));

			// 2P�� 1P�� �Ѿ��� �¾��� �� ����, �Ѿ�ó��
			if ((_Two_Player.radius / 2) + (player_one_bullet[i]->radius / 2) >= width_one_enemy)
			{
				delete player_one_bullet[i];
				player_one_bullet[i] = NULL;
				One_Player_Score++;

			}
		}

		if (player_one_bullet[i] != NULL)									// 1P�� �ڱ��ڽ��� �Ѿ��� �¾����� ó���ϴ� �κ� 2P�� ������ �ö󰣴�.
		{																	// 1P�� �Ѿ��� �������.
			// 1P���� �߻��� �Ѿ˰� 1P�� ��ü�Ÿ� ��� �κ�
			int width_one_my = sqrt(pow((_One_Player.center.x - player_one_bullet[i]->Center.x), 2) +
				pow((_One_Player.center.y - player_one_bullet[i]->Center.y), 2));


			// 1P �Ѿ��� 1P�� �¾�����(�ڱ� �ڽ��� �� �Ѿ��� �¾�����)
			if ((_One_Player.radius / 2) + (player_one_bullet[i]->radius / 2) >= width_one_my)
			{
				delete player_one_bullet[i];
				player_one_bullet[i] = NULL;
				Two_Player_Score++;
			}

		}
		
		if (player_Two_bullet[i] != NULL)									// 2P�� �Ѿ��� �߻� ���� �� 1P ��ü���� �´� �κ� 2P�� ������ �ö󰣴�. 
		{																	// 2P�� �Ѿ��� �������.

			// 2P���� �߻��� �Ѿ˰� 1P�� ��ü�Ÿ� ��� �κ�
			int width_Two_enemy = sqrt(pow((_One_Player.center.x - player_Two_bullet[i]->Center.x), 2) +
				pow((_One_Player.center.y - player_Two_bullet[i]->Center.y), 2));


			// 1P�� 2P �Ѿ��� �¾��� �� �Ѿ�, ���� ó��
			if ((_One_Player.radius / 2) + (player_Two_bullet[i]->radius / 2) >= width_Two_enemy)
			{
				delete player_Two_bullet[i];
				player_Two_bullet[i] = NULL;
				Two_Player_Score++;

			}

		}

		if (player_Two_bullet[i] != NULL)																// 2P�� �ڱ� �ڽ����� �Ѿ��� �¾����� 1P�� ������ �ö󰣴�.
		{																								// 2P�� �Ѿ��� �������.
			// 2P���� �߻��� �Ѿ˰� 2P�� ��ü�Ÿ� ��� �κ�
			int width_Two_my = sqrt(pow((_Two_Player.center.x - player_Two_bullet[i]->Center.x), 2) +
				pow((_Two_Player.center.y - player_Two_bullet[i]->Center.y), 2));


			// 2P�� �ڱ� �ڽ� �Ѿ��� �¾��� �� �Ѿ�, ���� ó��
			if ((_Two_Player.radius / 2) + (player_Two_bullet[i]->radius / 2) >= width_Two_my)
			{
				delete player_Two_bullet[i];
				player_Two_bullet[i] = NULL;
				One_Player_Score++;
			}
		}
		
	}
}




float GameStudy::getAngle(float x1, float y1, float x2, float y2)					// �浹����...(����) 
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

