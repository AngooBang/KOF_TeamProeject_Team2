#pragma once
#include "UI.h"

class HPBar : public UI
{
private:
	Image* hpBarFrameImg;
	Image* hpBarImg;
	Image* portraitBackImg;
	Image* koImg;

	int lostHp;
	int getDamage;
	int portraitBackImgX1, portraitBackImgX2;
	int playerNum;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetPlayerNum(int playerNum) { this->playerNum = playerNum; }
	inline void DamageToHp(int getDamage) { this->lostHp += getDamage; }

	inline bool GetIsAlive() { return this->isAlive; }
};

