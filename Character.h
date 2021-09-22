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
	int walkFrameX[15], maxFrame;
	int hp;
	bool isAlive, isStatus, isMoveRight, isMoveLeft, isHit;
	char ch[50];
	string fileName;
	

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetHit(bool isHit) { this->isHit = isHit; }

};

