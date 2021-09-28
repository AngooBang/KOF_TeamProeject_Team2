#include "SelectIcon.h"
#include "KeyManager.h"
#include "Image.h"

void SelectIcon::Init()
{
	icon = new Image();

	icon->Init("Image/SelectCharacterImage/Icon.bmp", 159 * 5, 49 * 5, 4, 1, true, RGB(240, 0, 240));
	frameXDataInput[0] = 0;
	frameXDataInput[1] = 40 * 5;
	frameXDataInput[2] = 80 * 5;
	frameXDataInput[3] = 120 * 5;
	frameXDataInput[4] = 159 * 5;

	characterType = CharacterType::CharEnd;

	switch (playerNum)
	{
	case 1:
		frameX = 0;
		pos.x = 365;
		break;
	case 2:
		pos.x = 365 + (160 * 3);
		frameX = 2;
		break;
	}
	frameY = 0;
	pos.y = 585;
	isSelect = false;

	elapsedCount = 0;
	frameXData = frameXDataInput;



}

void SelectIcon::Update()
{
	if (isSelect) return;


	elapsedCount++;
	if (elapsedCount == 5)
	{
		switch (playerNum)
		{
		case 1:
			frameX == 0 ? frameX = 1 : frameX = 0;
			break;
		case 2:
			frameX == 2 ? frameX = 3 : frameX = 2;
			break;
		}

		elapsedCount = 0;
	}


	switch (playerNum)
	{
	case 1:
		if (KeyManager().GetSingleton()->IsOnceKeyDown(VK_LEFT))
		{
			InputLeft();
			if (characterType == target->GetCharacterType())
				InputLeft();
		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown(VK_RIGHT))
		{
			InputRight();
			if (characterType == target->GetCharacterType())
				InputRight();
		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown('A'))
		{
			if (characterType == CharacterType::Kyo || characterType == CharacterType::Iori)
			{

			}
			else
			{
				frameX = 1;
				isSelect = true;
			}
		}
		break;
	case 2:
		if (KeyManager().GetSingleton()->IsOnceKeyDown('J'))
		{
			InputLeft();
			if (characterType == target->GetCharacterType())
				InputLeft();
		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown('L'))
		{
			InputRight();
			if (characterType == target->GetCharacterType())
				InputRight();
		}
		if (KeyManager().GetSingleton()->IsOnceKeyDown('D'))
		{
			if (characterType == CharacterType::Kyo || characterType == CharacterType::Iori)
			{

			}
			else
			{
				frameX = 3;
				isSelect = true;
			}
		}
		break;
	}


	SetPosFromCharType();
}

void SelectIcon::Render(HDC hdc)
{
	icon->Render(hdc, pos.x, pos.y, frameX, frameY, frameXData);
}

void SelectIcon::Release()
{
	SAFE_RELEASE(icon);
}

void SelectIcon::SetPosFromCharType()
{
	switch (characterType)
	{
	case CharacterType::Terry:
		pos.x = 365;
		break;
	case CharacterType::Mary:
		pos.x = 365 + 160;
		break;
	case CharacterType::Kyo:
		pos.x = 365 + (160 * 2);
		break;
	case CharacterType::Iori:
		pos.x = 365 + (160 * 3);
		break;
	}
}

void SelectIcon::InputLeft()
{
	switch (characterType)
	{
	case CharacterType::Terry:
		characterType = CharacterType::Iori;
		break;
	case CharacterType::Mary:
		characterType = CharacterType::Terry;
		break;
	case CharacterType::Kyo:
		characterType = CharacterType::Mary;
		break;
	case CharacterType::Iori:
		characterType = CharacterType::Kyo;
		break;
	}
}

void SelectIcon::InputRight()
{
	switch (characterType)
	{
	case CharacterType::Terry:
		characterType = CharacterType::Mary;
		break;
	case CharacterType::Mary:
		characterType = CharacterType::Kyo;
		break;
	case CharacterType::Kyo:
		characterType = CharacterType::Iori;
		break;
	case CharacterType::Iori:
		characterType = CharacterType::Terry;
		break;
	}
}
