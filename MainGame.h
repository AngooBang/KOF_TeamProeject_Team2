#pragma once
#include "Config.h"
#include "GameEntity.h"

// 우리가 구성할 게임 월드
class Image;
class HPBar;
class UI;
class Timer;
class Character;
class Map;
class Intro;
class StartScene;
class SelectScene;
class FightScene;
	
class MainGame : public GameEntity
{
private:
	// 타이머
	HANDLE hTimer;
	HANDLE hSecTimer;
	HANDLE hIntroTimer;

	bool isSecTimer;
	bool IntroTimer;
	// UI
	char text[128];

	int mousePosX;
	int mousePosY;
	int clickedMousePosX;
	int clickedMousePosY;

	// 백버퍼
	Image* backBuffer;

	Intro* intro;

	// 배경 이미지
	Image* backGround;
	Map* map;
	E_SCENE playScene;

	//UI
	UI* HP;

	Timer* roundTimer;

	Character* player1;
	Character* player2;

	MoveDir moveDir;
	StartScene* startScene;
	SelectScene* selectScene;
	FightScene* fightScene;

public:
	void Init();
	void Update();
	void SecUpdate();
	//void Render();			// 오버라이딩 : 상속 관계에서 부모클래스의 함수를 재정의
	void Render(HDC hdc);	// 오버로딩
	void Release();

	//LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void SetIsSecTimer(bool isSecTimer) { this->isSecTimer = isSecTimer; }

	inline bool GetIsSecTimer() { return this->isSecTimer; }
};

//int MainGame::clickedMousePosX = 0;