#include "HitBox.h"
#include "Image.h"
#include "Character.h"
#include "HitMotionFrame.h"

void HitBox::Init()
{
	HitImg = new Image[HitMotion::HitEnd];
	
	isAlive = false;
	pos.x = pos.y = 0;

	HitImg[HitMotion::Small].Init("Image/hit.bmp", 327, 102, 5, 1, true, RGB(7, 79, 151));
	HitImg[HitMotion::Big].Init("Image/hit.bmp", 327, 102, 5, 1, true, RGB(7, 79, 151));
	HitImg[HitMotion::HitGuard].Init("Image/Terry_guard.bmp", 342, 76, 6, 1, true, RGB(143, 123, 165));

	

	maxFrameX[HitMotion::Small] = 5;
	maxFrameX[HitMotion::Big] = 5;
	maxFrameX[HitMotion::HitGuard] = 6;


	actionFrameX[HitMotion::Small] = HitSmall;
	actionFrameX[HitMotion::Big] = Hitbig;
	actionFrameX[HitMotion::HitGuard] = GuardHit;

	hitMotion = HitMotion::Small;

	bodySizeX = 30;

	 
	maxFrame = frameX = 0;
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
		CheckCollision();
		maxFrame;
		/*targetPos = target->GetPos();

		if (frameX <= maxFrame)
		{
			pos.x += moveSpeed;
			frameX++;
			SetBodySize();
		}
		else
		{
			isAlive = false;
			frameX = 0;
		}*/
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
		/*if (target.GetAction() == Action::bMove)
		{
			asdfasdfasdf
		}*/
		HitImg[hitMotion].Render(hdc, pos.x-20, pos.y, frameX, frameY, actionFrameX[hitMotion]);
	}
	/*if (guard)
	{
		guardImg(renadfmakflsf; lasadk;lsakfdlka)
	}*/
}	 
	 
void HitBox::Release()
{
	delete HitImg;
	HitImg = nullptr;
}

void HitBox::CheckCollision()
{
	if (!target) return;

	//if (object1.left < object2.right &&
	//	object1.top < object2.bottom &&
	//	object1.right > object2.left &&
	//	object1.bottom > object2.top)
	targetPos = target->GetPos();
	hitMotion;
	if (shape.left < targetPos.x + (target->GetBodySizeX() / 2) && shape.top < targetPos.y + (target->GetBodySizeY() / 2)
		&& shape.right > targetPos.x - (target->GetBodySizeX() / 2) && shape.bottom > targetPos.y - (target->GetBodySizeY() / 2))	// 충돌 조건
	{
		isAlive = false;

		if (target->GetAction() == Action::bMove)
		{
			isHit = true;
			hitMotion = HitMotion::HitGuard;
			target->SetIsHit(true);
			target->SetHitMotion(hitMotion);
		}
		else
		{
			isHit = true;
			target->SetIsHit(true);
			target->SetHitMotion(hitMotion);
		}
		frameX = 0;
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
		shape.top = pos.y - (bodySizeX / 2);
		shape.bottom = pos.y + (bodySizeX / 2);
	}
}


void HitBox::NextFrame()
{
	frameX++;
	if (frameX >= maxFrameX[hitMotion])
	{
		isHit = false;
		frameX = 0;
	}
}

