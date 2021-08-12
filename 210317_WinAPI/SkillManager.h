#pragma once
#include "GameNode.h"
#include "Player.h"
class Image;
class SkillManager : public GameNode
{
protected:
	float coolTime;	
	bool isFire;
public:
	virtual HRESULT Init(Player* player);
	virtual void Release();
	virtual void Update(Player* player);
	virtual void Render(HDC hdc, Player* player);
	virtual void Skill(Player* player);
	virtual float GetCoolTime() { return this->coolTime; }
	virtual vector<RECT>* GetAtkCol() = 0;
};

