#pragma once
#include "GameNode.h"
typedef enum JANGGIMAL{	//말의 종류
	KING = 0, CANNON, ELEPHANT, HORSE, CAR, OFFICER, SOLDIER
};
typedef enum CAMP{	//진영의 종류
	RED = 0, BLUE
};
typedef enum JANGGI_TURN_STATE{	//턴의 상태 종류
	PLAY_TURN_START = 0, PLAY_MAL_CLICK, PLAY_MAL_MOVE, PLAY_MAL_MOVE_FAIL, PLAY_TURN_END
} TurnState;
class JangGiMal;
class JangGi : public GameNode{
private:
	typedef struct tagJangGiPan	{
		RECT rc;
		JangGiMal* mal;
		tagJangGiPan(RECT r) :rc(r), mal(NULL){}
	} JangGiPan;
	Image* _backImage;		//장기판 이미지
	JangGiMal* _mal[2][16];	//말의 정보를 가짐
	JangGiPan* _pan[10][9];	//이동 가능한 모든 위치의 정보를 가짐
	CAMP _turn;				//어느 진영의 턴이니
	TurnState _turnState;	//턴의 상태
	JangGiMal* _selectMal;	//선택한 말
	std::list<POINT> _movablePoint;	//선택한 말의 이동가능한 포인트들
	int _takeMal[2];		//잡힌 말의 갯수
	bool _isGameEnd;		//게임 끝?
	bool _isJangGun;		//장군?
	CAMP _jangGunCamp;		//누가 장군받았니?
public:
	JangGi();
	~JangGi(){}
	HRESULT initialize();
	void release();
	void update();
	void render();
	std::list<POINT> movablePoint(JangGiMal* mal);	//말의 위치와 종류를 보고 이동 가능한 좌표들을 리턴
	bool checkMovablePoint(int startX, int startY, int endX, int endY, JangGiMal *mal);	//말의 종류 따라 시작지점에서 끝지점으로 이동 가능한지의 여부
	void addMovablePoint(int malX, int malY, int endX, int endY, JangGiMal* mal, std::list<POINT> * lPoint); //말의 위치에서 이동할 상대 위치를 입력해 이동 가능하면 해당 상대좌표를 리스트에 넣음 
	bool checkMovablePointByCannon(int startX, int startY, int endX, int endY, JangGiMal *mal, bool isExistWall); //포 버전
	void changeTurn();	//턴 바꿈. 장군 여부도 판단
	void selectMal();	//말선택
	void moveMal();		//말 움직임
	void takeMal(JangGiMal*);	//말 잡음
};
class JangGiMal{
private:
	int _x, _y;	//말의 x, y위치
	const JANGGIMAL _kind;	//말의 종류
	const CAMP _camp;				//진영
	SpriteImage* _image;	//말 이미지
public:
	JangGiMal(int x, int y, JANGGIMAL mal, CAMP camp);
	~JangGiMal(){}
	void release();
	void move(POINT point);
	inline int getX(){ return _x; }
	inline int getY(){ return _y; }
	inline void setX(float x){ _x = x; }
	inline void setY(float y){ _y = y; }
	SpriteImage* getImage(){ return _image; }
	inline JANGGIMAL getKind(){ return _kind; }
	inline CAMP getCamp(){ return _camp; }
};