#include "UI_Player.h"
#include "Player.h"
#include "CommonFunction.h"
#include "Image.h"
#include "SkillManager.h"
HRESULT UI_Player::Init()
{
	ImageManager::GetSingleton()->AddImage("�������ͽ���", "Image/WOL/UIs/playerStatus/playerStatusBar2.bmp", 271, 66, 1, 1, true, RGB(255, 0, 255));
	statusBar = ImageManager::GetSingleton()->FindImage("�������ͽ���");
	ImageManager::GetSingleton()->AddImage("ü�¹�", "Image/WOL/UIs/playerStatus/playerHpBar.bmp", 201, 26, 1, 1, true, RGB(255, 0, 255));
	hpBar = ImageManager::GetSingleton()->FindImage("ü�¹�");
	ImageManager::GetSingleton()->AddImage("ü�¹ٵ�", "Image/WOL/UIs/playerStatus/playerHpBackBar.bmp", 201, 26, 1, 1, true, RGB(255, 0, 255));
	hpBarBack = ImageManager::GetSingleton()->FindImage("ü�¹ٵ�");
	ImageManager::GetSingleton()->AddImage("��", "Image/WOL/UIs/playerStatus/playerPortrait.bmp", 53, 54, 1, 1, true, RGB(255, 255, 255));
	face = ImageManager::GetSingleton()->FindImage("��");
	ImageManager::GetSingleton()->AddImage("������", "Image/WOL/UIs/skillUI/skillIconFrame.bmp", 120, 60, 2, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("��ų", "Image/WOL/UIs/skillIcons/Skills.bmp", 256, 256, 16, 16, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("��Ÿ��", "Image/WOL/UIs/skillIcons/��Ÿ��5.bmp", 30000 * 0.1, 600 * 0.1, 50, 1, false, RGB(255, 255, 255));
	for (int i = 0; i < 4; i++)
	{
		skillFrame[i] = ImageManager::GetSingleton()->FindImage("������");
		skillimg[i] = ImageManager::GetSingleton()->FindImage("��ų");
		skillCoolTime[i] = ImageManager::GetSingleton()->FindImage("��Ÿ��");
		coolShadow[i] = 0;
		blendValue[i] = 0;
	}
	lastHP = player->GetMaxHP();
	nowHP = player->GetMaxHP();
	lastBackHP = player->GetMaxHP();
	elapsedTime = 0.0f;

	return S_OK;
}

void UI_Player::Release()
{


}

void UI_Player::Update()
{

	skillCool[0] = player->GetSkillMgr0()->GetCoolTime();//���̾�뽬	
	skillCool[1] = player->GetSkillMgr2()->GetCoolTime();//��
	skillCool[2] = player->GetSkillMgr4()->GetCoolTime();//���̽�

	elapsedTime += TimerManager::GetSingleton()->GetElapsedTime();

	nowHP = player->GetNowHP();

	if (lastBackHP != nowHP)
	{
		if (elapsedTime > 0.01f)
		{
			if(lastBackHP- nowHP>=0)
			lastBackHP -= 100;
			elapsedTime = 0.0f;
		}
	}

	coolShadow[0] = skillCool[0] * 10;
	coolShadow[1] = skillCool[1] * 10;
	coolShadow[2] = skillCool[2] * 10;

}

void UI_Player::Render(HDC hdc)
{
	statusBar->Render(hdc, 30, 30);
	hpBarBack->Render3(hdc, 93, 40, 0, player->GetMaxHP(), lastBackHP);
	hpBar->Render3(hdc, 93, 40, 0, player->GetMaxHP(), nowHP);
	face->Render(hdc, 37, 37);

	skillFrame[0]->FrameRender(hdc, 20, WINSIZE_Y - 80, 0, 0);
	skillFrame[1]->FrameRender(hdc, 100, WINSIZE_Y - 80, blendValue[0],0 );
	skillFrame[2]->FrameRender(hdc, 180, WINSIZE_Y - 80, blendValue[1],0 );
	skillFrame[3]->FrameRender(hdc, 260, WINSIZE_Y - 80, blendValue[2],0);

	skillimg[0]->FrameRender(hdc, 20+5, WINSIZE_Y - 80+5, 0, 4, 0, 3);//�������
	skillimg[1]->FrameRender(hdc, 100+5, WINSIZE_Y - 80+5, 4, 0, 0, 3);//���̾�뽬
	skillimg[2]->FrameRender(hdc, 180+5, WINSIZE_Y - 80+5, 15, 8, 0, 3);//�����ο�
	skillimg[3]->FrameRender(hdc, 260+5, WINSIZE_Y - 80+5, 0, 2, 0, 3);//���̽�ũ����Ż

	if (skillCool[0] > 0)
	{
		skillCoolTime[0]->AlphaRender2(hdc, 100, WINSIZE_Y - 80, 0, (int)coolShadow[0], 1);
		blendFunc[0] = skillCoolTime[0]->GetBlendFunc();
		blendFunc[0]->SourceConstantAlpha = 150;
		blendValue[0] = 0;
	}
	else blendValue[0] = 1;
	if (skillCool[1] > 0)
	{
		skillCoolTime[1]->AlphaRender2(hdc, 180, WINSIZE_Y - 80, 0, (int)coolShadow[1], 1);
		blendFunc[1] = skillCoolTime[1]->GetBlendFunc();
		blendFunc[1]->SourceConstantAlpha = 150;
		blendValue[1] = 0;
	}
	else blendValue[1] = 1;
	if (skillCool[2] > 0)
	{
		skillCoolTime[2]->AlphaRender2(hdc, 260, WINSIZE_Y - 80, 0, (int)coolShadow[2], 1);
		blendFunc[2] = skillCoolTime[2]->GetBlendFunc();
		blendFunc[2]->SourceConstantAlpha = 150;
		blendValue[2] = 0;
	}
	else blendValue[2] = 1;

	
	

	//wsprintf(szText, "rockCool: %d", (int)skillCool[1]);
	//TextOut(hdc, 1000, 60, szText, strlen(szText));
}
