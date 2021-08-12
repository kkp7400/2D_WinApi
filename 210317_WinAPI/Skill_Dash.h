#pragma once
#include"SkillManager.h"

class Skill_Dash : public SkillManager
{
private:
	Image* fireDashImage;
	bool isDashStop;
	POINT currFrame;
	float moveSpeed = 0;
	FPOINT clientPos;
	FPOINT pos;
	float frameSpeed;
	float moveframespeed;
	
public:
	virtual HRESULT Init(Player* player);
	virtual void Release();
	virtual void Update(Player* player);
	virtual void Render(HDC hdc, Player* player);
	virtual void Skill(Player* player);
	virtual vector<RECT>* GetAtkCol() { return nullptr; }
};
