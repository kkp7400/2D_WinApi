#pragma once
#include"SkillManager.h"
class Image;
class Skill_IceCrystal :public SkillManager
{
private:
	Image* img[16];
	POINT currFrame[16];
	float moveSpeed = 0;
	FPOINT clientPos2[16];
	FPOINT clientPos;
	FPOINT RockShadowPos;
	FPOINT pos;
	float frameSpeed;
	float moveframespeed;
	int attackCount;
	string attackDIr;
	float elapsedTime[16];
	int maxFrame;
	int minFrame;
	bool atkDir;
	float angle;
	float size;
	bool isFx[16];
	float timer;
	char szText[128];
	enum  SDir
	{
		좌단, 우단, 상단, 하단, 좌상단, 좌하단, 우상단, 우하단
	};
	SDir sDir;
public:
	virtual HRESULT Init(Player* player);
	virtual void Release();
	virtual void Update(Player* player);
	virtual void Render(HDC hdc, Player* player);
	virtual void Skill(Player* player);
	virtual float GetCoolTime() { return this->coolTime; }
	virtual vector<RECT>* GetAtkCol() { return nullptr; }
};
