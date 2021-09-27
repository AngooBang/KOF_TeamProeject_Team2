#pragma once
#include "Config.h"
#include "GameEntity.h"

// �츮�� ������ ���� ����
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
	// Ÿ�̸�
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

	// �����
	Image* backBuffer;

	Intro* intro;

	// ��� �̹���
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
	//void Render();			// �������̵� : ��� ���迡�� �θ�Ŭ������ �Լ��� ������
	void Render(HDC hdc);	// �����ε�
	void Release();

	//LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void SetIsSecTimer(bool isSecTimer) { this->isSecTimer = isSecTimer; }

	inline bool GetIsSecTimer() { return this->isSecTimer; }
};

//int MainGame::clickedMousePosX = 0;