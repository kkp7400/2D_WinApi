#include "UI.h"
#include "UIManager.h"
#include "UI_Player.h"
#include "Image.h"

HRESULT UI::Init()
{
	uiMgr.resize(2);
	uiMgr[0] = new UI_Player();
	uiMgr[0]->SetPlayer(player);	
	uiMgr[0]->Init();
	
	return S_OK;
}

void UI::Release()
{

}

void UI::Update()
{
	uiMgr[0]->Update();
}

void UI::Render(HDC hdc)
{
	uiMgr[0]->Render(hdc);
}