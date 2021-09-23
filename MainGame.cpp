#include "MainGame.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "Terry.h"
#include "UI.h"



void MainGame::Init()
{
	//KeyManager keyMgr;
	KeyManager::GetSingleton()->Init();
	SceneManager::GetSingleton();

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 100, NULL);

	// 백버퍼
	backBuffer = new Image;
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);

	// HP
	player1_Hp = new UI;
	player1_Hp->Init();
	POINTFLOAT pos1{ HP_BAR_SET_X, HP_BAR_SET_Y };
	player1_Hp->SetPos(pos1);
	
	
	player2_Hp = new UI;
	player2_Hp->Init();
	POINTFLOAT pos2{ WIN_SIZE_X - HP_BAR_SET_X, HP_BAR_SET_Y };
	player2_Hp->SetPos(pos2);

	//게임 타이머
	Game_Timer = new UI;
	Game_Timer->InitTimer();
	


	// 배경 이미지
	backGround = new Image;
	if (!SUCCEEDED(backGround->Init("Image/mapImage.bmp", 1400, 933)))
	{
		cout << "Image/bin.bmp 파일 로드에 실패했다." << endl;
	}
	terry = new Terry;
	terry->Init();

}

void MainGame::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		player1_Hp->SetHitStatus1(true);
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		player2_Hp->SetHitStatus2(true);
	}

	player1_Hp->Update();
	player2_Hp->Update();
	
	if (!(player1_Hp->GetIsAlive() == false || player2_Hp->GetIsAlive() == false))
	{
		Game_Timer->Update();
	}
	

	terry->Update();
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	wsprintf(text, "MousePosX : %d", mousePosX);
	TextOut(hBackBufferDC, 200, 10, text, strlen(text));

	wsprintf(text, "MousePosY : %d", mousePosY);
	TextOut(hBackBufferDC, 200, 40, text, strlen(text));

	backGround->Render(hBackBufferDC);

	terry->Render(hBackBufferDC);

	player1_Hp->Render(hBackBufferDC);
	player2_Hp->Render(hBackBufferDC);

	Game_Timer->RenderTimer(hBackBufferDC);

	backBuffer->Render(hdc);

}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	SAFE_RELEASE(backGround);

	SAFE_RELEASE(player1_Hp);
	SAFE_RELEASE(player2_Hp);

	SAFE_RELEASE(Game_Timer);

	SAFE_RELEASE(terry);

	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
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
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
