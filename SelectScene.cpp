#include "SelectScene.h"
#include "Image.h"
#include "SelectIcon.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "FightScene.h"

void SelectScene::Init()
{

	selectBackground = new Image;
	selectChar1 = new Image;
	selectChar2 = new Image;
	selectCharframe = new Image;
	
	selectBackground->Init("Image/SelectCharacterImage/SelectCharBackground.bmp", 1200, 800, true, RGB(89, 177, 77));
	selectChar1->Init("Image/SelectCharacterImage/TerryProfile.bmp", 158, 171, true, RGB(89, 177, 77));
	selectChar2->Init("Image/SelectCharacterImage/MarryProfile.bmp", 150, 171, true, RGB(89, 177, 77));
	selectCharframe->Init("Image/SelectCharacterImage/SelectCharFrame.bmp", 149, 172);

	iconP1 = new SelectIcon();
	iconP2 = new SelectIcon();

	iconP1->SetPlayerNum(1);
	iconP2->SetPlayerNum(2);

	iconP1->Init();
	iconP2->Init();

	iconP1->SetCharacterType(CharacterType::Terry);
	iconP2->SetCharacterType(CharacterType::Mary);
	iconP1->SetTarget(iconP2);
	iconP2->SetTarget(iconP1);

	elapsedtCount = 0;
}

void SelectScene::Update()
{
	iconP1->Update();
	iconP2->Update();

	if (iconP1->GetIsSelect() && iconP2->GetIsSelect())
	{
		fightScene->SetCharType(iconP1->GetCharacterType(), 1);
		fightScene->SetCharType(iconP2->GetCharacterType(), 2);
		SceneManager::GetSingleton()->ChangeScene(E_SCENE_FIGHT);
	}
}

void SelectScene::Render(HDC hdc)
{

	selectBackground->Render(hdc);
	for (int i = 0; i < 4; i++)
	{
		selectCharframe->Render(hdc, 360 + (i * 160), 600);
	}

	selectChar1->Render(hdc, 365, 600);
	selectChar2->Render(hdc, 365 + 160, 600);

	iconP1->Render(hdc);
	iconP2->Render(hdc);
}

void SelectScene::Release()
{
	SAFE_RELEASE(iconP1);
	SAFE_RELEASE(iconP2);
	SAFE_RELEASE(selectChar1);
	SAFE_RELEASE(selectChar2);
	SAFE_RELEASE(selectCharframe);
	SAFE_RELEASE(selectBackground);
}
