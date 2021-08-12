#pragma once
#include"SkillManager.h"
class Image;
class Skill_WindAttack :public SkillManager
{
private:
	Image* img;
	Image* WinAttackImage;
	POINT currFrame;
	float moveSpeed = 0;
	FPOINT clientPos;
	FPOINT pos;
	float frameSpeed;
	float moveframespeed;
	int attackCount;
	string attackDIr;
	float elapsedTime;
	int maxFrame;
	int minFrame;
	bool atkDir;
	bool isFire;
	enum  SDir
	{
		좌단, 우단, 상단, 하단, 좌상단, 좌하단, 우상단, 우하단
	};
	SDir sDir;
	vector<RECT> atkCol;
public:
	virtual HRESULT Init(Player* player);
	virtual void Release();
	virtual void Update(Player* player);
	virtual void Render(HDC hdc, Player* player);
	virtual void Skill(Player* player);
	virtual vector<RECT>* GetAtkCol() { return &atkCol; }
	//virtual void SetIsFire(bool isFire) { this->isFire = isFire; };
};