#pragma once
#include "Config.h"
#include "GameEntity.h"

// �츮�� ������ ���� ����
class Image;
class HPBar;
class UI;
class Timer;
class Iori;
class Terry;
class Mary;
class MainGame : public GameEntity
{
private:
	// Ÿ�̸�
	HANDLE hTimer;
	HANDLE hSecTimer;

	bool isSecTimer;
	// UI
	char text[128];

	int mousePosX;
	int mousePosY;
	int clickedMousePosX;
	int clickedMousePosY;

	// �����
	Image* backBuffer;

	// ��� �̹���
	Image* backGround;

	//UI
	UI* HP;

	Timer* roundTimer;

	// �̿���
	//Iori* ioriX;
	//Iori** ioriY;
	Terry* terry;
	Mary* mary;

	MoveDir moveDir;

public:
	void Init();
	void Update();
	//void Render();			// �������̵� : ��� ���迡�� �θ�Ŭ������ �Լ��� ������
	void Render(HDC hdc);	// �����ε�
	void Release();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void SetIsSecTimer(bool isSecTimer) { this->isSecTimer = isSecTimer; }

	bool GetIsSecTimer() { return this->isSecTimer; }
};

//int MainGame::clickedMousePosX = 0;