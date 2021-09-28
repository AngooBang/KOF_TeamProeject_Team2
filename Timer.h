#pragma once
#include "GameObject.h"

class HPBar;
class Image;
class Timer : public GameObject
{
private:
	Image* timerNumImg;
	Image* timeOverImg;
	Image* timeOverImgEffect;

	int tenSecNumImg;
	int oneSecNumImg;
	int chgNumColor;

	int elapsedcount1, elapsedcount2;

	bool wordEffect;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline bool SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
};

