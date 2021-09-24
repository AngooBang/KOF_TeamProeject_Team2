#include "Map.h"
#include "Image.h"

void Map::Init()
{
	TownStage = new Image;
	TownStage->Init("Image/Map/Town_Stage.bmp", WIN_SIZE_X * 1.5, (WIN_SIZE_Y * 8), 1, 8, true, RGB(255, 0, 255));

	mapFrameX, mapFrameY = 0;

	elapsedCount = 0;
}

void Map::Update()
{
	elapsedCount++;
	if (elapsedCount == 5)
	{
		mapFrameY++;
		if (mapFrameY == 7)
		{
			mapFrameY = 0;
		}
		elapsedCount = 0;
	}

}

void Map::Render(HDC hdc)
{
	if (TownStage)
	{
		TownStage->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 0, mapFrameY);
	}
}

void Map::Release()
{
	if (TownStage)
	{
		delete TownStage;
		TownStage = nullptr;
	}
}
