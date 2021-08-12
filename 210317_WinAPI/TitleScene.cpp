#include "TitleScene.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT TitleScene::Init()
{
	ImageManager::GetSingleton()->AddImage("타이틀씬", "Image/WOL/mainmenu/title.bmp", 1600*0.9, 900*0.9,1,1,RGB(1, 2, 3));
	ImageManager::GetSingleton()->AddImage("로고", "Image/WOL/mainmenu/logo.bmp", 1600*0.9, 900*0.9, 1, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("스타트", "Image/WOL/mainmenu/pressTheEnterButton.bmp", 322, 20, 1, 1, true, RGB(255, 0, 255));
	logo = ImageManager::GetSingleton()->FindImage("로고");
	titleImage = ImageManager::GetSingleton()->FindImage("타이틀씬");
	start = ImageManager::GetSingleton()->FindImage("스타트");
	//0: 1P	//1: 2P	//2: 맵툴
	selectMode = 0;
	currFrame = 0;
	titleTimer = 0;
	return S_OK;
}

void TitleScene::Release()
{	
}

void TitleScene::Update()
{
	if (selectMode == 0 and KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		SceneManager::GetSingleton()->ChangeScene("전투_1");
	}
}

void TitleScene::Render(HDC hdc)
{	
	titleImage->FrameRender(hdc, 1600 * 0.85/2, 900 * 0.85/2, 0, 0, true);
	logo->FrameRender(hdc, WINSIZE_X/2, WINSIZE_Y / 2, 0, 0,1);
	start->FrameRender(hdc, WINSIZE_X / 2, WINSIZE_Y / 2 + 100, 0, 0, 1);
}
