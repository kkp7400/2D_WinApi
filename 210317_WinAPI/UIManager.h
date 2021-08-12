#pragma once
#include "GameNode.h"
class Image;
class Player;
class SkillManager;
class UIManager:GameNode
{
protected:

	Player* player;
public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	void SetPlayer(Player* player) { this->player = player; }



};