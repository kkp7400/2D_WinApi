#pragma once
#include "UIManager.h"
class Image;
class SkillManager;
class UI_Player : public UIManager
{
private:
	Image* statusBar;
	Image* hpBarBack;
	Image* hpBar;
	Image* face;
	Image* skillFrame[4];
	Image* skillimg[4];
	Image* skillCoolTime[4];
	char szText[128];
	float lastHP;
	float nowHP;
	float lastBackHP;
	float hpBackPer;
	float elapsedTime;
	float skillCool[4];
	int coolShadow[4];
	BLENDFUNCTION* blendFunc[6];
	SkillManager* skill;
	int blendValue[4];
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

