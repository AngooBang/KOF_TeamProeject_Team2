#pragma once
#include "UI.h"

class HPBar : public UI
{
private:
	Image* hpBarFrameImg;
	Image* hpBarImg;
	Image* portraitBackImg;
	Image* portraitImg;
	Image* koImg;

	int lostHp;
	int getDamage;
	int portraitBackImgX1, portraitBackImgX2;
	int portraitImgX1, portraitImgX2;
	int playerNum;
	int characterNum;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetPlayerNum(int playerNum) { this->playerNum = playerNum; }
	inline void DamageToHp(int getDamage) { this->lostHp += getDamage; }
	inline void SetCharacterNum(int characterNum) { this->characterNum = characterNum; }

	inline bool GetIsAlive() { return this->isAlive; }
};

