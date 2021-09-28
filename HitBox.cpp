#include "HitBox.h"
#include "Image.h"
#include "Character.h"
#include "HitMotionFrame.h"

void HitBox::Init()
{
	HitImg = new Image[HitMotion::HitEnd];
	
	isAlive = false;
	pos.x = pos.y = 0;

	/*HitImg[HitMotion::Small].Init("Image/hit.bmp", 327, 102, 5, 1, true, RGB(7, 79, 151));
	HitImg[HitMotion::Big].Init("Image/hit.bmp", 327, 102, 5, 1, true, RGB(7, 79, 151));
	HitImg[HitMotion::HitGuard].Init("Image/Terry_guard.bmp", 342, 76, 6, 1, true, RGB(143, 123, 165));


	

	maxFrameX[HitMotion::Small] = 5;
	maxFrameX[HitMotion::Big] = 5;
	maxFrameX[HitMotion::HitGuard] = 6;


	actionFrameX[HitMotion::Small] = HitSmall;
	actionFrameX[HitMotion::Big] = Hitbig;
	actionFrameX[HitMotion::HitGuard] = GuardHit;*/

	HitImg[HitMotion::Small].Init("Image/sHit.bmp", 504, 86, 8, 1, true, RGB(240, 0, 240));
	HitImg[HitMotion::Big].Init("Image/bHit.bmp", 487, 88, 8, 1, true, RGB(240, 0, 240));
	HitImg[HitMotion::HitGuard].Init("Image/Guard.bmp", 217, 76, 7, 1, true, RGB(240, 0, 240));

	maxFrameX[HitMotion::Small] = 8;
	maxFrameX[HitMotion::Big] = 8;
	maxFrameX[HitMotion::HitGuard] = 7;

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
	if (isFire)
	{
		isAlive = true;
		frameX = 0;
		isHit = false;
		isFire = false;
	}
	if (isAlive)
	{
		SetBodySize();
		CheckCollision();
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
	if (!isAlive && !isHit) return;
	
	/*if (isAlive)
	{
		Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}*/
	if (isHit)
	{
		HitImg[hitMotion].Render(hdc, pos.x, pos.y, frameX, frameY, actionFrameX[hitMotion]);
	}

}	 
	 
void HitBox::Release()
{
	delete HitImg;
	HitImg = nullptr;
}

void HitBox::CheckCollision()
{
	if (!target) return;

	targetPos = target->GetPos();

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

