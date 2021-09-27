#pragma once
#include "GameObject.h"

class Image;
class SelectIcon : public GameObject
{
private:
	Image* icon;

	int frameX, frameY;
	int* frameXData;
	int frameXDataInput[5];



	bool isSelect;

	int playerNum;
	int elapsedCount;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetPlayerNum(int num) { this->playerNum = num; }
};

