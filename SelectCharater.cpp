#include "SelectCharater.h"

void SelectCharater::Init()
{
	SelectBackground = new Image;

	SelectChar = new Image;
	SelectIconP = new Image;

	SelectCharframe = new Image;

	SelectIconP2 = new Image;

	SelectBackground->Init("Image/SelectCharacterImage/SelectCharBackground.bmp", 1200, 800, true, RGB(89, 177, 77));

	SelectChar->Init("Image/SelectCharacterImage/123688.bmp", 1192, 860, true, RGB(89, 177, 77));
	SelectIconP->Init("Image/SelectCharImage.bmp", 248*5, 52*5,6,1, true, RGB(240, 0, 240));

	SelectCharframe->Init("Image/SelectCharacterImage/SelectCharFrame.bmp", 149, 172);

	SelectIconP2->Init("Image/SelectCharImage.bmp", 248 * 5, 52 * 5, 6, 1, true, RGB(240, 0, 240));

	selectCharFrameNum = 0;
	selectCharFrameX = 1;
	selectCharFrameX2 = 3;

	SelectCharPos[0].x = 370;
	SelectCharPos[0].y = 580;

	SelectCharPos[1].x = 380 + 160 * 3;
	SelectCharPos[1].y = 580;

	selectCharFramePos = 360;
	
	elapsedtCount = 0;
}

void SelectCharater::Update()
{
	elapsedtCount++;
	if (elapsedtCount > 4)
	{
		switch (selectCharFrameNum)
		{
		case 0:
			selectCharFrameX = 1;
			selectCharFrameX2 = 3;
			selectCharFrameNum = 1;
			break;

		case 1:
			selectCharFrameX = 0;
			selectCharFrameX2 = 2;
			selectCharFrameNum = 0;
			break;
		}
		elapsedtCount = 0;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q') ||
		KeyManager::GetSingleton()->IsOnceKeyDown('W') ||
		KeyManager::GetSingleton()->IsOnceKeyDown('A') ||
		KeyManager::GetSingleton()->IsOnceKeyDown('S'))
		{ selectCharFrameX = 1; }			//1P 캐릭터 선택시 아이콘 멈춤 수정 필요

	if (KeyManager::GetSingleton()->IsOnceKeyDown('E') ||
		KeyManager::GetSingleton()->IsOnceKeyDown('R') ||
		KeyManager::GetSingleton()->IsOnceKeyDown('D') ||
		KeyManager::GetSingleton()->IsOnceKeyDown('F'))
		{ selectCharFrameX2 = 3; }			//2P 캐릭터 선택시 아이콘 멈춤 수정 필요
		
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
	{
		SelectCharPos[0].x += 160;
		if (SelectCharPos[0].x+10 == SelectCharPos[1].x) { SelectCharPos[0].x += 160; }
		if (SelectCharPos[0].x > (370 + 160 * 3)) { SelectCharPos[0].x = 370; }
		if (SelectCharPos[0].x + 10 == SelectCharPos[1].x) { SelectCharPos[0].x += 160; }
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
	{
		SelectCharPos[0].x -= 160;
		if (SelectCharPos[0].x+10 == SelectCharPos[1].x) { SelectCharPos[0].x -= 160; }
		if (SelectCharPos[0].x < 370) { SelectCharPos[0].x = (370 + 160 * 3); }
		if (SelectCharPos[0].x + 10 == SelectCharPos[1].x) { SelectCharPos[0].x -= 160; }
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('L'))
	{
		SelectCharPos[1].x += 160;
		if (SelectCharPos[0].x + 10 == SelectCharPos[1].x) { SelectCharPos[1].x += 160; }
		if (SelectCharPos[1].x > (380 + 160 * 3)) { SelectCharPos[1].x = 380; }
		if (SelectCharPos[0].x + 10 == SelectCharPos[1].x) { SelectCharPos[1].x += 160; }
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
	{
		SelectCharPos[1].x -= 160;
		if (SelectCharPos[1].x == SelectCharPos[0].x + 10) { SelectCharPos[1].x -= 160; }
		if (SelectCharPos[1].x < 380) { SelectCharPos[1].x = (380 + 160 * 3); }
		if (SelectCharPos[1].x == SelectCharPos[0].x + 10) { SelectCharPos[1].x -= 160; }
	}

}

void SelectCharater::Render(HDC hdc)
{
	SelectBackground->Render(hdc);

	SelectCharframe->Render(hdc, selectCharFramePos, 600);

	SelectCharframe->Render(hdc, selectCharFramePos+160, 600);

	SelectCharframe->Render(hdc, selectCharFramePos+160*2, 600);

	SelectCharframe->Render(hdc, selectCharFramePos+160*3, 600);

	SelectChar->SelectCharRender(hdc, 880, 950, 5, 3);
	SelectIconP->Render(hdc, SelectCharPos[0].x, SelectCharPos[0].y, selectCharFrameX, 0);


	SelectChar->SelectCharRender(hdc, 890+160*3, 950, 8, 3);
	SelectIconP2->Render(hdc, SelectCharPos[1].x, SelectCharPos[1].y, selectCharFrameX2, 0);

}

void SelectCharater::Release()
{
	delete SelectChar;
	delete SelectIconP;
	delete SelectCharframe;
	delete SelectIconP2;
	delete SelectBackground;
}
