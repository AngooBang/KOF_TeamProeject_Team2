#pragma once
#include "UI.h"

class HPBar : public UI
{
private:
	HANDLE HPDecMotion;

	Image* HPBarFrame;
	Image* HPBar;
	Image* Portrait;
	Image* KO;

	int hp;
	int lostHP;
	int damage;
	int portraitX1, portraitX2;
	
	bool hitP1, hitP2;
	bool isAlive;
	bool player1, player2;

	int elapsedCount;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetPlayer1(bool player1) { this->player1 = player1; }
	inline void SetPlayer2(bool player2) { this->player2 = player2; }

	inline void DamageToHp(int hp) { this->lostHP += hp; }
	

	inline bool GetIsAlive() { return this->isAlive; }
};

