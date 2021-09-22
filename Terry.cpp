#include "Terry.h"
#include "Image.h"
#include "KeyManager.h"

void Terry::Init()
{
	img = new Image;
	backBuffer = new Image;
	backGround = new Image;

	isReverse = true;
	isAlive = true;
	isMoveLeft = isMoveRight = isStatus = isHit = false;
	maxFrame = 7;
	hp = 100;

	fileName = "Image/Terry/Terry_basic.bmp";
	strcpy_s(ch, fileName.c_str());
	//img->Init("Image/Iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255), true);

	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);
	backGround->Init("Image/characterBackground.bmp", 1200, 800, true, RGB(255, 0, 255));


	img->Init(ch, 598, 120, maxFrame, 1, true, RGB(143, 123, 165));

	walkFrameX[0] = 0;	walkFrameX[1] = 87, walkFrameX[2] = 172, walkFrameX[3] = 256, 
	walkFrameX[4] = 342, walkFrameX[5] = 426, walkFrameX[6] = 511, walkFrameX[maxFrame] = 598;

	frameX = frameY = 0;
	elapsedCount = 0;
	

	pos.x = 200;
	pos.y = WIN_SIZE_Y / 2;
	moveSpeed = 10;

	bodySizeY = 120;
	for (int i = 0; i < maxFrame; i++)
	{
		bodySizeX = walkFrameX[i + 1] - walkFrameX[i];
		shape.left = pos.x - (bodySizeX /2);
		shape.right = pos.x + (bodySizeX / 2);
		shape.top = pos.y - (bodySizeY / 2);
		shape.bottom = pos.y + (bodySizeY / 2);
	}

	ammo = new Ammo;
	ammo->Init();

}



void Terry::Update()
{
	if (isHit)
	{
		hp--;
		isHit = false;
		KeyEvent(7);
		isStatus = true;
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
	}
	else if (isMoveRight)
	{
		if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			isMoveRight = false;
			KeyEvent(0);
		}
		frameX++;
		pos.x += moveSpeed;
		if (frameX >= maxFrame)
		{
			frameX = 0;
		}
		for (int i = 0; i < maxFrame; i++)
		{
			bodySizeX = walkFrameX[i + 1] - walkFrameX[i];
			shape.left = pos.x - (bodySizeX / 2);
			shape.right = pos.x + (bodySizeX / 2);
			shape.top = pos.y - (bodySizeY / 2);
			shape.bottom = pos.y + (bodySizeY / 2);
		}
	}
	else if (isMoveLeft)
	{
		if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			isMoveLeft = false;
			KeyEvent(0);
		}
		frameX--;
		pos.x -= moveSpeed;
		if (frameX <= 0)
		{
			frameX = maxFrame-1;
		}
		for (int i = 0; i < maxFrame; i++)
		{
			bodySizeX = walkFrameX[i + 1] - walkFrameX[i];
			shape.left = pos.x - (bodySizeX / 2);
			shape.right = pos.x + (bodySizeX / 2);
			shape.top = pos.y - (bodySizeY / 2);
			shape.bottom = pos.y + (bodySizeY / 2);
		}

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
			isMoveRight = true;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			KeyEvent(2);
			isMoveLeft = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))	//강발
		{
			KeyEvent(3);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))	//약발
		{
			KeyEvent(4);
			isStatus = true;			
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))	//강손
		{
			KeyEvent(5);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('W'))	//약손
		{
			KeyEvent(6);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))	//1피격
		{
			KeyEvent(7);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))	//2피격
		{
			KeyEvent(8);
			isStatus = true;
		}
	}
	ammo->Update();
	// 앞으로 움직이기

	backBuffer->GetImageInfo()->frameWidth = shape.right - shape.left;
	backBuffer->GetImageInfo()->frameHeight = shape.bottom - shape.top;
}

void Terry::Render(HDC hdc)
{

	if (isReverse)
	{

		HDC reverseDC = backBuffer->GetMemDC();
		backGround->Render(reverseDC, pos.x, pos.y);
		//Rectangle(reverseDC, shape.left, shape.top, shape.right, shape.bottom);
		img->Render(reverseDC, pos.x, pos.y, frameX, frameY, walkFrameX);
		ammo->Render(reverseDC);

		backBuffer->Render(hdc, pos.x, pos.y, frameX, frameY, walkFrameX, true);
	}
	else
	{

		//Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
		img->Render(hdc, pos.x, pos.y, frameX, frameY, walkFrameX);
		ammo->Render(hdc);
	}
}

void Terry::Release()
{
	if (img)
	{
		delete img;
		img = nullptr;
	}
	SAFE_RELEASE(backGround);
	SAFE_RELEASE(backBuffer);
	ammo->Release();
}

void Terry::KeyEvent(int a)
{
	switch (a)
	{
	case 0:		//기본자세
		fileName = "Image/Terry/Terry_basic.bmp";
		maxFrame = 7;
		walkFrameX[0] = 0;	walkFrameX[1] = 87, walkFrameX[2] = 172, walkFrameX[3] = 256,
			walkFrameX[4] = 342, walkFrameX[5] = 426, walkFrameX[6] = 511, walkFrameX[maxFrame] = 598;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 598, 111, maxFrame, 1, true, RGB(143, 123, 165));
		frameX = 0;
		break;
	case 1:		//앞으로
		fileName = "Image/Terry/Terry_Forward.bmp";
		maxFrame = 6;
		walkFrameX[0] = 0;	walkFrameX[1] = 77, walkFrameX[2] = 151, walkFrameX[3] = 217,
			walkFrameX[4] = 281, walkFrameX[5] = 345, walkFrameX[maxFrame] = 423;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 423, 133, maxFrame, 1, true, RGB(143, 123, 165));
		frameX = 0;
		break;
	case 2:		//뒤로
		fileName = "Image/Terry/Terry_Backward.bmp";
		maxFrame = 6;
		walkFrameX[0] = 0;	walkFrameX[1] = 85, walkFrameX[2] = 152, walkFrameX[3] = 217,
			walkFrameX[4] = 280, walkFrameX[5] = 335, walkFrameX[maxFrame] = 409;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 409, 130, maxFrame, 1, true, RGB(143, 123, 165));
		frameX = maxFrame-1;
		break;
	case 3:		//강발
		fileName = "Image/Terry/Terry_kick.bmp";
		maxFrame = 8;
		walkFrameX[0] = 0;	walkFrameX[1] = 75, walkFrameX[2] = 140, walkFrameX[3] = 260,
		walkFrameX[4] = 375, walkFrameX[5] = 490, walkFrameX[6] = 590, walkFrameX[7] = 650, walkFrameX[maxFrame] = 745;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 745, 114, maxFrame, 1, true, RGB(143, 123, 165));
		frameX = 0;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(30);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 4:		//약발
		fileName = "Image/Terry/Terry_sKick.bmp";
		maxFrame = 5;
		walkFrameX[0] = 0;	walkFrameX[1] = 90, walkFrameX[2] = 156, walkFrameX[3] = 282,
			walkFrameX[4] = 348,walkFrameX[maxFrame] = 444;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 444, 112, maxFrame, 1, true, RGB(143, 123, 165));
		frameX = 0;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(35);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 5:		//강손
		fileName = "Image/Terry/Terry_bAttack.bmp";
		maxFrame = 8;
		walkFrameX[0] = 0;	walkFrameX[1] = 86, walkFrameX[2] = 170, walkFrameX[3] = 254,
			walkFrameX[4] = 371, walkFrameX[5] = 486, walkFrameX[6] = 577, walkFrameX[7] = 660, walkFrameX[maxFrame] = 753;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 753, 116, maxFrame, 1, true, RGB(143, 123, 165));
		frameX = 0;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(20);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(4);
		break;
	case 6:		//약손
		fileName = "Image/Terry/Terry_sAttack.bmp";
		maxFrame = 3;
		walkFrameX[0] = 0;	walkFrameX[1] = 85, walkFrameX[2] = 188,walkFrameX[maxFrame] = 275;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 275, 114, maxFrame, 1, true, RGB(143, 123, 165));
		frameX = 0;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(20);
		ammo->SetTerryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 7:		//1피격
		fileName = "Image/Terry/Terry_Hit.bmp";
		maxFrame = 5;
		walkFrameX[0] = 0;	walkFrameX[1] = 94, walkFrameX[2] = 194,
		walkFrameX[3] = 290, walkFrameX[4] = 385, walkFrameX[maxFrame] = 473;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 473, 115, maxFrame, 1, true, RGB(143, 123, 165));
		frameX = 0;
		break;
	case 8:		//2피격
		fileName = "Image/Terry/Terry_bHit.bmp";
		maxFrame = 5;
		walkFrameX[0] = 0;	walkFrameX[1] = 97, walkFrameX[2] = 192,
		walkFrameX[3] = 276, walkFrameX[4] = 353, walkFrameX[maxFrame] = 440;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 440, 115, maxFrame, 1, true, RGB(143, 123, 165));
		frameX = 0;
		break;
	
		
	}


	
	
}
