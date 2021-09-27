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
		
		pos.x = 400;
		break;
	}

	hitBox = new HitBox();
	hitBox->Init();

	pos.y = WIN_SIZE_Y / 2+140;

	hp = 100;
	isAlive = true;
	isStatus = isHit = isMove = false;

	moveSpeed = 20;

	action = Action::Basic;

	bodySizeX = 175;
	bodySizeY = 260;
	for (int i = 0; i < maxFrame[action]; i++)
	{
		bodySizeX = actionFrameX[action][frameX + 1] - actionFrameX[action][frameX];
		//bodySizeX = actionFrameX[i + 1] - actionFrameX[i];
		shape.left = pos.x - (bodySizeX / 2);
		shape.right = pos.x + (bodySizeX / 2);
		shape.top = pos.y - (bodySizeY / 2);
		shape.bottom = pos.y + (bodySizeY / 2);
	}
	// 캐릭터가 히트박스 객체를 하나씩 갖는다.
	// 히트박스의 타겟은 메인게임에서 지정을해준다.
	// 충돌은 히트박스.cpp에서 처리한다.
	// 캐릭터.cpp에선 이동,조작,공격등ㅇ을 정의한다.
	// 캐릭터init()에선 캐릭터타입에 따른 이미지 값 초기화를 정의한다.
	// 이미지값 초기화는 CharacterType에 따라 
}

void Character::Update()
{
	/*if (!isStatus)
	{
		ProcessInputKey();
	}
	else if (isHit)
	{
		ProcessInputKey();
	}*/
	hitBox->Update();

	if (isHit)
	{
		IsHit();
	}
	if (!isStatus)
		ProcessInputKey();
	if (isMove)
		MoveToFrame();

	NextFrame();

	//if (isHit)
	//{
	//	NextFrame();
	//}

	SetBodySize();
	
}

void Character::Render(HDC hdc)
{

	//Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	if (charImg)
	{
		switch (playerNum)
		{
		case 1:
			charImg[action].Render(hdc, pos.x, pos.y, frameX, frameY, actionFrameX[action]);
			break;
		case 2:
			charImg[action].Render2P(hdc, pos.x, pos.y, frameX, frameY, actionFrameX[action]);
			break;
		}
		
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
		charImg = new Image[Action::ActEnd];

		charImg[Action::Basic].Init("Image/Terry/Terry_basic.bmp", 1320, 260, 7, 1, true, RGB(143, 123, 165));
		charImg[Action::bMove].Init("Image/Terry/Terry_Backward.bmp", 900, 270, 6, 1, true, RGB(143, 123, 165));
		charImg[Action::sHand].Init("Image/Terry/Terry_sAttack.bmp", 600, 255, 3, 1, true, RGB(143, 123, 165));
		charImg[Action::bHand].Init("Image/Terry/Terry_bAttack.bmp", 1650, 255, 8, 1, true, RGB(143, 123, 165));
		charImg[Action::sKick].Init("Image/Terry/Terry_sKick.bmp", 970, 255, 5, 1, true, RGB(143, 123, 165));
		charImg[Action::bKick].Init("Image/Terry/Terry_kick.bmp", 1640, 255, 8, 1, true, RGB(143, 123, 165));
		charImg[Action::sHit].Init("Image/Terry/Terry_Hit.bmp", 1030, 255, 5, 1, true, RGB(143, 123, 165));
		charImg[Action::bHit].Init("Image/Terry/Terry_bHit.bmp", 970, 255, 5, 1, true, RGB(143, 123, 165));
		charImg[Action::Guard].Init("Image/Terry/Terry_Guard.bmp", 600, 250, 3, 1, true, RGB(143, 123, 165));

		
		maxFrame[Action::Basic] = 7;
		maxFrame[Action::fMove] = 6;
		maxFrame[Action::bMove] = 6;
		maxFrame[Action::sHand] = 3;
		maxFrame[Action::bHand] = 8;
		maxFrame[Action::sKick] = 5;
		maxFrame[Action::bKick] = 8;
		maxFrame[Action::sHit] = 5;
		maxFrame[Action::bHit] = 5;
		maxFrame[Action::Guard] = 3;


		switch (playerNum)
		{
		case 1:	// player1p
			actionFrameX[Action::Basic] = terryBasic;
			actionFrameX[Action::fMove] = terryfMove;
			charImg[Action::fMove].Init("Image/Terry/Terry_Forward.bmp", 920, 270, 6, 1, true, RGB(143, 123, 165));
			actionFrameX[Action::bMove] = terrybMove;
			actionFrameX[Action::sHand] = terrysHand;
			actionFrameX[Action::bHand] = terrybHand;
			actionFrameX[Action::sKick] = terrysKick;
			actionFrameX[Action::bKick] = terrybKick;
			actionFrameX[Action::sHit] = terrysHit;
			actionFrameX[Action::bHit] = terrybHit;
			actionFrameX[Action::Guard] = terryGuard;
			break;
		case 2: // player2p
			actionFrameX[Action::Basic] = terryBasic;
			actionFrameX[Action::fMove] = terryfMove_R;
			charImg[Action::fMove].Init("Image/Terry/Terry_Forward_R.bmp", 920, 270, 6, 1, true, RGB(143, 123, 165));
			actionFrameX[Action::bMove] = terrybMove_R;
			actionFrameX[Action::sHand] = terrysHand_R;
			actionFrameX[Action::bHand] = terrybHand_R;
			actionFrameX[Action::sKick] = terrysKick_R;
			actionFrameX[Action::bKick] = terrybKick_R;
			actionFrameX[Action::sHit] = terrysHit_R;
			actionFrameX[Action::bHit] = terrybHit_R;
			actionFrameX[Action::Guard] = terryGuard_R;
			break;
		}

			//actionFrameX[0] = 0;	actionFrameX[1] = 87, actionFrameX[2] = 172, actionFrameX[3] = 256,
			//actionFrameX[4] = 342, actionFrameX[5] = 426, actionFrameX[6] = 511, actionFrameX[maxFrame] = 598;
		break;

	case CharacterType::Mary:
		charImg = new Image[Action::ActEnd];

		charImg[Action::Basic].Init("Image/Mary/Mary_Basic.bmp", 1700, 260, 12, 1, true, RGB(0, 102, 0));
		charImg[Action::fMove].Init("Image/Mary/Mary_Forward.bmp", 1100, 340, 8, 1, true, RGB(0, 102, 0));
		charImg[Action::bMove].Init("Image/Mary/Mary_BackWard.bmp", 950, 270, 7, 1, true, RGB(0, 102, 0));
		charImg[Action::sHand].Init("Image/Mary/Mary_sAttack.bmp", 500, 270 , 3, 1, true, RGB(0, 102, 0));
		charImg[Action::bHand].Init("Image/Mary/Mary_bAttack.bmp", 840, 275, 5, 1, true, RGB(0, 102, 0));
		charImg[Action::sKick].Init("Image/Mary/Mary_sKick.bmp", 970, 280, 6, 1, true, RGB(0, 102, 0));
		charImg[Action::bKick].Init("Image/Mary/Mary_bKick.bmp", 1740, 260, 10, 1, true, RGB(0, 102, 0));
		charImg[Action::sHit].Init("Image/Mary/Mary_Hit.bmp", 950, 270, 5, 1, true, RGB(0, 102, 0));
		charImg[Action::bHit].Init("Image/Mary/Mary_bHit.bmp", 900, 270, 5, 1, true, RGB(0, 102, 0));
		charImg[Action::Guard].Init("Image/Mary/Mary_Guard.bmp", 540, 260, 3, 1, true, RGB(0, 102, 0));

		maxFrame[Action::Basic] = 12;
		maxFrame[Action::fMove] = 8;
		maxFrame[Action::bMove] = 7;
		maxFrame[Action::sHand] = 3;
		maxFrame[Action::bHand] = 5;
		maxFrame[Action::sKick] = 6;
		maxFrame[Action::bKick] = 10;
		maxFrame[Action::sHit] = 5;
		maxFrame[Action::bHit] = 5;
		maxFrame[Action::Guard] = 3;

		switch (playerNum)
		{
		case 1:	// player1p
			actionFrameX[Action::Basic] = maryBasic;
			actionFrameX[Action::fMove] = maryfMove;
			actionFrameX[Action::bMove] = marybMove;
			actionFrameX[Action::sHand] = marysHand;
			actionFrameX[Action::bHand] = marybHand;
			actionFrameX[Action::sKick] = marysKick;
			actionFrameX[Action::bKick] = marybKick;
			actionFrameX[Action::sHit] = marysHit;
			actionFrameX[Action::bHit] = marybHit;
			actionFrameX[Action::Guard] = maryGuard;
			break;
		case 2: // player2p
			actionFrameX[Action::Basic] = maryBasic_R;
			actionFrameX[Action::fMove] = maryfMove_R;
			actionFrameX[Action::bMove] = marybMove_R;
			actionFrameX[Action::sHand] = marysHand_R;
			actionFrameX[Action::bHand] = marybHand_R;
			actionFrameX[Action::sKick] = marysKick_R;
			actionFrameX[Action::bKick] = marybKick_R;
			actionFrameX[Action::sHit] = marysHit_R;
			actionFrameX[Action::bHit] = marybHit_R;
			actionFrameX[Action::Guard] = maryGuard_R;
			break;
		}

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
	charImg[Action::Guard].ReverseImg();
}


void Character::KeyEvent(char inputKey)
{
	switch (inputKey)
	{
		if (!isMove && !isStatus )
		{
	case VK_RIGHT:		//앞으로
		action = Action::fMove;
		frameX = 0;
		isMove = true;
		break;
	case VK_LEFT:		//뒤로
		action = Action::bMove;
		frameX = 0;
		isMove = true;
		break;
		}
	case 'A':		//강발
		action = Action::bKick;
		hitMotion = HitMotion::Big;
		frameX = 0;
		isMove = false;
		isStatus = true;
		isFire();
		break;
	case 'S':		//약발
		action = Action::sKick;
		hitMotion = HitMotion::Small;
		frameX = 0;
		isMove = false;
		isStatus = true;
		isFire();
		break;
	case 'Q':		//강손
		action = Action::bHand;
		hitMotion = HitMotion::Big;
		frameX = 0;
		isMove = false;
		isStatus = true;
		isFire();
		break;
	case 'W':		//약손
		action = Action::sHand;
		hitMotion = HitMotion::Small;
		frameX = 0;
		isMove = false;
		isStatus = true;
		isFire();
		break;
	case 'Z':		//1피격
		action = Action::sHit;
		frameX = 0;
		isMove = false;
		isStatus = true;
		isHit = false;
		break;
	case 'X':		//2피격
		action = Action::bHit;
		frameX = 0;
		isMove = false;
		isStatus = true;
		break;
		if (!isMove)
		{
	case 'J':		//앞으로
		action = Action::fMove;
		frameX = 0;
		isMove = true;
		break;
	case 'L':		//뒤로
		action = Action::bMove;
		frameX = 0;
		isMove = true;
		break;
		}
	case 'D':		//강발
		action = Action::bKick;
		hitMotion = HitMotion::Big;
		frameX = 0;
		isMove = false;
		isStatus = true;
		isFire();
		break;
	case 'F':		//약발
		action = Action::sKick;
		hitMotion = HitMotion::Small;
		frameX = 0;
		isMove = false;
		isStatus = true;
		isFire();
		break;
	case 'E':		//강손
		action = Action::bHand;
		hitMotion = HitMotion::Big;
		frameX = 0;
		isMove = false;
		isStatus = true;
		isFire();
		break;
	case 'R':		//약손
		action = Action::sHand;
		hitMotion = HitMotion::Small;
		frameX = 0;
		isMove = false;
		isStatus = true;
		isFire();
		break;
	case 'C':		//1피격
		action = Action::sHit;
		frameX = 0;
		isMove = false;
		isStatus = true;
		isHit = false;
		break;
	case 'V':		//2피격
		action = Action::bHit;
		frameX = 0;
		isMove = false;
		isStatus = true;
		break;

	case 0:	//기본자세
		action = Action::Basic;
		break;
	}

}


void Character::SetBodySize()
{
	for (int i = 0; i < maxFrame[action]; i++)
	{
		bodySizeX = actionFrameX[action][frameX + 1] - actionFrameX[action][frameX];
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
			if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT) || isStatus || isHit)
			{
				isMove = false;
				KeyEvent(0);
			}
			pos.x += moveSpeed;
		}break;
		case Action::bMove:
		{
			if (!KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT) || isStatus || isHit)
			{
				isMove = false;
				KeyEvent(0);
			}
			pos.x -= moveSpeed;
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
		}break;
		case Action::bMove:
		{
			if (!KeyManager::GetSingleton()->IsStayKeyDown('L') || isStatus)
			{
				isMove = false;
				KeyEvent(0);
			}
			pos.x += moveSpeed;
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
		if (!isMove)
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
			{
				KeyEvent(VK_RIGHT);
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
			{
				KeyEvent(VK_LEFT);
			}
		}
		if (!isHit)
		{
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
		}
		//if (isHit || KeyManager::GetSingleton()->IsOnceKeyDown('Z'))	//1피격
		//{
		//	KeyEvent('Z');
		//}
		//if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))	//2피격
		//{
		//	KeyEvent('X');
		//}

		break;
	case 2:
		if (!isMove)
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown('J'))
			{
				KeyEvent('J');
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown('L'))
			{
				KeyEvent('L');
			}
		}
		if (!isHit)
		{
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
		}
		//if (isHit || KeyManager::GetSingleton()->IsOnceKeyDown('C'))	//1피격
		//{
		//	KeyEvent('C');
		//}
		//if (KeyManager::GetSingleton()->IsOnceKeyDown('V'))	//2피격
		//{
		//	KeyEvent('V');
		//}

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
		isHit = false;
		if (!isMove)
		{
			KeyEvent(0);
		}
	}
	/*frameX--;
	if (frameX <= 0)
	{
		frameX = maxFrame[action]-1;
		isStatus = false;
		if (!isMove)
		{
			KeyEvent(0);
		}
	}*/
}

void Character::isFire()
{
	hitBox->SetIsAlive(true);
	hitBox->SetPos(pos);
	switch (characterType)
	{
	case CharacterType::Terry:
		switch (action)
		{
		case Action::sHand:
			hitBox->SetMaxFrame(1);
			hitBox->SetMoveSpeed(70);
			hitBox->SetPos({ hitBox->GetPos().x, hitBox->GetPos().y - 70 });
			hitBox->SetHitMotion(hitMotion);
			break;
		case Action::bHand:
			hitBox->SetMaxFrame(1);
			hitBox->SetMoveSpeed(100);
			hitBox->SetPos({ hitBox->GetPos().x, hitBox->GetPos().y - 70 });
			hitBox->SetHitMotion(hitMotion);
			break;
		case Action::sKick:
			hitBox->SetMaxFrame(1);
			hitBox->SetMoveSpeed(130);
			hitBox->SetHitMotion(hitMotion);
			break;
		case Action::bKick:
			hitBox->SetMaxFrame(1);
			hitBox->SetMoveSpeed(100);
			hitBox->SetPos({ hitBox->GetPos().x, hitBox->GetPos().y - 70 });
			hitBox->SetHitMotion(hitMotion);
			break;
		}
		break;
	case CharacterType::Mary:
		switch (action)
		{
		case Action::sHand:
			hitBox->SetMaxFrame(1);
			hitBox->SetMoveSpeed(50);
			hitBox->SetPos({ hitBox->GetPos().x, hitBox->GetPos().y - 55 });
			hitBox->SetHitMotion(hitMotion);
			break;
		case Action::bHand:
			hitBox->SetMaxFrame(1);
			hitBox->SetMoveSpeed(100);
			hitBox->SetPos({ hitBox->GetPos().x, hitBox->GetPos().y - 50 });
			hitBox->SetHitMotion(hitMotion);
			break;
		case Action::sKick:
			hitBox->SetMaxFrame(1);
			hitBox->SetMoveSpeed(40);
			hitBox->SetPos({ hitBox->GetPos().x, hitBox->GetPos().y + 70 });
			hitBox->SetHitMotion(hitMotion);
			break;
		case Action::bKick:
			hitBox->SetMaxFrame(2);
			hitBox->SetMoveSpeed(50);
			hitBox->SetHitMotion(hitMotion);
			break;
		}
		break;
	}

	//ammo->SetIsAlive(true);
			//ammo->SetPos(pos);
			//ammo->SetMoveSpeed(30);
			//ammo->SetTerryFire(true);
			//ammo->SetMaxFrame(2);
}

void Character::IsHit()
{
	frameX = 0;
	isStatus = true;
	isMove = false;
	isHit = false;
	switch (hitMotion)
	{
	case HitMotion::Small:
		action = Action::sHit;
		break;
	case HitMotion::Big:
		action = Action::bHit;
		break;

	case HitMotion::HitGuard:
		action = Action::Guard;
		break;
	}
}

//bool IsGuard()
//{
//	if (action == Action::bMove)
//		return true;
//	else
//		return false;
//}
