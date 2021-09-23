#pragma once
#include "GameObject.h"
#include <string>

class Image;
class Character : public GameObject
{
protected:
	Image* img;
	int frameX, frameY;
	int elapsedCount;
	int actionFrameX[15], maxFrame, walkFrameX[15];
	int hp;
	bool isAlive, isStatus, isMoveRight, isMoveLeft, isHit, istest, isMove;
	char ch[50];
	string fileName;


	enum Action { Basic, fMove, bMove, sHand, bHand, sKick, bKick, sHit, bHit, END };
	Action action;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetHit(bool isHit) { this->isHit = isHit; }


};

