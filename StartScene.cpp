#include "StartScene.h"
#include "Image.h"
#include "SceneManager.h"
#include "KeyManager.h"

void StartScene::Init()
{
	//인트로 바탕, 검은색 프레임
	introImage[0] = new Image;
	introImage[0]->Init("Image/intro/introbackground.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	introImage[1] = new Image;
	introImage[1]->Init("Image/intro/introbackground2.bmp", WIN_SIZE_X, 150);

	//인트로1 캐릭터 걷는 장면
	introImage[2] = new Image;
	introImage[2]->Init("Image/intro/intro_1/intro_walking.bmp", 3200, 700, 8, 1, true, RGB(255, 0, 255));

	introImage[3] = new Image;
	introImage[3]->Init("Image/intro/intro_1/intro_words.bmp", 1800, 300, 4, 3, true, RGB(44, 106, 63));

	introImage[4] = new Image;
	introImage[4]->Init("Image/intro/intro_1/walking_background.bmp", WIN_SIZE_X * 5, 600, 3, 1, true, RGB(255, 0, 255));

	//인트로1 캐릭터 이동 후 이미지
	introImage[5] = new Image;
	introImage[5]->Init("Image/intro/intro_2/walking_after_1.bmp", 400, WIN_SIZE_Y, true, RGB(255, 0, 255));

	introImage[6] = new Image;
	introImage[6]->Init("Image/intro/intro_2/walking_after_2.bmp", WIN_SIZE_X * 3, 600, 3, 2, true, RGB(255, 0, 255));

	//episode 6 문구
	introImage[7] = new Image;
	introImage[7]->Init("Image/intro/intro_3/episode_6.bmp", 1400, 100, 6, 1, true, RGB(255, 0, 255));

	introImage[8] = new Image;
	introImage[8]->Init("Image/intro/intro_3/episode_after.bmp", WIN_SIZE_X * 3, 1200, 3, 2, true, RGB(255, 0, 255));

	//캐릭터 화면 발차기
	introImage[9] = new Image;
	introImage[9]->Init("Image/intro/intro_4/logo_after_1.bmp", WIN_SIZE_X * 3, 600, 3, 1, true, RGB(255, 0, 255));

	introImage[10] = new Image;
	introImage[10]->Init("Image/intro/intro_4/logo_after_2.bmp", WIN_SIZE_X / 2, 200, true, RGB(255, 0, 255));

	introImage[11] = new Image;
	introImage[11]->Init("Image/intro/intro_4/kick_background.bmp", WIN_SIZE_X * 4, WIN_SIZE_Y * 3, 4, 4, true, RGB(255, 0, 255));

	introImage[12] = new Image;
	introImage[12]->Init("Image/intro/intro_4/intro_kick_ready.bmp", WIN_SIZE_X * 3, 600, 6, 1, true, RGB(255, 0, 255));

	introImage[13] = new Image;
	introImage[13]->Init("Image/intro/intro_4/intro_kick.bmp", WIN_SIZE_X * 3, 1200, 3, 2, true, RGB(255, 0, 255));

	//게임 시작 대기 화면
	introImage[14] = new Image;
	introImage[14]->Init("Image/intro/game_logo.bmp", WIN_SIZE_X - 200, WIN_SIZE_Y / 3, true, RGB(32, 80, 48));

	introImage[15] = new Image;
	introImage[15]->Init("Image/intro/2000_SNK.bmp", WIN_SIZE_X - 300, WIN_SIZE_Y / 5, true, RGB(0, 0, 0));

	introBackground2PosX = WIN_SIZE_X / 2;
	introBackground2PosY = WIN_SIZE_Y - 75;
	intro1WalkingMotionFrameX = 0;
	intro1WalkingMotionPosX = WIN_SIZE_X - 200;
	intro1TiltleWordFrameX, intro1TiltleWordFrameY = 0;
	intro1TiltleWordPosX = 300;
	intro1WallPosX = -(WIN_SIZE_X * 5) / 2 + 1200;
	intro2HorizontalImgPosY = WIN_SIZE_Y + (WIN_SIZE_Y / 2);
	intro2VerticalImgPosY = WIN_SIZE_Y / 4;
	Intro2Img2FmX, Intro2Img2FmY = 0;
	intro3EpisodeWordFrmX = 0;
	intro3EpisodeImgFrmX, intro3EpisodeImgFrmY = 0;
	intro4StepImgFrmX = 0;
	intro4BackgroundFrmX, intro4BackgroundFrmY = 0;
	intro4KickReadyMotionFrmX = 0;
	intro4KickMotionFrmX, intro4KickMotionFrmY = 0;

	elapsedCount1 = 0;
	elapsedCount2 = 0;
	elapsedCount3 = 0;
	elapsedCount4 = 0;

	showIntro = true;
	gameStart = false;
}

void StartScene::Update()
{
	elapsedCount1++;

	if (elapsedCount1 == 2)
	{
		intro1WalkingMotionFrameX++;
		if (intro1TiltleWordFrameX < 3 && intro1TiltleWordFrameY < 3)
		{
			intro1TiltleWordFrameX++;
		}
		if (intro1TiltleWordFrameX == 3 && intro1TiltleWordFrameY != 2)
		{
			intro1TiltleWordFrameX = 0;
			intro1TiltleWordFrameY++;
		}
		if (intro1TiltleWordFrameX == 3 && intro1TiltleWordFrameY == 2)
		{
			intro1TiltleWordFrameX = 3;
			intro1TiltleWordFrameY = 2;
		}
		if (intro1WalkingMotionFrameX == 8)
		{
			intro1WalkingMotionFrameX = 0;
		}
		if (elapsedCount2 > 100)
		{
			intro3EpisodeWordFrmX++;
		}
		if (elapsedCount2 > 195)
		{
			intro4KickReadyMotionFrmX++;
		}
		if (elapsedCount2 > 207)
		{
			if (intro4KickMotionFrmX != 2)
			{
				intro4KickMotionFrmX++;
			}
			if (intro4KickMotionFrmX == 2 && intro4KickMotionFrmY != 1)
			{
				intro4KickMotionFrmY++;
				intro4KickMotionFrmX = 0;
			}
		}
		elapsedCount1 = 0;
	}


	elapsedCount2++;
	if (elapsedCount2 <= 50)intro1WallPosX += 100;
	if (elapsedCount2 > 50)intro1WallPosX += 200;

	if (elapsedCount2 > 50)
	{
		if (introBackground2PosY < WIN_SIZE_Y + 75) introBackground2PosY += 30;
		if (intro1WalkingMotionPosX > 300) intro1WalkingMotionPosX -= 150;
	}

	if (elapsedCount2 == 18)
	{
		intro1TiltleWordFrameX = 3;
		intro1TiltleWordFrameY = 2;
	}
	if (elapsedCount2 > 20)
	{
		intro1TiltleWordFrameX += 100;
	}
	if (elapsedCount2 > 55)
	{
		if (intro2HorizontalImgPosY > WIN_SIZE_Y / 2)
		{
			intro2HorizontalImgPosY -= 200;
		}
	}
	if (elapsedCount2 > 63 && !(intro2HorizontalImgPosY > WIN_SIZE_Y / 2))
	{
		intro2HorizontalImgPosY -= 200;
	}

	if (elapsedCount2 > 117)
	{
		elapsedCount3++;
		if (elapsedCount3 == 10)
		{
			intro3EpisodeImgFrmX++;
			if (intro3EpisodeImgFrmX == 3 && intro3EpisodeImgFrmY != 1)
			{
				intro3EpisodeImgFrmY++;
				intro3EpisodeImgFrmX = 0;
			}
			elapsedCount3 = 0;
		}
	}
	if (elapsedCount2 > 182)
	{
		elapsedCount4++;
		if (elapsedCount4 == 3)
		{
			if (intro4StepImgFrmX != 2)
			{
				intro4StepImgFrmX++;
			}
			if (intro4BackgroundFrmX != 3)
			{
				intro4BackgroundFrmX++;
			}
			if (intro4BackgroundFrmX == 3 && intro4BackgroundFrmY != 3)
			{
				intro4BackgroundFrmY++;
				intro4BackgroundFrmX = 0;
			}
			elapsedCount4 = 0;
		}
	}
	if (elapsedCount2 > 230)showIntro = false;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_TAB)) showIntro = false;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_F5)) gameStart = true;

	if (gameStart)
		SceneManager::GetSingleton()->ChangeScene(E_SCENE_SELECT);

}

void StartScene::Render(HDC hdc)
{
	if (showIntro)
	{
		if (introImage[0]) introImage[0]->Render(hdc);

		if (introImage[4]) introImage[4]->Render(hdc, intro1WallPosX, WIN_SIZE_Y / 2);
		if (introImage[3]) introImage[3]->Render(hdc, intro1TiltleWordPosX, WIN_SIZE_Y / 2, intro1TiltleWordFrameX, intro1TiltleWordFrameY);

		if (elapsedCount2 > 65) introImage[6]->Render(hdc, WIN_SIZE_X / 2, intro2VerticalImgPosY, 0, 0);
		if (elapsedCount2 > 70) introImage[6]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y - intro2VerticalImgPosY, 0, 1);
		if (elapsedCount2 > 75) introImage[6]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2 - intro2VerticalImgPosY / 2, 1, 0);
		if (elapsedCount2 > 80) introImage[6]->Render(hdc, WIN_SIZE_X / 2, intro2VerticalImgPosY / 2, 1, 1);
		if (elapsedCount2 > 85) introImage[6]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 2, 0);

		if (introImage[2]) introImage[2]->Render(hdc, intro1WalkingMotionPosX, WIN_SIZE_Y - 350, intro1WalkingMotionFrameX, 0);
		if (introImage[1]) introImage[1]->Render(hdc, introBackground2PosX, introBackground2PosY);

		if (elapsedCount2 > 55) introImage[5]->Render(hdc, WIN_SIZE_X - 300, intro2HorizontalImgPosY);

		if (elapsedCount2 > 95) introImage[0]->Render(hdc);

		if (elapsedCount2 > 100) introImage[7]->Render(hdc, WIN_SIZE_X - 300, WIN_SIZE_Y / 2, intro3EpisodeWordFrmX, 0);
		if (elapsedCount2 > 117) introImage[8]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, intro3EpisodeImgFrmX, intro3EpisodeImgFrmY);

		if (elapsedCount2 > 180) introImage[0]->Render(hdc);

		if (elapsedCount2 > 182) introImage[9]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, intro4StepImgFrmX, 0);
		if (elapsedCount2 > 190) introImage[10]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		if (elapsedCount2 > 195) introImage[11]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, intro4BackgroundFrmX, intro4BackgroundFrmY);
		if (elapsedCount2 > 195) introImage[12]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, intro4KickReadyMotionFrmX, 0);
		if (elapsedCount2 > 207) introImage[13]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, intro4KickMotionFrmX, intro4KickMotionFrmY);
	}
	if (showIntro == false && gameStart == false)
	{
		introImage[0]->Render(hdc);
		introImage[14]->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		introImage[15]->Render(hdc, WIN_SIZE_X / 2 - 100, WIN_SIZE_Y - 100);
	}
}

void StartScene::Release()
{
	SAFE_RELEASE(introImage[0]);
	SAFE_RELEASE(introImage[1]);
	SAFE_RELEASE(introImage[4]);
	SAFE_RELEASE(introImage[3]);
	SAFE_RELEASE(introImage[2]);
	SAFE_RELEASE(introImage[5]);
	SAFE_RELEASE(introImage[6]);
	SAFE_RELEASE(introImage[7]);
	SAFE_RELEASE(introImage[8]);
	SAFE_RELEASE(introImage[9]);
	SAFE_RELEASE(introImage[10]);
	SAFE_RELEASE(introImage[11]);
	SAFE_RELEASE(introImage[12]);
	SAFE_RELEASE(introImage[13]);
	SAFE_RELEASE(introImage[14]);
	SAFE_RELEASE(introImage[15]);
}
