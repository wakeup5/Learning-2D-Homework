#pragma once
#include "GameNode.h"
#include "Bullet.h"
#include "Image.h"
#include "SpriteImage.h"

using namespace std;


class GameObject
{
private:
	Image *_image;
	float _centerX = 0, _centerY = 0;

	float _imageX = 0.0f, _imageY = 0.0f;
	int _imageWidth = 0, _imageHeight = 0;

public:
	GameObject() :_image(NULL){}
	~GameObject(){}

	void setImage(Image* image){ _image = image; }
	void setImageInfo(float x, float y, int width, int height)
	{
		_imageX = x; _imageY = y; _imageWidth = width; _imageHeight = height;
	}

	void setPosition(float x, float y)
	{
		_centerX = x; _centerY = y;
	}

	POINT getPosition(){ return POINT{ _centerX, _centerY }; }
	RECT getRect(){ return makeRectCenter(_centerX, _centerY, _imageWidth, _imageHeight); }

	void draw(HDC hdc)
	{
		_image->render(hdc, _centerX - _imageWidth / 2, _centerY - _imageHeight / 2, _imageX, _imageY, _imageWidth, _imageHeight);
	}
};

class Player : public GameObject
{
public:
	enum PLAYER_ITEM_STATE
	{
		ITEM_STATE_TWO = 0,
		ITEM_STATE_LONG,
		ITEM_STATE_SHOOT,
		ITEM_STATE_BASIC
	};

	enum PLAYER_STATE
	{
		STATE_LEFT,
		STATE_RIGHT,
		STATE_STAY
	};

private:
	PLAYER_ITEM_STATE _itemState;
	PLAYER_STATE _state;

public:
	void setState(PLAYER_STATE s)
	{
		_state = s;
	}
	void setItemState(PLAYER_ITEM_STATE s)
	{
		_itemState = s;
		switch (_itemState)
		{
		case ITEM_STATE_BASIC:
			setImageInfo(0, 224, 64, 16);
			break;
		case ITEM_STATE_LONG:
			setImageInfo(0, 240, 96, 16);
			break;
		case ITEM_STATE_SHOOT:
			setImageInfo(0, 256, 64, 16);
			break;
		}
	}

	PLAYER_STATE getState(){ return _state; }
	PLAYER_ITEM_STATE getItemState(){ return _itemState; }
};

class Block : public GameObject
{
private :
	int _color;
	int _hp = 1;
public :
	void setColor(int color){ _color = color; }
	int getHp(){ return _hp; }
	void setHp(int hp)
	{
		_hp = hp; 
		setImageInfo((_hp - 1) * 64, _color * 32, 64, 16);
	}
};

typedef Bullet Object;

class GameStudy :
	public GameNode
{
private:
	typedef struct tagBall
	{
		Bullet b;
		bool isFire = false;
	}Ball;

	typedef struct tagItem
	{
		Bullet item;
		Player::PLAYER_ITEM_STATE itemNum;
		bool isLive = false;
	}Item;

	Image *_ballImage;

	Image *_background;
	Image *_image;

	Ball _ball[10];
	Player _player;

	Block _block[30];

	bool _isStart;

	Item _item[10];

	bool _isShoot;
	int _shootTime;

	Bullet _bullet[20];

public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void gameInit();

	void setBackBuffer();

	void dropItem();

	void fireBullet();
	void shootTime();
	void bulletMove();
	void bulletCollition();

	void dropItem(POINT startPosition);
};
