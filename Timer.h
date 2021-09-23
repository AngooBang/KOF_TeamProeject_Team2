#pragma once
#include "UI.h"

class HPBar;
class Timer : public UI
{
private:
	Image* SecTimer;
	Image* TimeOver;

	int tenSec;
	int oneSec;
	int chgNumColor;

	bool isAlive;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline bool SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
};

