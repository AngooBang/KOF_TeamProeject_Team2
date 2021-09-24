#include "Ammo.h"
#include "Terry.h"
#include "Mary.h"
#include "Image.h"

void Ammo::Init()
{
	img = new Image[Action::END];

	isAlive = false;
	pos.x = pos.y = 0;

	img[Action::fMove].Init("Image/hit.bmp", 327, 102, 5, 1, true, RGB(7, 79, 151));

	walkFrameX[0] = 0;	walkFrameX[1] = 60, walkFrameX[2] = 120, walkFrameX[3] = 180,
		walkFrameX[4] = 250, walkFrameX[5] = 327;

	action = Action::fMove;

	bodySizeX = 15;
	bodySizeY = 15;

	shape.left = 0;
	shape.top = 0;
	shape.right = 0;
	shape.bottom = 0;

	frameX =  1;
	frameY = maxFrame = 0;
	terryFire = maryFire = false;
}

void Ammo::Update()
{
	if (isStatus)
	{
		frameX++;
		if (frameX == maxFrame)
		{
			isStatus = false;
			frameX = 1;
		}
	}

	/*if (!isAlive)
	{
		frameX = 1;
		return;
	}*/

	if (isAlive)
	{
		shape.left = pos.x - (bodySizeX / 2.0f);
		shape.top = pos.y - (bodySizeX / 2.0f);
		shape.right = pos.x + (bodySizeY / 2.0f);
		shape.bottom = pos.y + (bodySizeY / 2.0f);


		if (terryFire)
		{
			if (CheckCollision())
			{
				isAlive = false;
				terryFire = false;
				maryTarget->SetHit(true);

				isStatus = true;
				frameX = 0;
				maxFrame = 5;
			}
			else if (frameX < maxFrame)
			{
				frameX++;
				pos.x += moveSpeed;
			}
			else
			{
				isAlive = false;
				terryFire = false;
			}
			
			if (maryFire)
			{
				if (CheckCollision())
				{
					isAlive = false;
					maryFire = false;
					terryTarget->SetHit(true);
				}
				if (frameX < maxFrame)
				{
					frameX++;
					pos.x -= moveSpeed;
				}
				if (frameX == maxFrame)
				{
					isAlive = false;
					terryFire = false;
				}
			}
		}
	}
	
	
}
	 
void Ammo::Render(HDC hdc)
{	
	//if (!isAlive) return;
	
	if (isAlive)
	{
		Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
	if (isStatus)
	{
		img[action].Render(hdc, pos.x, pos.y, frameX, frameY, walkFrameX);
	}
}	 
	 
void Ammo::Release()
{

}

bool Ammo::CheckCollision()
{
	if (!terryFire && !maryFire) return false;
	
	POINTFLOAT targetPos;
	int targetBodySizeX, targetBodySizeY;

	if (terryFire)
	{
		targetPos = maryTarget->GetPos();
		targetBodySizeX = maryTarget->GetBodySizeX();
		//targetBodySizeY = maryTarget->GetBodySizeY();
		if (shape.right >= targetPos.x - (targetBodySizeX / 2))
		{
			return true;
		}
	}
	if (maryFire)
	{
		targetPos = terryTarget->GetPos();
		targetBodySizeX = terryTarget->GetBodySizeX();
		//targetBodySizeY = terryTarget->GetBodySizeY();
		if (shape.left <= targetPos.x + (targetBodySizeX / 2))
		{
			return true;
		}
	}

	return false;
}
