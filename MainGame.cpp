#include "MainGame.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "Terry.h"


void MainGame::Init()
{
	//KeyManager keyMgr;
	KeyManager::GetSingleton()->Init();
	SceneManager::GetSingleton();

	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 30, NULL);

	// 백버퍼
	backBuffer = new Image;
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);

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

	backBuffer->Render(hdc);

}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	SAFE_RELEASE(backGround);

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
