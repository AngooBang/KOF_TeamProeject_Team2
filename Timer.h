#pragma once
#include "UI.h"

class HPBar;
class Timer : public UI
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

