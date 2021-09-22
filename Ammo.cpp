#include "Ammo.h"
#include "Terry.h"
#include "Mary.h"

void Ammo::Init()
{
	isAlive = false;
	pos.x = pos.y = 0;

	bodySizeX = 15;
	bodySizeY = 15;

	shape.left = 0;
	shape.top = 0;
	shape.right = 0;
	shape.bottom = 0;

	frameX = 0;
	maxFrame = 0;

	terryFire = maryFire = false;
}

void Ammo::Update()
{
	if (!isAlive)
	{
		frameX = 0;
		return;
	}

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
			}
			if (frameX < maxFrame)
			{
				frameX++;
				pos.x += moveSpeed;
			}
			if (frameX == maxFrame)
			{
				isAlive = false;
				terryFire = false;
			}
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
	 
void Ammo::Render(HDC hdc)
{	
	if (!isAlive) return;
	
	if (isAlive)
	{
		Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
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
		targetBodySizeY = maryTarget->GetBodySizeY();
		if (shape.right >= targetPos.x - (targetBodySizeX / 2))
		{
			return true;
		}
	}
	else if (maryFire)
	{
		targetPos = terryTarget->GetPos();
		targetBodySizeX = terryTarget->GetBodySizeX();
		targetBodySizeY = terryTarget->GetBodySizeY();
		if (shape.left <= targetPos.x + (targetBodySizeX / 2))
		{
			return true;
		}
	}

	return false;
}
