#pragma once
#include "GameObject.h"
#include "Config.h"

class Image;
class UI : public GameObject
{
private:
	HANDLE hTimer;

	Image* HP_bar;
	Image* Health_point;
	Image* Timer;
	Image* Time_Over;
	Image* KO;

	int lostHp;
	int elapsedCount;
	int lostHp_Player1, lostHp_Player2;
	//timer_FrameX1(초 10단위), timer_FrameX2(초 1단위)
	int timer_FrameX1,timer_FrameX2, timer_FrameY;
	

	bool hit_Player1, hit_Player2;
	bool isAlive;

public:
	void Init();
	void InitTimer();
	void Update();
	void Render(HDC hdc);
	void RenderTimer(HDC hdc);
	void Release();

	inline void SetHitStatus1(bool hit_player1) { this->hit_Player1 = hit_player1; }
	inline void SetHitStatus2(bool hit_player2) { this->hit_Player2 = hit_player2; }
	inline bool SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }
};


