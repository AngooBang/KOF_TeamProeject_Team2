#include "FightScene.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Image.h"
#include "Terry.h"
#include "HPBar.h"
#include "Timer.h"
#include "Mary.h"
#include "UI.h"
#include "Map.h"

void FightScene::Init()
{

	//hSecTimer = (HANDLE)SetTimer(g_hWnd, 1, 1000, NULL);

	// HP
	HP = new UI;
	HP->Init();

	//���� Ÿ�̸�
	roundTimer = new Timer;
	roundTimer->Init();

	// ��� �̹���
	backGround = new Image; 
	backGround->Init("Image/mapImage.bmp", 1400, 933);

	map = new Map;
	map->Init();

	terry = new Terry;
	terry->Init();
	mary = new Mary;
	mary->Init();

	terry->ammo->SetTarget(mary);
	mary->ammo->SetTarget(terry);

}

void FightScene::Update()
{
	terry->Update();
	mary->Update();
	HP->Update();
	map->Update();
	if (isSecTimer)
	{

		if (HP->GetIsAlive() == true)
		{
			roundTimer->Update();
		}
		isSecTimer = false;
	}

	InvalidateRect(g_hWnd, NULL, false);
}

void FightScene::Render(HDC hdc)
{

	backGround->Render(hdc);

	map->Render(hdc);

	terry->Render(hdc);
	mary->Render(hdc);

	HP->Render(hdc);
	roundTimer->Render(hdc);

}

void FightScene::Release()
{


	SAFE_RELEASE(backGround);

	SAFE_RELEASE(map);

	SAFE_RELEASE(HP);

	SAFE_RELEASE(roundTimer);

	SAFE_RELEASE(terry);

	SAFE_RELEASE(mary);

	KillTimer(g_hWnd, 1);
}
