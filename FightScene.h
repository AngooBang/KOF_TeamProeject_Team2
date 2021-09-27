#pragma once
#include "GameEntity.h"

class Image;
class HPBar;
class UI;
class Timer;
class Map;
class Character;
class FightScene : public GameEntity
{
private:
	HANDLE hSecTimer;

	bool isSecTimer;

	// 배경 이미지
	Image* backGround;
	Map* map;

	// UI
	UI* HP;
	Timer* roundTimer;

	// 캐릭터
	Character* player1;
	Character* player2;

public:

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetIsSecTimer(bool isSecTimer) { this->isSecTimer = isSecTimer; }

	inline bool GetIsSecTimer() { return this->isSecTimer; }
};

