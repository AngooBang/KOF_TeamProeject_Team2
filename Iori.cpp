#include "Iori.h"
#include "Image.h"
#include "KeyManager.h"

void Iori::Init()
{
	img = new Image;
	isAlive = true;
	
	//img->Init("Image/Iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255), true);

	img->Init("Image/qwerMove.bmp", 589, 99, 11, 1, true, RGB(240, 0, 240));
	
	
	frameX = frameY = 0;
	elapsedCount = 0;
	
	pos.x = WIN_SIZE_X/2;
	pos.y = WIN_SIZE_Y/2;
	moveSpeed = 0;

	
}

void Iori::Update()
{
	// 앞으로 움직이기
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		elapsedCount++;
		if (elapsedCount >= 10)
		{
			frameX++;
			pos.x += moveSpeed;
			if (frameX >= 9)
			{
				frameX = 0;
			}
			elapsedCount = 0;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		elapsedCount++;
		if (elapsedCount >= 10)
		{
			frameX--;
			pos.x-= moveSpeed;
			if (frameX < 0)
			{
				frameX = 8;
			}
			elapsedCount = 0;
		}
	}
	
}

void Iori::Render(HDC hdc)
{
	if (img)
	{
		img->Render(hdc, pos.x, pos.y, frameX, frameY);
	}
}

void Iori::Release()
{
	if (img)
	{
		delete img;
		img = nullptr;
	}
}

