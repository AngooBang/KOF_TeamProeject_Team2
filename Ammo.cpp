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

	actionFrameX[0] = 0;	actionFrameX[1] = 60, actionFrameX[2] = 120, actionFrameX[3] = 180,
		actionFrameX[4] = 250, actionFrameX[5] = 327;

	action = Action::fMove;

	bodySizeX = 15;
	bodySizeY = 15;

	shape.left = 0;
	shape.top = 0;
	shape.right = 0;
	shape.bottom = 0;

	frameX =  0;
	frameY = maxFrame = 0;
	terryFire = maryFire = false;
}

void Ammo::Update()
{
	if (isHit)
	{
		NextFrame();
	}

	if (isAlive)
	{
		SetBodySize();
		fireCheck();

		/*if (terryFire)
		{
			fireCheck();
			CheckCollision();
			if (frameX < maxFrame)
			{
				frameX++;
				pos.x += moveSpeed;
			}
			else
			{
				isAlive = false;
				terryFire = false;
				frameX = 0;
			}

		}

		if (maryFire)
		{
			fireCheck();
			CheckCollision();
			if (frameX < maxFrame)
			{
				frameX++;
				pos.x -= moveSpeed;
			}
			else
			{
				maryFire = false;
				terryFire = false;
				frameX = 0;
			}
		}*/
		
	}
	
	
}
	 
void Ammo::Render(HDC hdc)
{	
	//if (!isAlive) return;
	
	if (isAlive)
	{
		Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
	if (isHit)
	{
		img[action].Render(hdc, pos.x-20, pos.y, frameX, frameY, actionFrameX);
	}
}	 
	 
void Ammo::Release()
{

}

void Ammo::fireCheck()
{
	if (!terryFire && !maryFire) return;

	if (terryFire)
	{
		targetPos = maryTarget->GetPos();
		targetBodySizeX = maryTarget->GetBodySizeX();
	}

	if (maryFire)
	{
		targetPos = terryTarget->GetPos();
		targetBodySizeX = terryTarget->GetBodySizeX();
	}
	CheckCollision();
}

bool Ammo::CheckCollision()
{
	if (terryFire)
	{
		if (shape.right >= targetPos.x - (targetBodySizeX / 2))
		{
			isAlive = false;
			terryFire = false;
			maryTarget->SetHit(true);

			isHit = true;
			frameX = 0;
			maxFrame = 5;
			return true;
		}
		if (frameX < maxFrame)
		{
			frameX++;
			pos.x += moveSpeed;
		}
		else
		{
			isAlive = false;
			terryFire = false;
			frameX = 0;
		}
	}
	if (maryFire)
	{
		if (shape.left <= targetPos.x + (targetBodySizeX / 2))
		{
			isAlive = false;
			maryFire = false;
			terryTarget->SetHit(true);

			isHit = true;
			frameX = 0;
			maxFrame = 5;
			return true;
		}
		if (frameX < maxFrame)
		{
			frameX++;
			pos.x -= moveSpeed;
		}
		else
		{
			maryFire = false;
			terryFire = false;
			frameX = 0;
		}
	}
	return false;
}

void Ammo::SetBodySize()
{
	for (int i = 0; i < maxFrame; i++)
	{
		shape.left = pos.x - (bodySizeX / 2);
		shape.right = pos.x + (bodySizeX / 2);
		shape.top = pos.y - (bodySizeY / 2);
		shape.bottom = pos.y + (bodySizeY / 2);
	}
}


void Ammo::NextFrame()
{
	frameX++;
	if (frameX >= maxFrame)
	{
		isStatus = false;
		frameX = 0;
	}
}

