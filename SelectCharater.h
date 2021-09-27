#pragma once
#include "GameObject.h"

class Image;
class SelectIcon;
class SelectCharater : public GameObject
{
private:
	Image* selectBackground;

	Image* selectChar1;
	Image* selectChar2;

	//Image* selectIconP;
	//Image* selectIconP2;

	Image* selectCharframe;

	SelectIcon* icon;
	//SelectIcon* iconP1;
	SelectIcon* iconP2;

	int elapsedtCount;

	//int selectCharFrameNum1;
	//int selectCharFrameNum2;
	//int selectCharFrameX1;
	//int selectCharFrameX2;

	int selectCharFramePos;


	//POINT selectCharPos[2];

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

