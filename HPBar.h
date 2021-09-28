#pragma once
#include "GameObject.h"

class Image;
class HPBar : public GameObject
{
private:
	Image* hpBarFrameImg;
	Image* hpBarImg;
	Image* hpBarEffect;
	Image* portraitBackImg;
	Image* koImg;
	Image* koImgEffect;

	Image* portraitImg;

	CharacterType characterType;

	int lostHp;
	int lostHpMotion;
	int getDamage;
	int portraitImgFrameX;
	int playerNum;
	int elapsedcount;

	bool wordEffect;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void DamageToHp(int getDamage) { this->lostHp += getDamage; }

	inline void SetCharacterType(CharacterType type) { this->characterType = type; }


	inline void SetPlayerNum(int playerNum) { this->playerNum = playerNum; }

	inline bool GetIsAlive() { return this->isAlive; }
};