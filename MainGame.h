#pragma once
#include "Config.h"
#include "GameEntity.h"

// �츮�� ������ ���� ����
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
	// Ÿ�̸�
	HANDLE hTimer;


public:
	void Init();
	void Update();
	void SecUpdate();
	//void Render();			// �������̵� : ��� ���迡�� �θ�Ŭ������ �Լ��� ������
	void Render(HDC hdc);	// �����ε�
	void Release();

};

//int MainGame::clickedMousePosX = 0;