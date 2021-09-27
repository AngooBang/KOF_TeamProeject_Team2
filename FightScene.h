#pragma once
#include "GameEntity.h"

class Image;
class HPBar;
class UI;
class Timer;
class Terry;
class Mary;
class Map;
class FightScene : GameEntity
{
private:
	HANDLE hSecTimer;

	bool isSecTimer;
	// UI
	char text[128];


	// 배경 이미지
	Image* backGround;
	Map* map;

	//UI
	UI* HP;

	Timer* roundTimer;


	MoveDir moveDir;
public:

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetIsSecTimer(bool isSecTimer) { this->isSecTimer = isSecTimer; }

	inline bool GetIsSecTimer() { return this->isSecTimer; }
};

