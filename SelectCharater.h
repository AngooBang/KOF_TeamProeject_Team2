#pragma once
#include "Config.h"
#include "image.h"
#include "KeyManager.h"

class SelectCharater
{
private:
	Image* SelectBackground;

	Image* SelectChar;
	Image* SelectIconP;

	Image* SelectCharframe;

	Image* SelectIconP2;

	int elapsedtCount;

	int selectCharFrameNum;
	int selectCharFrameX;
	int selectCharFrameX2;

	int selectCharFramePos;

	POINT SelectCharPos[2];

	HANDLE hTimer;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

