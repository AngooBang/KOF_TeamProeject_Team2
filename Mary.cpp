#include "Mary.h"
#include "Image.h"
#include "KeyManager.h"

void Mary::Init()
{
	img = new Image[Action::END];
	isAlive = true;
	istest = isMoveLeft = isMoveRight = isStatus = isHit = false;
	maxFrame = 7;
	hp = 100;

	img[Action::Basic].Init("Image/Mary/Mary_Basic.bmp", 771, 120, 12, 1, true, RGB(0, 102, 0));
	img[Action::fMove].Init("Image/Mary/Mary_Forward.bmp", 501, 155, 8, 1, true, RGB(0, 102, 0));
	img[Action::bMove].Init("Image/Mary/Mary_BackWard.bmp", 430, 125, 7, 1, true, RGB(0, 102, 0));
	img[Action::sHand].Init("Image/Mary/Mary_sAttack.bmp", 228, 125, 3, 1, true, RGB(0, 102, 0));
	img[Action::bHand].Init("Image/Mary/Mary_bAttack.bmp", 379, 129, 5, 1, true, RGB(0, 102, 0));
	img[Action::sKick].Init("Image/Mary/Mary_sKick.bmp", 441, 133, 6, 1, true, RGB(0, 102, 0));
	img[Action::bKick].Init("Image/Mary/Mary_bKick.bmp", 786, 123, 10, 1, true, RGB(0, 102, 0));
	img[Action::sHit].Init("Image/Mary/Mary_Hit.bmp", 432, 125, 5, 1, true, RGB(0, 102, 0));
	img[Action::bHit].Init("Image/Mary/Mary_bHit.bmp", 409, 125, 5, 1, true, RGB(0, 102, 0));

	img[Action::Basic].ReverseImg();
	img[Action::fMove].ReverseImg();
	img[Action::bMove].ReverseImg();
	img[Action::sHand].ReverseImg();
	img[Action::bHand].ReverseImg();
	img[Action::sKick].ReverseImg();
	img[Action::bKick].ReverseImg();
	img[Action::sHit].ReverseImg();
	img[Action::bHit].ReverseImg();

	frameX = frameY = 0;

	KeyEvent(0);

	elapsedCount = 0;

	pos.x = 400;
	pos.y = WIN_SIZE_Y / 2;
	moveSpeed = 10;

	bodySizeY = 120;
	for (int i = 0; i < maxFrame; i++)
	{
		bodySizeX = actionFrameX[i + 1] - actionFrameX[i];
		shape.left = pos.x - (bodySizeX / 2);
		shape.right = pos.x + (bodySizeX / 2);
		shape.top = pos.y - (bodySizeY / 2);
		shape.bottom = pos.y + (bodySizeY / 2);
	}

	ammo = new Ammo;
	ammo->Init();

}



void Mary::Update()
{

	//ProcessInputKey();
	//if (inputKey)
	//{
	//	KeyEvent(inputKey);
	//	inputKey = 0;
	//	isMove = false;
	//	
	//}
	/*if (isHit)
	{
		isHit = false;
		KeyEvent('Z');
		isStatus = true;
	}*/
	if (isHit)
	{
		KeyEvent('C');
	}

	if (!isStatus)
	{
		ProcessInputKey();
	}
	if (isMove)
	{
		MoveToFrame();
	}
	else
	{
		NextFrame(true);
	}

	/*if(!isStatus)
	ProcessInputKey();

	if (inputKey)
	{
		KeyEvent(inputKey);
		inputKey = 0;
	}
	else
		KeyEvent(0);

	MoveToFrame();

	if(isStatus || !isMove)
		NextFrame(true);*/



	SetBodySize();

	ammo->Update();
}

void Mary::Render(HDC hdc)
{
	//Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);

	if (img)
	{
		img[action].Render2P(hdc, pos.x, pos.y, frameX, frameY, actionFrameX);
	}


	ammo->Render(hdc);
}

void Mary::Release()
{
	if (img)
	{
		delete img;
		img = nullptr;
	}
	ammo->Release();
}

void Mary::KeyEvent(char inputKey)
{
	switch (inputKey)
	{
	case 'J':		//앞으로
		if (!isMove)
		{
			action = Action::fMove;
			maxFrame = 8;
			actionFrameX[0] = 0;	actionFrameX[1] = 59, actionFrameX[2] = 115, actionFrameX[3] = 180,
				actionFrameX[4] = 248, actionFrameX[5] = 315, actionFrameX[6] = 381, actionFrameX[7] = 441, actionFrameX[maxFrame] = 501;
			frameX = 0;
			isMove = true;
		}
		break;
	case 'L':		//뒤로
		if (!isMove)
		{
			action = Action::bMove;
			maxFrame = 7;
			actionFrameX[0] = 0;	actionFrameX[1] = 66, actionFrameX[2] = 130, actionFrameX[3] = 195,
				actionFrameX[4] = 255, actionFrameX[5] = 314, actionFrameX[6] = 373, actionFrameX[maxFrame] = 430;
			frameX = 0;
			isMove = true;
		}
		break;
	case 'D':		//강발
		action = Action::bKick;
		maxFrame = 10;
		actionFrameX[0] = 0;	actionFrameX[1] = 65, actionFrameX[2] = 133, actionFrameX[3] = 205,
			actionFrameX[4] = 285, actionFrameX[5] = 395, actionFrameX[6] = 505, actionFrameX[7] = 583,
			actionFrameX[8] = 655, actionFrameX[9] = 722, actionFrameX[maxFrame] = 786;
		frameX = 0;
		isMove = false;
		isStatus = true;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(10);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(4);
		break;
	case 'F':		//약발
		action = Action::sKick;
		maxFrame = 6;
		actionFrameX[0] = 0;	actionFrameX[1] = 87, actionFrameX[2] = 160, actionFrameX[3] = 235,
			actionFrameX[4] = 305, actionFrameX[5] = 373, actionFrameX[maxFrame] = 441;
		frameX = 0;
		isMove = false;
		isStatus = true;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(10);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 'E':		//강손
		action = Action::bHand;
		maxFrame = 5;
		actionFrameX[0] = 0;	actionFrameX[1] = 81, actionFrameX[2] = 154, actionFrameX[3] = 242,
			actionFrameX[4] = 315, actionFrameX[maxFrame] = 379;
		frameX = 0;
		isMove = false;
		isStatus = true;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(15);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 'R':		//약손
		action = Action::sHand;
		maxFrame = 3;
		actionFrameX[0] = 0;	actionFrameX[1] = 85, actionFrameX[2] = 155, actionFrameX[maxFrame] = 228;
		frameX = 0;
		isMove = false;
		isStatus = true;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(10);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(2);
		break;
		break;
	case 'C':		//1피격
		action = Action::sHit;
		maxFrame = 5;
		actionFrameX[0] = 0;	actionFrameX[1] = 85, actionFrameX[2] = 155,
			actionFrameX[3] = 243, actionFrameX[4] = 343, actionFrameX[maxFrame] = 432;
		frameX = 0;
		isHit = false;
		isMove = false;
		isStatus = true;
		break;
	case 'V':		//2피격
		action = Action::bHit;
		maxFrame = 5;
		actionFrameX[0] = 0;	actionFrameX[1] = 78, actionFrameX[2] = 154,
			actionFrameX[3] = 236, actionFrameX[4] = 323, actionFrameX[maxFrame] = 409;
		frameX = 0;
		isMove = false;
		isStatus = true;
		break;
	case 0:	//기본자세
		action = Action::Basic;
		maxFrame = 12;
		actionFrameX[0] = 0, actionFrameX[1] = 60, actionFrameX[2] = 122, actionFrameX[3] = 184,
			actionFrameX[4] = 246, actionFrameX[5] = 311,actionFrameX[6] = 375, actionFrameX[7] = 440,
			actionFrameX[8] = 506, actionFrameX[9] = 574,actionFrameX[10] = 642, actionFrameX[11] = 706, actionFrameX[maxFrame] = 771;
		frameX = 0;
		break;


	}
}


void Mary::SetBodySize()
{
	for (int i = 0; i < maxFrame; i++)
	{
		bodySizeX = actionFrameX[i + 1] - actionFrameX[i];
		shape.left = pos.x - (bodySizeX / 2);
		shape.right = pos.x + (bodySizeX / 2);
		shape.top = pos.y - (bodySizeY / 2);
		shape.bottom = pos.y + (bodySizeY / 2);
	}
}

void Mary::MoveToFrame()
{
	switch (action)
	{
	case Action::fMove:
	{
		if (!KeyManager::GetSingleton()->IsStayKeyDown('J') || isStatus)
		{
			isMove = false;
			KeyEvent(0);
		}
		pos.x -= moveSpeed;
		NextFrame(true);
	}break;
	case Action::bMove:
	{
		if (!KeyManager::GetSingleton()->IsStayKeyDown('L') || isStatus)
		{
			isMove = false;
			KeyEvent(0);
		}
		pos.x += moveSpeed;
		NextFrame(false);
	}break;
	}
}

void Mary::ProcessInputKey()
{
	
	if (KeyManager::GetSingleton()->IsStayKeyDown('J'))
	{
		KeyEvent('J');
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown('L'))
	{
		KeyEvent('L');
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('D'))	//강발
	{
		KeyEvent('D');
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))	//약발
	{
		KeyEvent('F');
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('E'))	//강손
	{
		KeyEvent('E');
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))	//약손
	{
		KeyEvent('R');
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))	//1피격
	{
		KeyEvent('C');
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('V'))	//2피격
	{
		KeyEvent('V');
	}

	/*if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		inputKey = 0;
	}*/
}

void Mary::NextFrame(bool b)
{
	if (b)
	{
		frameX++;
		if (frameX >= maxFrame)
		{
			frameX = 0;
			isStatus = false;
			if (!isMove)
			{
				KeyEvent(0);
			}
		}
	}
	else
	{
		frameX--;
		if (frameX <= 0)
		{
			frameX = maxFrame - 1;
		}
	}
}

