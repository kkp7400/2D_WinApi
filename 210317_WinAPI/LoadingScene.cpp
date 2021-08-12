#include "LoadingScene.h"
#include "Image.h"

HRESULT LoadingScene::Init()
{
    bg = ImageManager::GetSingleton()->AddImage("로딩화면1", "Image/loading.bmp",
        WINSIZE_X, WINSIZE_Y);

    return S_OK;
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
}

void LoadingScene::Render(HDC hdc)
{
    if (bg)
    {
        bg->Render(hdc);
    }
}
