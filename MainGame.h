#pragma once
#include "GameEntity.h"

// �츮�� ������ ���� ����
class Image;
class StartScene;
class SelectScene;
class FightScene;
	
class MainGame : public GameEntity
{
private:
	// Ÿ�̸�
	HANDLE hTimer;
	HANDLE hSecTimer;

	bool isSecTimer;

	// �����
	Image* backBuffer;

	E_SCENE playScene;


	StartScene* startScene;
	SelectScene* selectScene;
	FightScene* fightScene;

public:
	void Init();
	void Update();
	void Render(HDC hdc);	
	void Release();

	//LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void SetIsSecTimer(bool isSecTimer) { this->isSecTimer = isSecTimer; }

	inline bool GetIsSecTimer() { return this->isSecTimer; }
};
