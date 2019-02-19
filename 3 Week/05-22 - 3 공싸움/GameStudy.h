#pragma once
#include "GameNode.h"

//  1. ��Ű ���� �����

#define PI					3.141592654f					// ����

#define	PLAYER_SIZE			150								// �÷��̾� ũ��
#define	BARREL_SIZE			30								// �÷��̾��� ���� ũ��

#define	MAX_CHAR			128								// ���ڿ� ���� �ִ�
#define SPEED				10								// ���ǵ�
#define	MAXBULLET			20								// �Ѿ� �ƽø�
#define BULLET_DISTANCE		100								// �Ѿ� �� ����




using namespace std;

class GameStudy :
	public GameNode
{
private:

	typedef struct tagPlayer
	{
		POINT center;										// �÷��̾��� ��ġ
		float angle;										// �÷��̾��� ���Ȱ�(��ǻ�Ͱ� �о� ���̴� ����)
		int radius;											// �÷��̾��� ��ü ũ��
		
	}Player;

	typedef struct tagPlayerBarrel
	{
		POINT center;										// ������ ��ġ
		float angel;										// �÷��̾��� ���� ���� ��
		int barrel_radius;									// �÷��̾��� ���� ũ��

	}BARREL;

	typedef struct tagbullet
	{
		POINT	Center;										// �Ѿ��� ��ġ
		int		Speed;										// �Ѿ��� ���ǵ�
		float	angle;										// ���� ����
		int		radius;										// �Ѿ��� ũ��

	}Bullet;

	Player _One_Player;										// 1P �÷��̾�
	Player _Two_Player;										// 2P �÷��̾�

	BARREL _One_Player_Barrel;								// 1P �÷��̾��� ����
	BARREL _Two_Player_Barrel;								// 2P �÷��̾��� ����

	Bullet* player_one_bullet[MAXBULLET];					// 1P �÷��̾��� �Ѿ�
	Bullet* player_Two_bullet[MAXBULLET];					// 2P �÷��̾��� �Ѿ�
	
	
	
	HBRUSH	MyBrush, OldBrush;								// �귯�� ����
	HFONT	hFont, OldFont;									// ��Ʈ ����
	HPEN	Mypen, Oldpen;									// �� ����

	int One_Player_Score, Two_Player_Score;					// �÷��̾���� ����
	bool crush_check;										// ���� �÷��̾���� �Ѿ˿� �¾Ҵ����� ���� �� üũ

	int Player_One_destance, Player_Two_destance;			// ���� �÷��̾� ���� �Ѿ� ����
	
	

public:
	virtual HRESULT initialize(void);						// �ʱ�ȭ �κ�
	virtual void release(void);
	virtual void update(void);								// ������Ʈ
	virtual void render(HDC hdc);							// ��ºκ�

	void One_Player_Move();									// ù��° �÷��̾� �̵� �Լ�
	void Two_Player_Move();									// �ι�° �÷��̾� �̵� �Լ�

	void Player_One_Bullet_Make();							// 1P �� �Ѿ� ����
	void Player_One_Bullet_Shot();							// 1P �� �Ѿ� �߻�(�̵�), ����


	void Player_Two_Bullet_Make();							// 2P �� �Ѿ� ����
	void Player_Two_Bullet_Shot();							// 2P �� �Ѿ� �߻�(�̵�), ����

	void Plus_Score();										// ���ھ�
	void Bullet_Crush();									// �Ѿ� �浹
	void Defence();											// ������ �÷��̾��� ���ſ� �Ѿ��� �ε����� ���ó��

	float getAngle(float x1, float y1, float x2, float y2);	// �浹 ���

		
	GameStudy(){}
	virtual ~GameStudy(){}
};

