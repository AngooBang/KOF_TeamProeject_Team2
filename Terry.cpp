#include "Terry.h"
#include "Image.h"
#include "KeyManager.h"

void Terry::Init()
{
	img = new Image;
	isAlive = false;

	img->Init("Image/Terry_walk.bmp", 420, 127, 6, 1, true, RGB(143, 123, 165));

	walkFrameX[0] = 0;	walkFrameX[1] = 80, walkFrameX[2] = 150, walkFrameX[3] = 220, 
		walkFrameX[4] = 285, walkFrameX[5] = 345, walkFrameX[6] = 420;

	frameX = frameY = 0;
	elapsedCount = 0;

	pos.x = WIN_SIZE_X / 2;
	pos.y = WIN_SIZE_Y / 2;
	moveSpeed = 0;
}

void Terry::Update()
{
	if (isAlive)
	{
		frameX++;
		walkFrameX[0] = 0;	walkFrameX[1] = 75, walkFrameX[2] = 140, walkFrameX[3] = 260,
			walkFrameX[4] = 375, walkFrameX[5] = 490, walkFrameX[6] = 590, walkFrameX[7] = 650, walkFrameX[8] = 745;
		img->Init("Image/Terry_kick.bmp", 745, 114, 8, 1, true, RGB(143, 123, 165));
		if (frameX == 8)
		{
			frameX = 0;
			isAlive = false;
		}
	}
	// 앞으로 움직이기
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		elapsedCount++;
		if (elapsedCount >= 2)
		{
			frameX++;
			pos.x += moveSpeed;
			if (frameX >= 5)
			{
				frameX = 0;
			}
			elapsedCount = 0;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		elapsedCount++;
		if (elapsedCount >= 2)
		{
			frameX--;
			pos.x -= moveSpeed;
			if (frameX < 0)
			{
				frameX = 5;
			}
			elapsedCount = 0;
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))
	{
		frameX = 0;
		isAlive = true;
	}
}

void Terry::Render(HDC hdc)
{
	if (img)
	{
		img->Render(hdc, pos.x, pos.y, frameX, frameY, walkFrameX);
	}
}

void Terry::Release()
{
	if (img)
	{
		delete img;
		img = nullptr;
	}
}
