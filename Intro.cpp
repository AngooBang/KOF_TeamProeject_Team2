#include "intro.h"
#include "Image.h"
#include "KeyManager.h"

void Intro::Init()
{
	//인트로 바탕, 검은색 프레임
	IntroBackground1 = new Image;
	IntroBackground1->Init("Image/intro/introbackground.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	IntroBackground2 = new Image;
	IntroBackground2->Init("Image/intro/introbackground2.bmp", WIN_SIZE_X, 150);

	//인트로1 캐릭터 걷는 장면
	IntroWalking = new Image;
	IntroWalking->Init("Image/intro/intro_1/intro_walking.bmp", 3200, 700, 8, 1, true, RGB(255, 0, 255));

	WalkingWord = new Image;
	WalkingWord->Init("Image/intro/intro_1/intro_words.bmp", 1800, 300, 4, 3, true, RGB(44, 106, 63));

	Wall = new Image;
	Wall->Init("Image/intro/intro_1/walking_background.bmp", WIN_SIZE_X * 5, 600, 3, 1, true, RGB(255, 0, 255));

	//인트로1 캐릭터 이동 후 이미지
	Intro2Img1 = new Image;
	Intro2Img1->Init("Image/intro/intro_2/walking_after_1.bmp", 400, WIN_SIZE_Y, true, RGB(255, 0, 255));

	Intro2Img2 = new Image;
	Intro2Img2->Init("Image/intro/intro_2/walking_after_2.bmp", WIN_SIZE_X * 3, 600, 3, 2, true, RGB(255, 0, 255));

	//episode 6 문구
	Episode = new Image;
	Episode->Init("Image/intro/intro_3/episode_6.bmp",1400, 100, 6, 1, true, RGB(255, 0, 255));

	EpisodeImg = new Image;
	EpisodeImg->Init("Image/intro/intro_3/episode_after.bmp", WIN_SIZE_X * 3, 1200, 3, 2, true, RGB(255, 0, 255));

	//캐릭터 화면 발차기
	Intro4Img1 = new Image;
	Intro4Img1->Init("Image/intro/intro_4/logo_after_1.bmp", WIN_SIZE_X * 3, 600, 3, 1, true, RGB(255, 0, 255));

	Intro4Img2 = new Image;
	Intro4Img2->Init("Image/intro/intro_4/logo_after_2.bmp", WIN_SIZE_X/2, 200, true, RGB(255, 0, 255));

	Intro4Img3 = new Image;
	Intro4Img3->Init("Image/intro/intro_4/kick_background.bmp", WIN_SIZE_X * 4, WIN_SIZE_Y * 3, 4, 4, true, RGB(255, 0, 255));

	Intro4Img4 = new Image;
	Intro4Img4->Init("Image/intro/intro_4/intro_kick_ready.bmp", WIN_SIZE_X * 3, 600, 6, 1, true, RGB(255, 0, 255));

	Intro4Img5 = new Image;
	Intro4Img5->Init("Image/intro/intro_4/intro_kick.bmp", WIN_SIZE_X * 3, 1200, 3, 2, true, RGB(255, 0, 255));

	//게임 시작 대기 화면
	GameLogo1 = new Image;
	GameLogo1->Init("Image/intro/game_logo.bmp", WIN_SIZE_X - 200, WIN_SIZE_Y / 3, true, RGB(32, 80, 48));

	GameLogo2 = new Image;
	GameLogo2->Init("Image/intro/2000_SNK.bmp", WIN_SIZE_X - 300, WIN_SIZE_Y / 5, true, RGB(0, 0, 0));

	blackPosX = WIN_SIZE_X / 2;
	blackPosY = WIN_SIZE_Y - 75;
	walkFrameX, walkFrameY = 0;
	walkPosX = WIN_SIZE_X - 200;
	wordFrameX, wordFrameY = 0;
	wordPosX = 300;
	wallPosX = -(WIN_SIZE_X * 5)/2 + 1200;
	intro2PosY1 = WIN_SIZE_Y + (WIN_SIZE_Y / 2);
	intro2PosY2 = WIN_SIZE_Y / 4;
	Intro2Img2FmX, Intro2Img2FmY = 0;
	intro2PosX2 = WIN_SIZE_X / 2;
	episodeFrmX = 0;
	episodeImgX, episodeImgY = 0;
	Intro4Img1X = 0;
	Intro4Img3X, Intro4Img3Y = 0;
	Intro4Img4X = 0;
	Intro4Img5X, Intro4Img5Y = 0;

	elapsedCount1 = 0;
	elapsedCount2 = 0;
	elapsedCount3 = 0;
	elapsedCount4 = 0;

	showIntro = true;
	gameStart = false;
}
void Intro::Update()
{
	elapsedCount1++;

	if (elapsedCount1 == 2)
	{
		walkFrameX++;
		if (wordFrameX < 3 && wordFrameY < 3)
		{
			wordFrameX++;
		}
		if (wordFrameX == 3 && wordFrameY != 2)
		{
			wordFrameX = 0;
			wordFrameY++;
		}
		if (wordFrameX == 3 && wordFrameY == 2)
		{
			wordFrameX = 3;
			wordFrameY = 2;
		}
		if (walkFrameX == 8)
		{
			walkFrameX = 0;
		}
		if (elapsedCount2 > 100)
		{
			episodeFrmX++;
		}
		if (elapsedCount2 > 195)
		{
			Intro4Img4X++;
		}
		if (elapsedCount2 > 207)
		{
			if (Intro4Img5X != 2)
			{
				Intro4Img5X++;
			}
			if (Intro4Img5X == 2 && Intro4Img5Y != 1)
			{
				Intro4Img5Y++;
				Intro4Img5X = 0;
			}
		}
		elapsedCount1 = 0;
		
	}


	elapsedCount2++;
	if (elapsedCount2 <= 50)wallPosX += 100;
	if (elapsedCount2 > 50)wallPosX += 200;
	
	if (elapsedCount2 > 50)
	{
		if(blackPosY < WIN_SIZE_Y + 75)
		blackPosY += 30;
		if(walkPosX > 300)
		walkPosX -= 150;
	}

	if (elapsedCount2 == 18)
	{
		wordFrameX = 3;
		wordFrameY = 2;
	}
	if (elapsedCount2 > 20)
	{
		wordPosX += 100;
	}
	if (elapsedCount2 > 55)
	{
		if (intro2PosY1 > WIN_SIZE_Y / 2)
		{
			intro2PosY1 -= 200;
		}
	}
	if (elapsedCount2 > 63 && !(intro2PosY1 > WIN_SIZE_Y / 2))
	{
		intro2PosY1 -= 200;
	}

	if (elapsedCount2 > 117)
	{
		elapsedCount3++;
		if (elapsedCount3 == 10)
		{
			episodeImgX++;
			if (episodeImgX == 3 && episodeImgY != 1)
			{
				episodeImgY++;
				episodeImgX = 0;
			}
			elapsedCount3 = 0;
		}
	}
	if (elapsedCount2 > 182)
	{
		elapsedCount4++;
		if (elapsedCount4 == 3)
		{
			if (Intro4Img1X != 2)
			{
				Intro4Img1X++;
			}
			if (Intro4Img3X != 3)
			{
				Intro4Img3X++;
			}
			if (Intro4Img3X == 3 && Intro4Img3Y != 3)
			{
				Intro4Img3Y++;
				Intro4Img3X = 0;
			}
			elapsedCount4 = 0;
		}
	}
	if (elapsedCount2 > 230)showIntro = false;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_TAB)) showIntro = false;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_F5)) gameStart = true;
}

void Intro::Render(HDC hdc)
{
	if (showIntro)
	{
		if (IntroBackground1)IntroBackground1->Render(hdc);
		if (Wall)Wall->Render(hdc, wallPosX, WIN_SIZE_Y / 2);
		if (WalkingWord)WalkingWord->Render(hdc, wordPosX, WIN_SIZE_Y / 2, wordFrameX, wordFrameY);

		if (elapsedCount2 > 65)Intro2Img2->Render(hdc, intro2PosX2, intro2PosY2, 0, 0);
		if (elapsedCount2 > 70)Intro2Img2->Render(hdc, intro2PosX2, WIN_SIZE_Y - intro2PosY2, 0, 1);
		if (elapsedCount2 > 75)Intro2Img2->Render(hdc, intro2PosX2, WIN_SIZE_Y / 2 - intro2PosY2 / 2, 1, 0);
		if (elapsedCount2 > 80)Intro2Img2->Render(hdc, intro2PosX2, intro2PosY2 / 2, 1, 1);
		if (elapsedCount2 > 85)Intro2Img2->Render(hdc, intro2PosX2, WIN_SIZE_Y / 2, 2, 0);

		if (IntroWalking)IntroWalking->Render(hdc, walkPosX, WIN_SIZE_Y - 350, walkFrameX, walkFrameY);
		if (IntroBackground2)IntroBackground2->Render(hdc, blackPosX, blackPosY);

		if (elapsedCount2 > 55)Intro2Img1->Render(hdc, WIN_SIZE_X - 300, intro2PosY1);

		if (elapsedCount2 > 95)IntroBackground1->Render(hdc);

		if (elapsedCount2 > 100)Episode->Render(hdc, WIN_SIZE_X - 300, WIN_SIZE_Y / 2, episodeFrmX, 0);
		if (elapsedCount2 > 117)EpisodeImg->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, episodeImgX, episodeImgY);

		if (elapsedCount2 > 180)IntroBackground1->Render(hdc);

		if (elapsedCount2 > 182)Intro4Img1->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, Intro4Img1X, 0);
		if (elapsedCount2 > 190)Intro4Img2->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		if (elapsedCount2 > 195)Intro4Img3->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, Intro4Img3X, Intro4Img3Y);
		if (elapsedCount2 > 195)Intro4Img4->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, Intro4Img4X, 0);
		if (elapsedCount2 > 207)Intro4Img5->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, Intro4Img5X, Intro4Img5Y);
	}
	if (showIntro == false && gameStart == false)
	{
		IntroBackground1->Render(hdc);
		GameLogo1->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		GameLogo2->Render(hdc, WIN_SIZE_X / 2 - 100, WIN_SIZE_Y - 100);
	}
	
}

void Intro::Release()
{
	SAFE_RELEASE(IntroBackground1);
	SAFE_RELEASE(Wall);
	SAFE_RELEASE(WalkingWord);
	SAFE_RELEASE(Intro2Img2);
	SAFE_RELEASE(IntroWalking);
	SAFE_RELEASE(IntroBackground2);
	SAFE_RELEASE(Intro2Img1);
	SAFE_RELEASE(Episode);
	SAFE_RELEASE(EpisodeImg);
	SAFE_RELEASE(Intro4Img1);
	SAFE_RELEASE(Intro4Img2);
	SAFE_RELEASE(Intro4Img3);
	SAFE_RELEASE(Intro4Img4);
	SAFE_RELEASE(Intro4Img5);
	SAFE_RELEASE(GameLogo1);
	SAFE_RELEASE(GameLogo2);

}
