#include "Terry.h"
#include "Image.h"
#include "KeyManager.h"

void Terry::Init()
{
	img = new Image[Action::END];
	isAlive = true;
	istest = isMoveLeft = isMoveRight = isStatus = isHit = false;
	maxFrame = 7;
	hp = 100;

	img[Action::Basic].Init("Image/Terry/Terry_basic.bmp", 598, 120, 7, 1, true, RGB(143, 123, 165));
	img[Action::fMove].Init("Image/Terry/Terry_Forward.bmp", 423, 133, 6, 1, true, RGB(143, 123, 165));
	img[Action::bMove].Init("Image/Terry/Terry_Backward.bmp", 409, 130, 6, 1, true, RGB(143, 123, 165));
	img[Action::sHand].Init("Image/Terry/Terry_sAttack.bmp", 275, 114, 3, 1, true, RGB(143, 123, 165));
	img[Action::bHand].Init("Image/Terry/Terry_bAttack.bmp", 753, 116, 8, 1, true, RGB(143, 123, 165));
	img[Action::sKick].Init("Image/Terry/Terry_sKick.bmp", 444, 112, 5, 1, true, RGB(143, 123, 165));
	img[Action::bKick].Init("Image/Terry/Terry_kick.bmp", 745, 114, 8, 1, true, RGB(143, 123, 165));
	img[Action::sHit].Init("Image/Terry/Terry_Hit.bmp", 473, 115, 5, 1, true, RGB(143, 123, 165));
	img[Action::bHit].Init("Image/Terry/Terry_bHit.bmp", 440, 115, 5, 1, true, RGB(143, 123, 165));



	frameX = frameY = 0;

	KeyEvent(0);

	elapsedCount = 0;

	pos.x = 200;
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



void Terry::Update()
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

void Terry::Render(HDC hdc)
{
	//Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	if (img)
	{
		img[action].Render(hdc, pos.x, pos.y, frameX, frameY, actionFrameX);
	}
	ammo->Render(hdc);
}

void Terry::Release()
{
	if (img)
	{
		delete img;
		img = nullptr;
	}
	ammo->Release();
}

void Terry::KeyEvent(char inputKey)
{
	switch (inputKey)
	{
	case VK_RIGHT:		//앞으로
		if (!isMove)
		{
			action = Action::fMove;
			maxFrame = 6;
			actionFrameX[0] = 0;	actionFrameX[1] = 77, actionFrameX[2] = 151, actionFrameX[3] = 217,
				actionFrameX[4] = 281, actionFrameX[5] = 345, actionFrameX[maxFrame] = 423;
			frameX = 0;
			isMove = true;
		}
		break;
	case VK_LEFT:		//뒤로
		if (!isMove) 
		{
			action = Action::bMove;
			maxFrame = 6;
			actionFrameX[0] = 0;	actionFrameX[1] = 85, actionFrameX[2] = 152, actionFrameX[3] = 217,
				actionFrameX[4] = 280, actionFrameX[5] = 335, actionFrameX[maxFrame] = 409;
			frameX = maxFrame - 1;
			isMove = true;
		}
		break;
	case 'A':		//강발
		action = Action::bKick;
		maxFrame = 8;
		actionFrameX[0] = 0;	actionFrameX[1] = 75, actionFrameX[2] = 140, actionFrameX[3] = 260,
			actionFrameX[4] = 375, actionFrameX[5] = 490, actionFrameX[6] = 590, actionFrameX[7] = 650, actionFrameX[maxFrame] = 745;
		frameX = 0;
		isMove = false;
		isStatus = true;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(30);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(2);
		break;
	case 'S':		//약발
		action = Action::sKick;
		maxFrame = 5;
		actionFrameX[0] = 0;	actionFrameX[1] = 90, actionFrameX[2] = 156, actionFrameX[3] = 282,
			actionFrameX[4] = 348, actionFrameX[maxFrame] = 444;
		frameX = 0;
		isMove = false;
		isStatus = true;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(35);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(2);
		break;
	case 'Q':		//강손
		action = Action::bHand;
		maxFrame = 8;
		actionFrameX[0] = 0;	actionFrameX[1] = 86, actionFrameX[2] = 170, actionFrameX[3] = 254,
			actionFrameX[4] = 371, actionFrameX[5] = 486, actionFrameX[6] = 577, actionFrameX[7] = 660, actionFrameX[maxFrame] = 753;
		frameX = 0;
		isMove = false;
		isStatus = true;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(20);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 'W':		//약손
		action = Action::sHand;
		maxFrame = 3;
		actionFrameX[0] = 0;	actionFrameX[1] = 85, actionFrameX[2] = 188, actionFrameX[maxFrame] = 275;
		frameX = 0;
		isMove = false;
		isStatus = true;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(20);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(2);
		break;
	case 'Z':		//1피격
		action = Action::sHit;
		maxFrame = 5;
		actionFrameX[0] = 0;	actionFrameX[1] = 94, actionFrameX[2] = 194,
			actionFrameX[3] = 290, actionFrameX[4] = 385, actionFrameX[maxFrame] = 473;
		frameX = 0;
		isMove = false;
		isStatus = true;
		break;
	case 'X':		//2피격
		action = Action::bHit;
		maxFrame = 5;
		actionFrameX[0] = 0;	actionFrameX[1] = 97, actionFrameX[2] = 192,
			actionFrameX[3] = 276, actionFrameX[4] = 353, actionFrameX[maxFrame] = 440;
		frameX = 0;
		isMove = false;
		isStatus = true;
		break;
	case 0:	//기본자세
		action = Action::Basic;
		maxFrame = 7;
		actionFrameX[0] = 0;	actionFrameX[1] = 87, actionFrameX[2] = 172, actionFrameX[3] = 256,
			actionFrameX[4] = 342, actionFrameX[5] = 426, actionFrameX[6] = 511, actionFrameX[maxFrame] = 598;
		break;


	}
}


void Terry::SetBodySize()
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

void Terry::MoveToFrame()
{
	switch (action)
	{
	case Action::fMove:
	{
		if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT) || isStatus)
		{
			isMove = false;
			KeyEvent(0);
		}
		pos.x += moveSpeed;
			NextFrame(true);
	}break;
	case Action::bMove:
	{
		if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT) || isStatus)
		{
			isMove = false;
			KeyEvent(0);
		}
		pos.x -= moveSpeed;
			NextFrame(false);
	}break;
	}
}

void Terry::ProcessInputKey()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		KeyEvent(VK_RIGHT);
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		KeyEvent(VK_LEFT);
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))	//강발
	{
		KeyEvent('A');
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))	//약발
	{
		KeyEvent('S');
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))	//강손
	{
		KeyEvent('Q');
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('W'))	//약손
	{
		KeyEvent('W');
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))	//1피격
	{
		KeyEvent('Z');
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))	//2피격
	{
		KeyEvent('X');
	}
	/*if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		inputKey = 0;
	}*/
}

void Terry::NextFrame(bool b)
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

