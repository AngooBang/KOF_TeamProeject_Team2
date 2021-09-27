#include "SelectIcon.h"
#include "KeyManager.h"
#include "Image.h"

void SelectIcon::Init()
{
	icon = new Image();

	icon->Init("Image/SelectCharacterImage/Icon.bmp", 159 * 5, 49 * 5, 4, 1, true, RGB(240, 0, 240));
	frameXDataInput[0] = 0;
	frameXDataInput[1] = 40 * 5;
	frameXDataInput[2] = 80 * 5;
	frameXDataInput[3] = 120 * 5;
	frameXDataInput[4] = 159 * 5;


	switch (playerNum)
	{
	case 1:
		frameX = 0;
		pos.x = 365;
		break;
	case 2:
		pos.x = 365 + (160 * 3);
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


	switch (playerNum)
	{
	case 1:
		if (KeyManager().GetSingleton()->IsOnceKeyDown(VK_LEFT))
		{
			pos.x -= 160;
		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown(VK_RIGHT))
		{
			pos.x += 160;
		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown('A'))
		{
			frameX = 1;
			isSelect = true;
		}
		break;
	case 2:
		if (KeyManager().GetSingleton()->IsOnceKeyDown('J'))
		{
			pos.x -= 160;
		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown('L'))
		{
			pos.x += 160;
		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown('D'))
		{
			frameX = 3;
			isSelect = true;
		}
		break;
	}

}

void SelectIcon::Render(HDC hdc)
{
	icon->Render(hdc, pos.x, pos.y, frameX, frameY, frameXData);
}

void SelectIcon::Release()
{
	SAFE_RELEASE(icon);
}
