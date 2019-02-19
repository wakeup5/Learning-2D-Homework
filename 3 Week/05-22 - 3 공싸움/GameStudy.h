#pragma once
#include "GameNode.h"

//  1. 하키 게임 만들기

#define PI					3.141592654f					// 파이

#define	PLAYER_SIZE			150								// 플레이어 크기
#define	BARREL_SIZE			30								// 플레이어의 포신 크기

#define	MAX_CHAR			128								// 문자열 길이 최대
#define SPEED				10								// 스피드
#define	MAXBULLET			20								// 총알 맥시멈
#define BULLET_DISTANCE		100								// 총알 간 간격




using namespace std;

class GameStudy :
	public GameNode
{
private:

	typedef struct tagPlayer
	{
		POINT center;										// 플레이어의 위치
		float angle;										// 플레이어의 라디안값(컴퓨터가 읽어 들이는 각도)
		int radius;											// 플레이어의 본체 크기
		
	}Player;

	typedef struct tagPlayerBarrel
	{
		POINT center;										// 포신의 위치
		float angel;										// 플레이어의 포신 라디안 값
		int barrel_radius;									// 플레이어의 포신 크기

	}BARREL;

	typedef struct tagbullet
	{
		POINT	Center;										// 총알의 위치
		int		Speed;										// 총알의 스피드
		float	angle;										// 공의 각도
		int		radius;										// 총알의 크기

	}Bullet;

	Player _One_Player;										// 1P 플레이어
	Player _Two_Player;										// 2P 플레이어

	BARREL _One_Player_Barrel;								// 1P 플레이어의 포신
	BARREL _Two_Player_Barrel;								// 2P 플레이어의 포신

	Bullet* player_one_bullet[MAXBULLET];					// 1P 플레이어의 총알
	Bullet* player_Two_bullet[MAXBULLET];					// 2P 플레이어의 총알
	
	
	
	HBRUSH	MyBrush, OldBrush;								// 브러쉬 저장
	HFONT	hFont, OldFont;									// 폰트 저장
	HPEN	Mypen, Oldpen;									// 펜 저장

	int One_Player_Score, Two_Player_Score;					// 플레이어들의 점수
	bool crush_check;										// 각각 플레이어들이 총알에 맞았는지에 대한 불 체크

	int Player_One_destance, Player_Two_destance;			// 각각 플레이어 들의 총알 간격
	
	

public:
	virtual HRESULT initialize(void);						// 초기화 부분
	virtual void release(void);
	virtual void update(void);								// 업데이트
	virtual void render(HDC hdc);							// 출력부분

	void One_Player_Move();									// 첫번째 플레이어 이동 함수
	void Two_Player_Move();									// 두번째 플레이어 이동 함수

	void Player_One_Bullet_Make();							// 1P 의 총알 생성
	void Player_One_Bullet_Shot();							// 1P 의 총알 발사(이동), 삭제


	void Player_Two_Bullet_Make();							// 2P 의 총알 생성
	void Player_Two_Bullet_Shot();							// 2P 의 총알 발사(이동), 삭제

	void Plus_Score();										// 스코어
	void Bullet_Crush();									// 총알 충돌
	void Defence();											// 각각의 플레이어의 포신에 총알을 부딪힐대 방어처리

	float getAngle(float x1, float y1, float x2, float y2);	// 충돌 계산

		
	GameStudy(){}
	virtual ~GameStudy(){}
};

