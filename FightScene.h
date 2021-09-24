#pragma once
#include "Scene.h"
#include "Config.h"
#include "GameEntity.h"

class Image;
class HPBar;
class UI;
class Timer;
class Terry;
class Mary;
class Map;
class FightScene : public Scene
{
private:
	HANDLE hSecTimer;

	bool isSecTimer;
	// UI
	char text[128];

	// 백버퍼
	Image* backBuffer;

	// 배경 이미지
	Image* backGround;
	Map* map;

	//UI
	UI* HP;

	Timer* roundTimer;

	Terry* terry;
	Mary* mary;

	MoveDir moveDir;
public:

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetIsSecTimer(bool isSecTimer) { this->isSecTimer = isSecTimer; }

	inline bool GetIsSecTimer() { return this->isSecTimer; }
};

