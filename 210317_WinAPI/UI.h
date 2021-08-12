#pragma once
#include "GameNode.h"

class UIManager;
class Player;
class SkillManager;
class UI:GameNode
{
private:
	vector<UIManager*> uiMgr;
	SkillManager* skillMgr[4];
	Player* player;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetPlayer(Player* player) { this->player = player; }

};
