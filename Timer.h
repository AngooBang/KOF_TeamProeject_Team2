#pragma once
#include "GameObject.h"

class HPBar;
class Image;
class Timer : public GameObject
{
private:
	Image* timerNumImg;
	Image* timeOverImg;

	int tenSecNumImg;
	int oneSecNumImg;
	int chgNumColor;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline bool SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
};

