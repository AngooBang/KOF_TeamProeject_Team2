#include "Mary.h"
#include "Image.h"
#include "KeyManager.h"

void Mary::Init()
{
	img = new Image;
	isAlive = true;
	isMoveLeft = isMoveRight = isStatus = isHit = false;
	maxFrame = 12;
	hp = 100;

	fileName = "Image/Mary/Mary_Basic.bmp";
	strcpy_s(ch, fileName.c_str());
	//img->Init("Image/Iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255), true);

	img->Init(ch, 771, 120, maxFrame, 1, true, RGB(0, 102, 0));

	walkFrameX[0] = 0,	walkFrameX[1] = 60, walkFrameX[2] = 122, walkFrameX[3] = 184,
	walkFrameX[4] = 246, walkFrameX[5] = 311, walkFrameX[6] = 375, walkFrameX[7] = 440,
	walkFrameX[8] = 506, walkFrameX[9] = 574, walkFrameX[10] = 642, walkFrameX[11] = 706, walkFrameX[maxFrame] = 771;

	frameX = frameY = 0;
	elapsedCount = 0;

	pos.x = 350;
	pos.y = WIN_SIZE_Y / 2;
	moveSpeed = 10;
	
	bodySizeY = 120;

	for (int i = 0; i < maxFrame; i++)
	{
		bodySizeX = walkFrameX[i + 1] - walkFrameX[i];
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
	if (isHit)
	{
		hp--;
		isHit = false;
		KeyEvent(7);
		isStatus = true;
	}

	if (isStatus)
	{
		frameX--;
		if (frameX <= 0)
		{
			frameX = maxFrame;
			isStatus = false;
			KeyEvent(0);
		}
	}
	else if (isMoveRight)
	{
		if (!KeyManager::GetSingleton()->IsStayKeyDown('L'))
		{
			isMoveRight = false;
			KeyEvent(0);
		}
		frameX--;
		pos.x += moveSpeed;
		if (frameX <= 0)
		{
			frameX = maxFrame - 1;
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
		if (!KeyManager::GetSingleton()->IsStayKeyDown('J'))
		{
			isMoveLeft = false;
			KeyEvent(0);
		}
		frameX--;
		pos.x -= moveSpeed;
		if (frameX <= 0)
		{
			frameX = maxFrame - 1;
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
		if (frameX <= 0)
		{
			frameX = maxFrame;
		}
		frameX--;

		if (KeyManager::GetSingleton()->IsStayKeyDown('L'))	//������(2p�� �ݴ�)
		{
			KeyEvent(2);
			isMoveRight = true;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('J'))	//�ڷ�(2p�� �ݴ�)
		{
			KeyEvent(1);
			isMoveLeft = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('D'))	//����
		{
			KeyEvent(3);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))	//���
		{
			KeyEvent(4);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('E'))	//����
		{
			KeyEvent(5);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))	//���
		{
			KeyEvent(6);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))	//1�ǰ�
		{
			KeyEvent(7);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('V'))	//2�ǰ�
		{
			KeyEvent(8);
			isStatus = true;
		}
	}
	ammo->Update();
	// ������ �����̱�
}

void Mary::Render(HDC hdc)
{
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	if (img)
	{
		img->Render(hdc, pos.x, pos.y, frameX, frameY, walkFrameX);
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

void Mary::KeyEvent(int a)
{
	switch (a)
	{
	case 0:		//�⺻�ڼ�
		fileName = "Image/Mary/Mary_Basic.bmp";
		maxFrame = 12;
		walkFrameX[0] = 0, walkFrameX[1] = 60, walkFrameX[2] = 122, walkFrameX[3] = 184,
			walkFrameX[4] = 246, walkFrameX[5] = 311, walkFrameX[6] = 375, walkFrameX[7] = 440,
			walkFrameX[8] = 506, walkFrameX[9] = 574, walkFrameX[10] = 642, walkFrameX[11] = 706, walkFrameX[maxFrame] = 771;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 771, 120, maxFrame, 1, true, RGB(0, 102, 0));
		break;
	case 1:		//������(2p�ݴ�)
		fileName = "Image/Mary/Mary_Forward.bmp";
		maxFrame = 8;
		walkFrameX[0] = 0;	walkFrameX[1] = 59, walkFrameX[2] = 115, walkFrameX[3] = 180,
			walkFrameX[4] = 248, walkFrameX[5] = 315, walkFrameX[6] = 381, walkFrameX[7] = 441, walkFrameX[maxFrame] = 501;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 501, 155, maxFrame, 1, true, RGB(0, 102, 0));
		frameX = maxFrame-1;
		break;
	case 2:		//�ڷ�(2p�ݴ�)
		fileName = "Image/Mary/Mary_BackWard.bmp";
		maxFrame = 7;
		walkFrameX[0] = 0;	walkFrameX[1] = 66, walkFrameX[2] = 130, walkFrameX[3] = 195,
			walkFrameX[4] = 255, walkFrameX[5] = 314, walkFrameX[6] = 373, walkFrameX[maxFrame] = 430;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 430, 125, maxFrame, 1, true, RGB(0, 102, 0));
		frameX = maxFrame-1;
		break;
	case 3:		//����
		fileName = "Image/Mary/Mary_bKick.bmp";
		maxFrame = 10;
		walkFrameX[0] = 0;	walkFrameX[1] = 65, walkFrameX[2] = 133, walkFrameX[3] = 205,
		walkFrameX[4] = 285, walkFrameX[5] = 395, walkFrameX[6] = 505, walkFrameX[7] = 583,
		walkFrameX[8] = 655, walkFrameX[9] = 722, walkFrameX[maxFrame] = 786;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 786, 123, maxFrame, 1, true, RGB(0, 102, 0));
		frameX = maxFrame - 1;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(10);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(4);
		break;
	case 4:		//���
		fileName = "Image/Mary/Mary_sKick.bmp";
		maxFrame = 6;
		walkFrameX[0] = 0;	walkFrameX[1] = 87, walkFrameX[2] = 160, walkFrameX[3] = 235,
		walkFrameX[4] = 305, walkFrameX[5] = 373, walkFrameX[maxFrame] = 441;
		strcpy_s(ch, fileName.c_str());
		frameX = maxFrame;
		img->Init(ch, 441, 133, maxFrame, 1, true, RGB(0, 102, 0));
		frameX = maxFrame - 1;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(10);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(4);
		break;
	case 5:		//����
		fileName = "Image/Mary/Mary_bAttack.bmp";
		maxFrame = 5;
		walkFrameX[0] = 0;	walkFrameX[1] = 81, walkFrameX[2] = 154, walkFrameX[3] = 242,
			walkFrameX[4] = 315, walkFrameX[maxFrame] = 379;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 379, 129, maxFrame, 1, true, RGB(0, 102, 0));
		frameX = maxFrame - 1;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(20);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 6:		//���
		fileName = "Image/Mary/Mary_sAttack.bmp";
		maxFrame = 3;
		walkFrameX[0] = 0;	walkFrameX[1] = 85, walkFrameX[2] = 155, walkFrameX[maxFrame] = 228;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 228, 125, maxFrame, 1, true, RGB(0, 102, 0));
		frameX = maxFrame-1;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(20);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 7:		//1�ǰ�
		fileName = "Image/Mary/Mary_Hit.bmp";
		maxFrame = 5;
		walkFrameX[0] = 0;	walkFrameX[1] = 85, walkFrameX[2] = 155,
			walkFrameX[3] = 243, walkFrameX[4] = 343, walkFrameX[maxFrame] = 432;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 432, 125, maxFrame, 1, true, RGB(0, 102, 0));
		frameX = maxFrame - 1;
		break;
	case 8:		//2�ǰ�
		fileName = "Image/Mary/Mary_bHit.bmp";
		maxFrame = 5;
		walkFrameX[0] = 0;	walkFrameX[1] = 78, walkFrameX[2] = 154,
			walkFrameX[3] = 236, walkFrameX[4] = 323, walkFrameX[maxFrame] = 409;
		strcpy_s(ch, fileName.c_str());
		img->Init(ch, 409, 125, maxFrame, 1, true, RGB(0, 102, 0));
		frameX = maxFrame - 1;
		break;


	}




}
