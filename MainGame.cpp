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
	hSecTimer = (HANDLE)SetTimer(g_hWnd, 1, 1000, NULL);

	// �����
	backBuffer = new Image;
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);

	// HP
	HP = new UI;
	HP->Init();

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

}

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

	InvalidateRect(g_hWnd, NULL, false);
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
	KillTimer(g_hWnd, 1);
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
		
			break;
		case VK_UP:
			
			break;
		case VK_DOWN:
		
			break;
		case VK_LEFT:
		
			break;
		case VK_RIGHT:
			
			break;
		}
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
