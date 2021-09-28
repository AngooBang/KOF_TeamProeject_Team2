#include "SelectScene.h"
#include "Image.h"
#include "SelectIcon.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "FightScene.h"

void SelectScene::Init()
{

	selectBackground = new Image;

	selectCharframe = new Image;

	charProfile = new Image[4];

	charProfile[0].Init("Image/SelectCharacterImage/TerryProfile.bmp", 150, 171, true, RGB(89, 177, 77));
	charProfile[1].Init("Image/SelectCharacterImage/MarryProfile.bmp", 150, 171, true, RGB(89, 177, 77));
	charProfile[2].Init("Image/SelectCharacterImage/KyoProfile.bmp", 150, 171, true, RGB(89, 177, 77));
	charProfile[3].Init("Image/SelectCharacterImage/IoriProfile.bmp", 150, 171, true, RGB(89, 177, 77));

	
	selectBackground->Init("Image/SelectCharacterImage/SelectCharBackground.bmp", 1200, 800, true, RGB(89, 177, 77));
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
		selectCharframe->Render(hdc, 360 + (160 * i), 600);
		charProfile[i].Render(hdc, 365 + (160 * i), 600);
	}

	iconP1->Render(hdc);
	iconP2->Render(hdc);
}

void SelectScene::Release()
{
	SAFE_RELEASE(charProfile);

	SAFE_RELEASE(iconP1);
	SAFE_RELEASE(iconP2);
	SAFE_RELEASE(selectCharframe);
	SAFE_RELEASE(selectBackground);
}
