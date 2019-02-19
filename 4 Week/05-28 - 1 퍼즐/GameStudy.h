#pragma once
#include "GameNode.h"
#include "Image.h"

#define PUZZLE_COL 10
#define PUZZLE_ROW PUZZLE_COL

#if PUZZLE_COL > 10
#define PUZZLE_COL 10
#endif

#if PUZZLE_ROW > 10
#define PUZZLE_ROW 10
#endif

#define PUZZLE_LENGTH (PUZZLE_COL * PUZZLE_ROW)
//#define AUTO_PUZZLE TRUE

using namespace std;

class GameStudy :
	public GameNode
{
private:
	Image *_background;

	Image *_puzzleImage;

	int _puzzleNum[PUZZLE_LENGTH];
	RECT _puzzleRect[PUZZLE_LENGTH];
	int _voidNum;

	int _pieceWidth, _pieceHeight;

	bool _isGameStart = false;

	int puzzleSwap(int clickNum);

	vector<int> _memorySwapNum;
	int _memorySwapNum2[PUZZLE_LENGTH * PUZZLE_LENGTH];
	int _memoryIndex;

public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void gameInit();

	void setBackBuffer();
};

