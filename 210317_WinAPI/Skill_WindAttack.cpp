#include "Skill_WindAttack.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Camera.h"

HRESULT Skill_WindAttack::Init(Player* player)
{
	ImageManager::GetSingleton()->AddImage("윈드어택", "Image/WOL/player/WOL_NORMAL_ATTACK.bmp", 1600*0.7, 1600 * 0.7, 8, 8, true, RGB(255, 0, 255));
	WinAttackImage = ImageManager::GetSingleton()->FindImage("윈드어택");//32

	clientPos.x = 0;
	clientPos.y = 0;
	currFrame = player->GetCurrFrame();
	moveSpeed = player->GetMoveSpeed();
	pos = player->GetPos();
	moveframespeed = player->GetMoveFrameSpeed();
	attackCount = 0;
	attackDIr = "Right";
	currFrame.x = 0;
	currFrame.y = 0;
	sDir = 하단;
	elapsedTime = 0.0f;
	maxFrame = 0;
	isFire = false;
	atkCol.resize(1);
	atkCol[0] = GetRectToCenter(-400, -400, 0, 0);
	return S_OK;
}

void Skill_WindAttack::Release()
{
}

void Skill_WindAttack::Update(Player* player)
{
	elapsedTime += 100.0f * TimerManager::GetSingleton()->GetElapsedTime();

//	currFrame = player->GetCurrFrame();
	atkDir = player->GetAtkDir();
	moveSpeed = player->GetMoveSpeed();
	pos = player->GetPos();
	moveframespeed = player->GetMoveFrameSpeed();

	

	if (elapsedTime > 5.f)
	{
		currFrame.x++;
		if (currFrame.x >= maxFrame)
		{
			isFire = false;
		}
		elapsedTime = 0.0f;
	}
}

void Skill_WindAttack::Render(HDC hdc, Player* player)
{
	/*Rectangle(hdc, atkCol.left - Camera::GetSingleton()->GetPos().x,
		atkCol.top - Camera::GetSingleton()->GetPos().y,
		atkCol.right - Camera::GetSingleton()->GetPos().x,
		atkCol.bottom - Camera::GetSingleton()->GetPos().y);*/
	if (isFire)
	{
		WinAttackImage->FrameRender(hdc, clientPos.x, clientPos.y, currFrame.x, currFrame.y, true);
		atkCol[0] = GetRectToCenter(clientPos.x + Camera::GetSingleton()->GetPos().x, clientPos.y + Camera::GetSingleton()->GetPos().y, 90, 90);
	}
	else
	{
		atkCol[0] = GetRectToCenter(-400, -400, 0, 0);
	}
}

void Skill_WindAttack::Skill(Player* player)
{
	//if (sDir == 좌단)
	//{
	//	if (elapsedTime > moveframespeed)
	//	{
	//		currFrame.x++;
	//		if (currFrame.x >= maxFrame)
	//		{
	//			currFrame.x = minFrame;
	//		}
	//		elapsedTime = 0.0f;
	//	}
	//};
	//if (sDir == 우단);
	//if (sDir == 상단);
	//if (sDir == 하단);
	//if (sDir == 좌상단);
	//if (sDir == 좌하단);
	//if (sDir == 우상단);
	//if (sDir == 우하단);
	if (player->mDir == 0)
	{
		sDir = 좌단;
		currFrame.y = 4;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x - 70;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y;		
	}
	else if (player->mDir == 1) 
	{
		sDir = 우단;		
		currFrame.y = 0;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x+70;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y;
	}
	else if (player->mDir == 2)
	{
		sDir = 상단;
		currFrame.y = 2;	
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y-70;
	}
	else if (player->mDir == 3)
	{
		sDir = 하단;
		currFrame.y = 6;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y+70;
	}
	else if (player->mDir == 4)
	{
		sDir = 좌상단;
		currFrame.y = 3;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x-40;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y-40;
	}
	else if (player->mDir == 5)
	{
		sDir = 좌하단;
		currFrame.y = 5;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x-40;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y+40;
	}
	else if (player->mDir == 6)
	{
		sDir = 우상단;
		currFrame.y = 1;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x+40;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y-40;
	}
	else if (player->mDir == 7) 
	{
		sDir = 우하단; 
		currFrame.y = 7;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x+40;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y+40;
	}
	if (atkDir)
	{
		currFrame.x = 0;
		maxFrame = 3;
		minFrame = 0;
	}
	else
	{
		currFrame.x = 4;
		maxFrame = 7;
		minFrame = 4;
	}
	isFire = true;
	elapsedTime = 0.0f;
}
