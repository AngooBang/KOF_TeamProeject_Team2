#include "MainGame.h"
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

void MainGame::Init()
{
	//KeyManager keyMgr;
	KeyManager::GetSingleton()->Init();

	//�� ����
	//SceneManager::GetSingleton()->ChangeScene(E_SCENE_FIGHT);

	// Ÿ�̸� ����
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);



	//���� Ÿ�̸�
	roundTimer = new Timer;
	roundTimer->Init();

	// ��� �̹���
	backGround = new Image;
	if (!SUCCEEDED(backGround->Init("Image/mapImage.bmp", 1400, 933)))
	{
		cout << "Image/bin.bmp ���� �ε忡 �����ߴ�." << endl;
	}

	map = new Map;
	map->Init();


	terry = new Terry;
	terry->Init();
	mary = new Mary;
	mary->Init();	

	terry->ammo->SetTarget(mary);
	mary->ammo->SetTarget(terry);

void MainGame::Update()
{
	//SceneManager::GetSingleton()->pScene->Update();

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


void MainGame::Render(HDC hdc)
{
	//SceneManager::GetSingleton()->pScene->Render();

	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->Render(hBackBufferDC);

	map->Render(hBackBufferDC);

	terry->Render(hBackBufferDC);
	mary->Render(hBackBufferDC);

	HP->Render(hBackBufferDC);
	roundTimer->Render(hBackBufferDC);

	backBuffer->Render(hdc);

}

void MainGame::Release()
{
	//SceneManager::GetSingleton()->pScene->Release();
	SAFE_RELEASE(backBuffer);

	SAFE_RELEASE(backGround);

	SAFE_RELEASE(map);

	SAFE_RELEASE(HP);

	SAFE_RELEASE(roundTimer);

	SAFE_RELEASE(terry);

	SAFE_RELEASE(mary);
	// Ÿ�̸� ��ü ����
	KillTimer(g_hWnd, 0);
}

