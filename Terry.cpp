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
	
	/*if (isStatus)
	{
		switch(action)
		{
		case Action::sHit:
			hp--;
			isHit = false;
			KeyEvent(7);
			isStatus = true;
			ammo->SetIsAlive(false);
			break;
		case Action::sHand:
			KeyEvent(6);
				break;

		}
	}*/
	/*if (isHit)
	{
		hp--;
		isHit = false;
		KeyEvent(7);
		isStatus = true;
		ammo->SetIsAlive(false);
	}

	if (isStatus)
	{
		
		frameX++;
		if (frameX >= maxFrame)
		{
			frameX = 0;
			isStatus = false;
			KeyEvent(0);
		}
	}*/

	fBodySize();

	if (istest)
	{
		IsStatus();
	}
	else if (isMove)
	{
		fIsMove();
	}
	else
	{
		frameX++;
		if (frameX >= maxFrame)
		{
		frameX = 0;
		}
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			KeyEvent(1);
			isMove = true;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			KeyEvent(2);
			isMove = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))	//강발
		{
			KeyEvent(3);
			istest = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))	//약발
		{
			KeyEvent(4);	
			istest = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))	//강손
		{
			KeyEvent(5);
			istest = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('W'))	//약손
		{
			KeyEvent(6);
			istest = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))	//1피격
		{
			KeyEvent(7);
			istest = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))	//2피격
		{
			KeyEvent(8);
			istest = true;
		}
	}
	ammo->Update();
}

void Terry::Render(HDC hdc)
{
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
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

void Terry::KeyEvent(int a)
{
	switch (a)
	{
	case 0:		//기본자세
		action = Action::Basic;
		maxFrame = 7;
		actionFrameX[0] = 0;	actionFrameX[1] = 87, actionFrameX[2] = 172, actionFrameX[3] = 256,
			actionFrameX[4] = 342, actionFrameX[5] = 426, actionFrameX[6] = 511, actionFrameX[maxFrame] = 598;
		frameX = 0;
		break;
	case 1:		//앞으로
		action = Action::fMove;
		maxFrame = 6;
		actionFrameX[0] = 0;	actionFrameX[1] = 77, actionFrameX[2] = 151, actionFrameX[3] = 217,
			actionFrameX[4] = 281, actionFrameX[5] = 345, actionFrameX[maxFrame] = 423;
		frameX = 0;
		isMoveRight = true;
		break;
	case 2:		//뒤로
		action = Action::bMove;
		maxFrame = 6;
		actionFrameX[0] = 0;	actionFrameX[1] = 85, actionFrameX[2] = 152, actionFrameX[3] = 217,
			actionFrameX[4] = 280, actionFrameX[5] = 335, actionFrameX[maxFrame] = 409;
		frameX = maxFrame - 1;
		isMoveLeft = true;
		break;
	case 3:		//강발
		action = Action::bKick;
		maxFrame = 8;
		actionFrameX[0] = 0;	actionFrameX[1] = 75, actionFrameX[2] = 140, actionFrameX[3] = 260,
			actionFrameX[4] = 375, actionFrameX[5] = 490, actionFrameX[6] = 590, actionFrameX[7] = 650, actionFrameX[maxFrame] = 745;
		frameX = 0;
		isStatus = true;
		/*ammo->SetIsAlive(true);
		pos.x += 70;
		ammo->SetPos(pos);
		pos.x -= 70;
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(3);*/
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(30);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 4:		//약발
		action = Action::sKick;
		maxFrame = 5;
		actionFrameX[0] = 0;	actionFrameX[1] = 90, actionFrameX[2] = 156, actionFrameX[3] = 282,
			actionFrameX[4] = 348, actionFrameX[maxFrame] = 444;
		frameX = 0;
		isStatus = true;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(35);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 5:		//강손
		action = Action::bHand;
		maxFrame = 8;
		actionFrameX[0] = 0;	actionFrameX[1] = 86, actionFrameX[2] = 170, actionFrameX[3] = 254,
			actionFrameX[4] = 371, actionFrameX[5] = 486, actionFrameX[6] = 577, actionFrameX[7] = 660, actionFrameX[maxFrame] = 753;
		frameX = 0;
		isStatus = true;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(20);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(4);
		break;
	case 6:		//약손
		action = Action::sHand;
		maxFrame = 3;
		actionFrameX[0] = 0;	actionFrameX[1] = 85, actionFrameX[2] = 188, actionFrameX[maxFrame] = 275;
		frameX = 0;
		isStatus = true;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(20);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 7:		//1피격
		action = Action::sHit;
		maxFrame = 5;
		actionFrameX[0] = 0;	actionFrameX[1] = 94, actionFrameX[2] = 194,
			actionFrameX[3] = 290, actionFrameX[4] = 385, actionFrameX[maxFrame] = 473;
		frameX = 0;
		isStatus = true;
		break;
	case 8:		//2피격
		action = Action::bHit;
		maxFrame = 5;
		actionFrameX[0] = 0;	actionFrameX[1] = 97, actionFrameX[2] = 192,
			actionFrameX[3] = 276, actionFrameX[4] = 353, actionFrameX[maxFrame] = 440;
		frameX = 0;
		isStatus = true;
		break;


	}
}

void Terry::IsStatus()
{
	if (isHit)
	{
		hp--;
		isHit = false;
		KeyEvent(7);
		isStatus = true;
		ammo->SetIsAlive(false);
		istest = true;
	}
	if (isStatus)
	{
		frameX++;
		if (frameX >= maxFrame)
		{
			frameX = 0;
			KeyEvent(0);
			isStatus = false;
			istest = false;
		}
	}
	//else
	//{
	//	frameX++;
	//	if (frameX >= maxFrame)
	//	{
	//		frameX = 0;
	//	}

	//	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	//	{
	//		KeyEvent(1);
	//	}
	//	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	//	{
	//		KeyEvent(2);
	//	}
	//	else if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))	//강발
	//	{
	//		KeyEvent(3);
	//	}
	//	else if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))	//약발
	//	{
	//		KeyEvent(4);
	//	}
	//	else if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))	//강손
	//	{
	//		KeyEvent(5);
	//	}
	//	else if (KeyManager::GetSingleton()->IsOnceKeyDown('W'))	//약손
	//	{
	//		KeyEvent(6);
	//	}
	//	else if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))	//1피격
	//	{
	//		KeyEvent(7);
	//	}
	//	else if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))	//2피격
	//	{
	//		KeyEvent(8);
	//	}
	//}
}

void Terry::fBodySize()
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

void Terry::fIsMove()
{
	if (isMoveRight)
	{
		if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			isMoveRight = false;
			KeyEvent(0);
			isMove = false;
		}
		frameX++;
		pos.x += moveSpeed;
		fBodySize();
		if (frameX >= maxFrame)
		{
			frameX = 0;
		}
	}
	else if (isMoveLeft)
	{
		if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			isMoveLeft = false;
			KeyEvent(0);
			isMove = false;
		}
		frameX--;
		pos.x -= moveSpeed;
		fBodySize();
		if (frameX <= 0)
		{
			frameX = maxFrame - 1;
		}
	}
}


