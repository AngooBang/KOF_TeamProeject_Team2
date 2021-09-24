#pragma once
#include "Config.h"
#include "GameEntity.h"

// 우리가 구성할 게임 월드
class Image;
class HPBar;
class UI;
class Timer;
class Terry;
class Mary;
class Map;
class MainGame : public GameEntity
{
private:
	// 타이머
	HANDLE hTimer;


public:
	void Init();
	void Update();
	void SecUpdate();
	//void Render();			// 오버라이딩 : 상속 관계에서 부모클래스의 함수를 재정의
	void Render(HDC hdc);	// 오버로딩
	void Release();

};

//int MainGame::clickedMousePosX = 0;