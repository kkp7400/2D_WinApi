#pragma once
#include"SkillManager.h"

class Image;
class Skill_FireDash:public SkillManager
{
private:
	Image* fireDashImage;
	bool isDashStop;
	bool isDashPos[5];
	bool isDashFX[5];
	POINT currFrame;
	int dashCurrFrameX[5];
	float dashSkillCoolTime;
	float dashTimer[5];
	POINT dashPos[5];
	float moveSpeed = 0;
	FPOINT clientPos;
	FPOINT pos;
	float frameSpeed;
	float moveframespeed;
	float speedCon;
	vector<RECT> atkCol;
public:
	virtual HRESULT Init(Player* player);
	virtual void Release();
	virtual void Update(Player* player);
	virtual void Render(HDC hdc, Player* player);
	virtual void Skill(Player* player);
	virtual vector<RECT>* GetAtkCol() { return &atkCol; }
};

