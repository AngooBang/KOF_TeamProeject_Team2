#pragma once
#include "UI.h"

class HPBar : public UI
{
private:
	Image* HPBarFrame;
	Image* HPBar;
	Image* KO;

	int HP;
	int lostHP;
	int damage;
	
	bool hitP1, hitP2;
	bool isAlive;
	bool player1, player2;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetPlayer1(bool player1) { this->player1 = player1; }
	inline void SetPlayer2(bool player2) { this->player2 = player2; }

	inline bool GetIsAlive() { return this->isAlive; }
};

