#include "SelectCharater.h"

void SelectCharater::Init()
{
	SelectPlayer1 = new Image;
	SelectIconP = new Image;
	SelectCharframe = new Image;

	SelectPlayer2 = new Image;

	SelectPlayer1->Init("Image/SelectCharacterImage/123688.bmp", 1192, 860, true, RGB(89, 177, 77));
	SelectIconP->Init("Image/SelectCharImage.bmp", 248*4.9, 52*4.9,6,1, true, RGB(240, 0, 240));
	SelectCharframe->Init("Image/SelectCharacterImage/SelectCharFrame.bmp", 149, 172);

	selectCharFrameX = 1;
	selectCharFrameY = 0;

	SelectCharPos[0].x = 200;
	SelectCharPos[0].y = 380;

	SelectCharPos[1].x = 200 + 149 * 3;
	SelectCharPos[1].y = 380;
}

void SelectCharater::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
	{
		SelectCharPos[0].x += 149;
		if (SelectCharPos[0].x > (200 + 149 * 3)) { SelectCharPos[0].x = 200; }
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
	{
		SelectCharPos[0].x -= 149;
		if (SelectCharPos[0].x < 200) { SelectCharPos[0].x = (200 + 149 * 3); }
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('l'))
	{
		SelectCharPos[1].x = (200 + 149 * 3) + 149;
		if (SelectCharPos[1].x > (200 + 149 * 3)) { SelectCharPos[1].x = 200; }
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('j'))
	{
		SelectCharPos[1].x = (200 + 149 * 3) - 149;
		if (SelectCharPos[1].x < 200) { SelectCharPos[1].x = (200 + 149 * 3); }
	}
}

void SelectCharater::Render(HDC hdc)
{
	SelectCharframe->Render(hdc, SelectCharPos[0].x-10, SelectCharPos[0].y+20);
	SelectPlayer1->SelectCharRender(hdc, 710, 750, 5, 3);
	SelectIconP->Render(hdc, SelectCharPos[0].x, SelectCharPos[0].y, selectCharFrameX, selectCharFrameY);

	/*selectcharframe->Render(hdc, (pos[0].x)+160, pos[0].y + 20);

	selectcharframe->Render(hdc, (pos[0].x) + 160*2, pos[1].y + 20);

	selectcharframe->Render(hdc, pos[1].x - 10, pos[1].y + 20);*/
	//selectPlayer2->SelectCharRender(hdc, , , 8, 3);
	//selectIconP->Render(hdc, pos[1].x, pos[1].y, frameX+2, frameY);
}

void SelectCharater::Release()
{
	delete SelectPlayer1;
	delete SelectIconP;
	delete SelectCharframe;
	delete SelectPlayer2;
}
