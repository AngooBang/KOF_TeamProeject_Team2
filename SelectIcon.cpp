#include "SelectIcon.h"
#include "KeyManager.h"
#include "Image.h"

void SelectIcon::Init()
{
	icon1 = new Image();
	icon2 = new Image();

	icon1->Init("Image/SelectCharacterImage/Icon.bmp", 159 * 5, 49 * 5, 4, 1, true, RGB(240, 0, 240));
	icon2->Init("Image/SelectCharacterImage/Icon.bmp", 159 * 5, 49 * 5, 4, 1, true, RGB(240, 0, 240));

	frameXDataInput[0] = 0;
	frameXDataInput[1] = 40 * 5;
	frameXDataInput[2] = 80 * 5;
	frameXDataInput[3] = 120 * 5;
	frameXDataInput[4] = 159 * 5;

	iconPosX[0] = 365;
	iconPosX[1] = (365 + 160 * 3);

	switch (playerNum)
	{
	case 1:
		frameX = 0;
		break;
	case 2:
		frameX = 2;
		break;
	}
	frameY = 0;
	pos.y = 585;
	isSelect = false;

	elapsedCount = 0;
	frameXData = frameXDataInput;



}

void SelectIcon::Update()
{
	if (isSelect) return;

	elapsedCount++;
	if (elapsedCount == 5)
	{
		switch (playerNum)
		{
		case 1:
			frameX == 0 ? frameX = 1 : frameX = 0;
			break;
		case 2:
			frameX == 2 ? frameX = 3 : frameX = 2;
			break;
		}

		elapsedCount = 0;
	}

	/*if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
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
		}*/

	/*switch (playerNum)
	{
	case 1:*/
		if (KeyManager().GetSingleton()->IsOnceKeyDown(VK_LEFT))
		{
			iconPosX[0] -= 160;
			if (iconPosX[0] == iconPosX[1]) { iconPosX[0] -= 160; }

			if (iconPosX[0] < 365)
			{
				iconPosX[0] = 365 + (160 * 3);
				if (iconPosX[0] == iconPosX[1]) { iconPosX[0] -= 160; }
			}

			
		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown(VK_RIGHT))
		{
			iconPosX[0] += 160;
			if (iconPosX[0] == iconPosX[1]) { iconPosX[0] += 160; }

			if (iconPosX[0] > 365 + (160 * 3))
			{
				iconPosX[0] = 365;
				if (iconPosX[0] == iconPosX[1]) { iconPosX[0] += 160; }
			}
		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown('A'))
		{
			frameX = 1;
			isSelect = true;
		}
	//	break;
	//case 2:
		if (KeyManager().GetSingleton()->IsOnceKeyDown('J'))
		{
			iconPosX[1] -= 160;

			if (iconPosX[1] == iconPosX[0]) { iconPosX[1] -= 160; }

			if (iconPosX[1] < 365)
			{
				iconPosX[1] = 365 + (160 * 3);
				if (iconPosX[1] == iconPosX[0]) { iconPosX[1] -= 160; }
			}

		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown('L'))
		{
			iconPosX[1] += 160;

			if (iconPosX[0] == iconPosX[1]) { iconPosX[1] += 160; }

			if (iconPosX[1] > 365 + (160 * 3))
			{
				iconPosX[1] = 365;
				if (iconPosX[0] == iconPosX[1]) { iconPosX[1] += 160; }
			}
		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown('D'))
		{
			frameX = 3;
			isSelect = true;
		}
		//break;
	//}

	//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
	//{
	//	selectCharPos[0].x += 160;
	//	if (selectCharPos[0].x + 10 == selectCharPos[1].x) { selectCharPos[0].x += 160; }
	//	if (selectCharPos[0].x > (370 + 160 * 3)) { selectCharPos[0].x = 370; }
	//	if (selectCharPos[0].x + 10 == selectCharPos[1].x) { selectCharPos[0].x += 160; }
	//}
	//else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
	//{
	//	selectCharPos[0].x -= 160;
	//	if (selectCharPos[0].x + 10 == selectCharPos[1].x) { selectCharPos[0].x -= 160; }
	//	if (selectCharPos[0].x < 370) { selectCharPos[0].x = (370 + 160 * 3); }
	//	if (selectCharPos[0].x + 10 == selectCharPos[1].x) { selectCharPos[0].x -= 160; }
	//}
}

void SelectIcon::Render(HDC hdc)
{
	//void Image::Render(HDC hdc, int destX, int destY, int frameX, int frameY, int* frameWidth)

	icon1->Render(hdc, iconPosX[0], pos.y, frameX, frameY, frameXData);
	icon2->Render(hdc, iconPosX[1], pos.y, frameX+2, frameY, frameXData);
}

void SelectIcon::Release()
{
	SAFE_RELEASE(icon1);
	SAFE_RELEASE(icon2);
}
