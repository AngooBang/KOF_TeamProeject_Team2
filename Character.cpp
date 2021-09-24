#include "Character.h"
#include "KeyManager.h"
#include "Image.h"
#include "HitBox.h"
#include "TerryFrame.h"
#include "MaryFrame.h"

void Character::Init()
{
	switch (playerNum)
	{
	case 1:	// player1p
		SetCharacterData(characterType);

		pos.x = 200;
		break;
	case 2: // player2p
		SetCharacterData(characterType);
		ReverseImg();
		
		pos.x = 800;
		break;
	}

	hitBox = new HitBox();

	pos.y = WIN_SIZE_Y / 2;

	hp = 100;
	isAlive = true;
	isStatus = isHit = isMove = false;

	moveSpeed = 10;

	action = Action::Basic;

	bodySizeY = 120;
	for (int i = 0; i < maxFrame[action]; i++)
	{
		bodySizeX = actionFrameX[i + 1] - actionFrameX[i];
		shape.left = pos.x - (bodySizeX / 2);
		shape.right = pos.x + (bodySizeX / 2);
		shape.top = pos.y - (bodySizeY / 2);
		shape.bottom = pos.y + (bodySizeY / 2);
	}
	// ĳ���Ͱ� ��Ʈ�ڽ� ��ü�� �ϳ��� ���´�.
	// ��Ʈ�ڽ��� Ÿ���� ���ΰ��ӿ��� ���������ش�.
	// �浹�� ��Ʈ�ڽ�.cpp���� ó���Ѵ�.
	// ĳ����.cpp���� �̵�,����,���ݵ�� �����Ѵ�.
	// ĳ����init()���� ĳ����Ÿ�Կ� ���� �̹��� �� �ʱ�ȭ�� �����Ѵ�.
	// �̹����� �ʱ�ȭ�� CharacterType�� ���� 
}

void Character::Update()
{
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
		NextFrame();
	}

	SetBodySize();

}

void Character::Render(HDC hdc)
{
	//Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);

	if (charImg)
	{
		charImg[action].Render(hdc, pos.x, pos.y, frameX, frameY, actionFrameX[action]);
	}
	hitBox->Render(hdc);
}

void Character::Release()
{
	//for (int i = 0; i < Action::END; i++)
	//{
	//	delete[] actionFrameX[i];
	//}
	//delete[] actionFrameX;
	if (charImg)
	{
		delete[] charImg;
		charImg = nullptr;
	}
	hitBox->Release();

}

void Character::SetCharacterData(CharacterType type)
{
	switch(type)
	{
	case CharacterType::Terry:
		charImg = new Image[Action::END];

		charImg[Action::Basic].Init("Image/Terry/Terry_basic.bmp", 598, 120, 7, 1, true, RGB(143, 123, 165));
		charImg[Action::fMove].Init("Image/Terry/Terry_Forward.bmp", 423, 133, 6, 1, true, RGB(143, 123, 165));
		charImg[Action::bMove].Init("Image/Terry/Terry_Backward.bmp", 409, 130, 6, 1, true, RGB(143, 123, 165));
		charImg[Action::sHand].Init("Image/Terry/Terry_sAttack.bmp", 275, 114, 3, 1, true, RGB(143, 123, 165));
		charImg[Action::bHand].Init("Image/Terry/Terry_bAttack.bmp", 753, 116, 8, 1, true, RGB(143, 123, 165));
		charImg[Action::sKick].Init("Image/Terry/Terry_sKick.bmp", 444, 112, 5, 1, true, RGB(143, 123, 165));
		charImg[Action::bKick].Init("Image/Terry/Terry_kick.bmp", 745, 114, 8, 1, true, RGB(143, 123, 165));
		charImg[Action::sHit].Init("Image/Terry/Terry_Hit.bmp", 473, 115, 5, 1, true, RGB(143, 123, 165));
		charImg[Action::bHit].Init("Image/Terry/Terry_bHit.bmp", 440, 115, 5, 1, true, RGB(143, 123, 165));
		
		maxFrame[Action::Basic] = 7;
		maxFrame[Action::fMove] = 6;
		maxFrame[Action::bMove] = 6;
		maxFrame[Action::sHand] = 3;
		maxFrame[Action::bHand] = 8;
		maxFrame[Action::sKick] = 5;
		maxFrame[Action::bKick] = 8;
		maxFrame[Action::sHit] = 5;
		maxFrame[Action::bHit] = 5;

		actionFrameX[Action::Basic] = terryBasic;
		actionFrameX[Action::fMove] = terryfMove;
		actionFrameX[Action::bMove] = terrybMove;
		actionFrameX[Action::sHand] = terrysHand;
		actionFrameX[Action::bHand] = terrybHand;
		actionFrameX[Action::sKick] = terrysKick;
		actionFrameX[Action::bKick] = terrybKick;
		actionFrameX[Action::sHit] = terrysHit;
		actionFrameX[Action::bHit] = terrybHit;

			//actionFrameX[0] = 0;	actionFrameX[1] = 87, actionFrameX[2] = 172, actionFrameX[3] = 256,
			//actionFrameX[4] = 342, actionFrameX[5] = 426, actionFrameX[6] = 511, actionFrameX[maxFrame] = 598;
		break;

	case CharacterType::Mary:
		charImg = new Image[Action::END];

		charImg[Action::Basic].Init("Image/Mary/Mary_Basic.bmp", 771, 120, 12, 1, true, RGB(0, 102, 0));
		charImg[Action::fMove].Init("Image/Mary/Mary_Forward.bmp", 501, 155, 8, 1, true, RGB(0, 102, 0));
		charImg[Action::bMove].Init("Image/Mary/Mary_BackWard.bmp", 430, 125, 7, 1, true, RGB(0, 102, 0));
		charImg[Action::sHand].Init("Image/Mary/Mary_sAttack.bmp", 228, 125, 3, 1, true, RGB(0, 102, 0));
		charImg[Action::bHand].Init("Image/Mary/Mary_bAttack.bmp", 379, 129, 5, 1, true, RGB(0, 102, 0));
		charImg[Action::sKick].Init("Image/Mary/Mary_sKick.bmp", 441, 133, 6, 1, true, RGB(0, 102, 0));
		charImg[Action::bKick].Init("Image/Mary/Mary_bKick.bmp", 786, 123, 10, 1, true, RGB(0, 102, 0));
		charImg[Action::sHit].Init("Image/Mary/Mary_Hit.bmp", 432, 125, 5, 1, true, RGB(0, 102, 0));
		charImg[Action::bHit].Init("Image/Mary/Mary_bHit.bmp", 409, 125, 5, 1, true, RGB(0, 102, 0));

		maxFrame[Action::Basic] = 12;
		maxFrame[Action::fMove] = 8;
		maxFrame[Action::bMove] = 7;
		maxFrame[Action::sHand] = 3;
		maxFrame[Action::bHand] = 5;
		maxFrame[Action::sKick] = 6;
		maxFrame[Action::bKick] = 10;
		maxFrame[Action::sHit] = 5;
		maxFrame[Action::bHit] = 5;

		actionFrameX[Action::Basic] = maryBasic;
		actionFrameX[Action::fMove] = maryfMove;
		actionFrameX[Action::bMove] = marybMove;
		actionFrameX[Action::sHand] = marysHand;
		actionFrameX[Action::bHand] = marybHand;
		actionFrameX[Action::sKick] = marysKick;
		actionFrameX[Action::bKick] = marybKick;
		actionFrameX[Action::sHit] = marysHit;
		actionFrameX[Action::bHit] = marybHit;

		break;
	}
}

void Character::ReverseImg()
{
	charImg[Action::Basic].ReverseImg();
	charImg[Action::fMove].ReverseImg();
	charImg[Action::bMove].ReverseImg();
	charImg[Action::sHand].ReverseImg();
	charImg[Action::bHand].ReverseImg();
	charImg[Action::sKick].ReverseImg();
	charImg[Action::bKick].ReverseImg();
	charImg[Action::sHit].ReverseImg();
	charImg[Action::bHit].ReverseImg();
}


void Character::KeyEvent(char inputKey)
{
	switch (inputKey)
	{
		case VK_RIGHT:		//������
			if (!isMove)
			{
				action = Action::fMove;
				frameX = 0;
				isMove = true;
			}
			break;
		case VK_LEFT:		//�ڷ�
			if (!isMove)
			{
				action = Action::bMove;
				frameX = 0;
				isMove = true;
			}
			break;
		case 'A':		//����
			action = Action::bKick;
			frameX = 0;
			isMove = false;
			isStatus = true;
			//ammo->SetIsAlive(true);
			//ammo->SetPos(pos);
			//ammo->SetMoveSpeed(30);
			//ammo->SetTerryFire(true);
			//ammo->SetMaxFrame(2);
			break;
		case 'S':		//���
			action = Action::sKick;
			frameX = 0;
			isMove = false;
			isStatus = true;
			//ammo->SetIsAlive(true);
			//ammo->SetPos(pos);
			//ammo->SetMoveSpeed(35);
			//ammo->SetTerryFire(true);
			//ammo->SetMaxFrame(2);
			break;
		case 'Q':		//����
			action = Action::bHand;
			frameX = 0;
			isMove = false;
			isStatus = true;
			//ammo->SetIsAlive(true);
			//ammo->SetPos(pos);
			//ammo->SetMoveSpeed(20);
			//ammo->SetTerryFire(true);
			//ammo->SetMaxFrame(3);
			break;
		case 'W':		//���
			action = Action::sHand;
			frameX = 0;
			isMove = false;
			isStatus = true;
			//ammo->SetIsAlive(true);
			//ammo->SetPos(pos);
			//ammo->SetMoveSpeed(20);
			//ammo->SetTerryFire(true);
			//ammo->SetMaxFrame(2);
			break;
		case 'Z':		//1�ǰ�
			action = Action::sHit;
			frameX = 0;
			isMove = false;
			isStatus = true;
			break;
		case 'X':		//2�ǰ�
			action = Action::bHit;
			frameX = 0;
			isMove = false;
			isStatus = true;
			break;
		case 'J':		//������
			if (!isMove)
			{
				action = Action::fMove;
				frameX = 0;
				isMove = true;
			}
			break;
		case 'L':		//�ڷ�
			if (!isMove)
			{
				action = Action::bMove;
				frameX = 0;
				isMove = true;
			}
			break;
		case 'D':		//����
			action = Action::bKick;
			frameX = 0;
			isMove = false;
			isStatus = true;
			//ammo->SetIsAlive(true);
			//ammo->SetPos(pos);
			//ammo->SetMoveSpeed(10);
			//ammo->SetMaryFire(true);
			//ammo->SetMaxFrame(4);
			break;
		case 'F':		//���
			action = Action::sKick;
			frameX = 0;
			isMove = false;
			isStatus = true;
			//ammo->SetIsAlive(true);
			//ammo->SetPos(pos);
			//ammo->SetMoveSpeed(10);
			//ammo->SetMaryFire(true);
			//ammo->SetMaxFrame(3);
			break;
		case 'E':		//����
			action = Action::bHand;
			frameX = 0;
			isMove = false;
			isStatus = true;
			//ammo->SetIsAlive(true);
			//ammo->SetPos(pos);
			//ammo->SetMoveSpeed(15);
			//ammo->SetMaryFire(true);
			//ammo->SetMaxFrame(3);
			break;
		case 'R':		//���
			action = Action::sHand;
			frameX = 0;
			isMove = false;
			isStatus = true;
			//ammo->SetIsAlive(true);
			//ammo->SetPos(pos);
			//ammo->SetMoveSpeed(10);
			//ammo->SetMaryFire(true);
			//ammo->SetMaxFrame(2);
			break;
			break;
		case 'C':		//1�ǰ�
			action = Action::sHit;
			frameX = 0;
			isHit = false;
			isMove = false;
			isStatus = true;
			break;
		case 'V':		//2�ǰ�
			action = Action::bHit;
			frameX = 0;
			isMove = false;
			isStatus = true;
			break;

		case 0:	//�⺻�ڼ�
			action = Action::Basic;
			break;
	}

}


void Character::SetBodySize()
{
	for (int i = 0; i < maxFrame[action]; i++)
	{
		bodySizeX = actionFrameX[i + 1] - actionFrameX[i];
		shape.left = pos.x - (bodySizeX / 2);
		shape.right = pos.x + (bodySizeX / 2);
		shape.top = pos.y - (bodySizeY / 2);
		shape.bottom = pos.y + (bodySizeY / 2);
	}
}

void Character::MoveToFrame()
{
	switch (playerNum)
	{
	case 1:	// player1p
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
			NextFrame();
		}break;
		case Action::bMove:
		{
			if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT) || isStatus)
			{
				isMove = false;
				KeyEvent(0);
			}
			pos.x -= moveSpeed;
			NextFrame();
		}break;
		}
		break;
	case 2: // player2p
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
			NextFrame();
		}break;
		case Action::bMove:
		{
			if (!KeyManager::GetSingleton()->IsStayKeyDown('L') || isStatus)
			{
				isMove = false;
				KeyEvent(0);
			}
			pos.x += moveSpeed;
			NextFrame();
		}break;
		}
		break;
	}




	
}

void Character::ProcessInputKey()
{
	switch (playerNum)
	{
	case 1:
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			KeyEvent(VK_RIGHT);
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			KeyEvent(VK_LEFT);
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))	//����
		{
			KeyEvent('A');
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))	//���
		{
			KeyEvent('S');
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))	//����
		{
			KeyEvent('Q');
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('W'))	//���
		{
			KeyEvent('W');
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))	//1�ǰ�
		{
			KeyEvent('Z');
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))	//2�ǰ�
		{
			KeyEvent('X');
		}

		break;
	case 2:
		if (KeyManager::GetSingleton()->IsStayKeyDown('J'))
		{
			KeyEvent('J');
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('L'))
		{
			KeyEvent('L');
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('D'))	//����
		{
			KeyEvent('D');
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))	//���
		{
			KeyEvent('F');
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('E'))	//����
		{
			KeyEvent('E');
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))	//���
		{
			KeyEvent('R');
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))	//1�ǰ�
		{
			KeyEvent('C');
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('V'))	//2�ǰ�
		{
			KeyEvent('V');
		}

		break;

	}
}

void Character::NextFrame()
{
	frameX++;
	if (frameX >= maxFrame[action])
	{
		frameX = 0;
		isStatus = false;
		if (!isMove)
		{
			KeyEvent(0);
		}
	}
}