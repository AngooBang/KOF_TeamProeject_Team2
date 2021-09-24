#include "Mary.h"
#include "Image.h"
#include "KeyManager.h"

void Mary::Init()
{
	img = new Image[Action::END];

	isAlive = true;
	isMoveLeft = isMoveRight = isStatus = isHit = false;
	maxFrame = 12;
	hp = 100;

	//fileName = "Image/Mary/Mary_Basic.bmp";
	//strcpy_s(ch, fileName.c_str());
	////img->Init("Image/Iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255), true);
	//img->Init(ch, 771, 120, maxFrame, 1, true, RGB(0, 102, 0));

	img[Action::Basic].Init("Image/Mary/Mary_Basic.bmp", 771, 120, 12, 1, true, RGB(0, 102, 0));
	img[Action::fMove].Init("Image/Mary/Mary_Forward.bmp", 501, 155, 8, 1, true, RGB(0, 102, 0));
	img[Action::bMove].Init("Image/Mary/Mary_BackWard.bmp", 430, 125, 7, 1, true, RGB(0, 102, 0));
	img[Action::sHand].Init("Image/Mary/Mary_sAttack.bmp", 228, 125, 3, 1, true, RGB(0, 102, 0));
	img[Action::bHand].Init("Image/Mary/Mary_bAttack.bmp", 379, 129, 5,1, true, RGB(0, 102, 0));
	img[Action::sKick].Init("Image/Mary/Mary_sKick.bmp", 441, 133, 6, 1, true, RGB(0, 102, 0));
	img[Action::bKick].Init("Image/Mary/Mary_bKick.bmp", 786, 123, 10, 1, true, RGB(0, 102, 0));
	img[Action::sHit].Init("Image/Mary/Mary_Hit.bmp", 432, 125, 5, 1, true, RGB(0, 102, 0));
	img[Action::bHit].Init("Image/Mary/Mary_bHit.bmp", 409, 125, 5, 1, true, RGB(0, 102, 0));

	img->ReverseImg();


	walkFrameX[0] = 0,	walkFrameX[1] = 60, walkFrameX[2] = 122, walkFrameX[3] = 184,
	walkFrameX[4] = 246, walkFrameX[5] = 311, walkFrameX[6] = 375, walkFrameX[7] = 440,
	walkFrameX[8] = 506, walkFrameX[9] = 574, walkFrameX[10] = 642, walkFrameX[11] = 706, walkFrameX[maxFrame] = 771;

	frameX = frameY = 0;
	elapsedCount = 0;

	action = Action::Basic;

	pos.x = 800;
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
		ammo->SetIsAlive(false);
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

		if (KeyManager::GetSingleton()->IsStayKeyDown('L'))	//앞으로(2p는 반대)
		{
			KeyEvent(2);
			isMoveRight = true;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('J'))	//뒤로(2p는 반대)
		{
			KeyEvent(1);
			isMoveLeft = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('D'))	//강발
		{
			KeyEvent(3);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))	//약발
		{
			KeyEvent(4);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('E'))	//강손
		{
			KeyEvent(5);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))	//약손
		{
			KeyEvent(6);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))	//1피격
		{
			KeyEvent(7);
			isStatus = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('V'))	//2피격
		{
			KeyEvent(8);
			isStatus = true;
		}
	}
	ammo->Update();
	// 앞으로 움직이기
}

void Mary::Render(HDC hdc)
{
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	if (img)
	{
		img[action].Render(hdc, pos.x, pos.y, frameX, frameY, walkFrameX);
	}
	ammo->Render(hdc);
}

void Mary::Release()
{
	if (img)
	{
		delete[] img;
		img = nullptr;
	}
	ammo->Release();
}

void Mary::KeyEvent(int a)
{
	switch (a)
	{
	case 0:		//기본자세
		action = Action::Basic;
		maxFrame = 12;
		walkFrameX[0] = 0, walkFrameX[1] = 60, walkFrameX[2] = 122, walkFrameX[3] = 184,
			walkFrameX[4] = 246, walkFrameX[5] = 311, walkFrameX[6] = 375, walkFrameX[7] = 440,
			walkFrameX[8] = 506, walkFrameX[9] = 574, walkFrameX[10] = 642, walkFrameX[11] = 706, walkFrameX[maxFrame] = 771;
		break;
	case 1:		//앞으로(2p반대)
		action = Action::fMove;
		maxFrame = 8;
		walkFrameX[0] = 0;	walkFrameX[1] = 59, walkFrameX[2] = 115, walkFrameX[3] = 180,
			walkFrameX[4] = 248, walkFrameX[5] = 315, walkFrameX[6] = 381, walkFrameX[7] = 441, walkFrameX[maxFrame] = 501;
		frameX = maxFrame-1;
		break;
	case 2:		//뒤로(2p반대)
		action = Action::bMove;
		maxFrame = 7;
		walkFrameX[0] = 0;	walkFrameX[1] = 66, walkFrameX[2] = 130, walkFrameX[3] = 195,
			walkFrameX[4] = 255, walkFrameX[5] = 314, walkFrameX[6] = 373, walkFrameX[maxFrame] = 430;
		frameX = maxFrame-1;
		break;
	case 3:		//강발
		action = Action::bKick;
		maxFrame = 10;
		walkFrameX[0] = 0;	walkFrameX[1] = 65, walkFrameX[2] = 133, walkFrameX[3] = 205,
			walkFrameX[4] = 285, walkFrameX[5] = 395, walkFrameX[6] = 505, walkFrameX[7] = 583,
				walkFrameX[8] = 655, walkFrameX[9] = 722, walkFrameX[maxFrame] = 786;
		frameX = maxFrame - 1;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(10);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(4);
		break;
	case 4:		//약발
		action = Action::sKick;
		maxFrame = 6;
		walkFrameX[0] = 0;	walkFrameX[1] = 87, walkFrameX[2] = 160, walkFrameX[3] = 235,
			walkFrameX[4] = 305, walkFrameX[5] = 373, walkFrameX[maxFrame] = 441;
		frameX = maxFrame - 1;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(10);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 5:		//강손
		action = Action::bHand;
		maxFrame = 5;
		walkFrameX[0] = 0;	walkFrameX[1] = 81, walkFrameX[2] = 154, walkFrameX[3] = 242,
			walkFrameX[4] = 315, walkFrameX[maxFrame] = 379;
		frameX = maxFrame - 1;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(15);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(3);
		break;
	case 6:		//약손
		action = Action::sHand;
		maxFrame = 3;
		walkFrameX[0] = 0;	walkFrameX[1] = 85, walkFrameX[2] = 155, walkFrameX[maxFrame] = 228;
		frameX = maxFrame-1;
		ammo->SetIsAlive(true);
		ammo->SetPos(pos);
		ammo->SetMoveSpeed(10);
		ammo->SetMaryFire(true);
		ammo->SetMaxFrame(2);
		break;
	case 7:		//1피격
		action = Action::sHit;
		maxFrame = 5;
		walkFrameX[0] = 0;	walkFrameX[1] = 85, walkFrameX[2] = 155,
			walkFrameX[3] = 243, walkFrameX[4] = 343, walkFrameX[maxFrame] = 432;
		frameX = maxFrame - 1;
		break;
	case 8:		//2피격
		action = Action::bHit;
		maxFrame = 5;
		walkFrameX[0] = 0;	walkFrameX[1] = 78, walkFrameX[2] = 154,
			walkFrameX[3] = 236, walkFrameX[4] = 323, walkFrameX[maxFrame] = 409;
		frameX = maxFrame - 1;
		break;


	}




}
