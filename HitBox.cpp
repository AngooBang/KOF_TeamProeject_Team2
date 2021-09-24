#include "HitBox.h"
#include "Image.h"
#include "Character.h"

void HitBox::Init()
{
	img = new Image;

	isAlive = false;
	pos.x = pos.y = 0;

	img->Init("Image/hit.bmp", 327, 102, 5, 1, true, RGB(7, 79, 151));

	actionFrameX[0] = 0;	actionFrameX[1] = 60, actionFrameX[2] = 120, actionFrameX[3] = 180,
		actionFrameX[4] = 250, actionFrameX[5] = 327;

	targetPos = target->GetPos();

	bodySizeX = 15;
	bodySizeY = 15;

	shape.left = 0;
	shape.top = 0;
	shape.right = 0;
	shape.bottom = 0;

	frameX =  0;
	frameY = maxFrame = 0;
}

void HitBox::Update()
{
	if (isHit)
	{
		NextFrame();
	}

	if (isAlive)
	{
		SetBodySize();
	}
	
	
}
	 
void HitBox::Render(HDC hdc)
{	
	//if (!isAlive) return;
	
	if (isAlive)
	{
		Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
	if (isHit)
	{
		img->Render(hdc, pos.x-20, pos.y, frameX, frameY, actionFrameX);
	}
}	 
	 
void HitBox::Release()
{
	delete img;
	img = nullptr;
}

void HitBox::CheckCollision()
{
	if (!target) return;

	//if (object1.left < object2.right &&
	//	object1.top < object2.bottom &&
	//	object1.right > object2.left &&
	//	object1.bottom > object2.top)

	if (shape.left < targetPos.x + (target->GetBodySizeX() / 2) && shape.top < targetPos.y + (target->GetBodySizeY() / 2)
		&& shape.right > targetPos.x - (target->GetBodySizeX() / 2) && shape.bottom > targetPos.y - (target->GetBodySizeY() / 2))	// 충돌 조건
	{
		isAlive = false;
		isHit = true;
		frameX = 0;
		maxFrame = 5;
		return ;
	}
	switch (target->GetPlayerNum())
	{
	case 1:
		if (frameX < maxFrame)
		{
			frameX++;
			pos.x -= moveSpeed;
		}
		else
		{
			isAlive = false;
			frameX = 0;
		}
		break;
	case 2:
		if (frameX < maxFrame)
		{
			frameX++;
			pos.x += moveSpeed;
		}
		else
		{
			isAlive = false;
			frameX = 0;
		}
		break;
	}
}

void HitBox::SetBodySize()
{
	for (int i = 0; i < maxFrame; i++)
	{
		shape.left = pos.x - (bodySizeX / 2);
		shape.right = pos.x + (bodySizeX / 2);
		shape.top = pos.y - (bodySizeY / 2);
		shape.bottom = pos.y + (bodySizeY / 2);
	}
}


void HitBox::NextFrame()
{
	frameX++;
	if (frameX >= maxFrame)
	{
		isHit = false;
		frameX = 0;
	}
}

