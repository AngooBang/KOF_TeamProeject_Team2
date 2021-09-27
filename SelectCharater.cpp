#include "selectCharater.h"
#include "Image.h"
#include "SelectIcon.h"


void SelectCharater::Init()
{
	selectBackground = new Image;
	selectChar1 = new Image;
	selectChar2 = new Image;
	selectCharframe = new Image;

	selectBackground->Init("Image/SelectCharacterImage/SelectCharBackground.bmp", 1200, 800, true, RGB(89, 177, 77));
	selectChar1->Init("Image/SelectCharacterImage/MarryProfile.bmp", 150, 171, true, RGB(89, 177, 77));
	selectChar2->Init("Image/SelectCharacterImage/TerryProfile.bmp", 158, 171, true, RGB(89, 177, 77));
	selectCharframe->Init("Image/SelectCharacterImage/SelectCharFrame.bmp", 149, 172);

	icon = new SelectIcon();
	/*iconP1 = new SelectIcon();
	iconP2 = new SelectIcon();*/

	icon->SetPlayerNum(1);
	//iconP1->SetPlayerNum(1);
	//iconP2->SetPlayerNum(2);

	icon->Init();
	/*iconP1->Init();
	iconP2->Init();*/


	//selectCharFrameNum1 = 0;
	//selectCharFrameNum2 = 0;
	//selectCharFrameX1 = 1;
	//selectCharFrameX2 = 3;
	//selectCharPos[0].x = 370;
	//selectCharPos[0].y = 580;
	//selectCharPos[1].x = 380 + 160 * 3; 
	//selectCharPos[1].y = 580;
	//selectCharFramePos = 360;
	
	elapsedtCount = 0;
}

void SelectCharater::Update()
{
	/*iconP1->Update();
	iconP2->Update();*/
	icon->Update();



/*
	if (moveIcon1 == true)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
		{
			selectCharPos[0].x += 160;
			if (selectCharPos[0].x+10 == selectCharPos[1].x) { selectCharPos[0].x += 160; }
			if (selectCharPos[0].x > (370 + 160 * 3)) { selectCharPos[0].x = 370; }
			if (selectCharPos[0].x + 10 == selectCharPos[1].x) { selectCharPos[0].x += 160; }
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
		{
			selectCharPos[0].x -= 160;
			if (selectCharPos[0].x+10 == selectCharPos[1].x) { selectCharPos[0].x -= 160; }
			if (selectCharPos[0].x < 370) { selectCharPos[0].x = (370 + 160 * 3); }
			if (selectCharPos[0].x + 10 == selectCharPos[1].x) { selectCharPos[0].x -= 160; }
		}
	}

	if (moveIcon2 == true)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('L'))
		{
			selectCharPos[1].x += 160;
			if (selectCharPos[0].x + 10 == selectCharPos[1].x) { selectCharPos[1].x += 160; }
			if (selectCharPos[1].x > (380 + 160 * 3)) { selectCharPos[1].x = 380; }
			if (selectCharPos[0].x + 10 == selectCharPos[1].x) { selectCharPos[1].x += 160; }
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
		{
			selectCharPos[1].x -= 160;
			if (selectCharPos[1].x == selectCharPos[0].x + 10) { selectCharPos[1].x -= 160; }
			if (selectCharPos[1].x < 380) { selectCharPos[1].x = (380 + 160 * 3); }
			if (selectCharPos[1].x == selectCharPos[0].x + 10) { selectCharPos[1].x -= 160; }
		}
	}*/

	//if (moveIcon1 == false && moveIcon2 == false)
	//{
	//	if (370 < selectCharPos[0].x&& selectCharPos[0].x < (370+160)) { /*1P = Mary로 넘어가기*/ }
	//	if (380 < selectCharPos[1].x && selectCharPos[1].x < (380 + 160)) { /*2P = Mary로 넘어가기*/ }

	//	if ((370 + 160 * 2) < selectCharPos[0].x && selectCharPos[0].x < (370 + 160 * 3)) { /*1P = Terry로 넘어가기*/ }
	//	if ((380 + 160 * 2) < selectCharPos[1].x && selectCharPos[0].x < (380 + 160 * 3)) { /*2P = Terry로 넘어가기*/ }
	//}
}

void SelectCharater::Render(HDC hdc)
{
	selectBackground->Render(hdc);
	for (int i = 0; i < 4; i++)
	{
		selectCharframe->Render(hdc, 360 +( i * 160), 600);
	}

	selectChar1->Render(hdc, 365, 600);
	selectChar2->Render(hdc, (365+160*3), 600);

	/*iconP1->Render(hdc);
	iconP2->Render(hdc);*/
	icon->Render(hdc);
}

void SelectCharater::Release()
{
	/*SAFE_RELEASE(iconP1);
	SAFE_RELEASE(iconP2);*/
	SAFE_RELEASE(icon)
	SAFE_RELEASE(selectChar1);
	SAFE_RELEASE(selectChar2);
	SAFE_RELEASE(selectCharframe);
	SAFE_RELEASE(selectBackground);
}
