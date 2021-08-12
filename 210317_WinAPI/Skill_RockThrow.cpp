#include "Skill_RockThrow.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Camera.h"

HRESULT Skill_RockThrow::Init(Player* player)
{
    ImageManager::GetSingleton()->AddImage("바위던지기", "Image/WOL/player/upRock.bmp", 121,128, 1, 1, true, RGB(255, 0, 255));
    img = ImageManager::GetSingleton()->FindImage("바위던지기");//32
	ImageManager::GetSingleton()->AddImage("바위그림자", "Image/WOL/player/BOTTOM_HOLE.bmp", 200*0.8, 150*0.8, 1, 1, true, RGB(255, 0, 255));
	img2 = ImageManager::GetSingleton()->FindImage("바위그림자");//32
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
	elapsedTime = 0.0f;
	maxFrame = 0;
	isFire = false;
	sDir = 상단;
	size = 0.5f;
	coolTime = 0.0f;
	atkCol.resize(1);
	atkCol[0] = GetRectToCenter(-300, -300, 0, 0);
    return S_OK;
}

void Skill_RockThrow::Release()
{
}

void Skill_RockThrow::Update(Player* player)
{
	if (isFire)
	{
		elapsedTime += 100.0f * TimerManager::GetSingleton()->GetElapsedTime();
		if (size <= 1.0f)
		{
			size += 0.01f;
		}
	}
	else if (coolTime >= 0) coolTime -= TimerManager::GetSingleton()->GetElapsedTime();

	//	currFrame = player->GetCurrFrame();
	atkDir = player->GetAtkDir();
	moveSpeed = player->GetMoveSpeed();
	pos = player->GetPos();
	moveframespeed = player->GetMoveFrameSpeed();

	if (elapsedTime > 100.0f)
	{
		isFire = false;
	}
	if (elapsedTime > 40.0f)
	{
		clientPos.x += cos(angle) * 0.6f * elapsedTime;
		clientPos.y -= sin(angle) * 0.6f * elapsedTime;
	}
	else if(elapsedTime < 25.f)
	{
		clientPos.x -= elapsedTime*0.05f;
		clientPos.y -= elapsedTime*0.1f;
	}
}

void Skill_RockThrow::Render(HDC hdc, Player* player)
{
	/*Rectangle(hdc, atkCol[0].left - Camera::GetSingleton()->GetPos().x,
		atkCol[0].top - Camera::GetSingleton()->GetPos().y,
		atkCol[0].right - Camera::GetSingleton()->GetPos().x,
		atkCol[0].bottom - Camera::GetSingleton()->GetPos().y);*/
	if (isFire)
	{		
		img2->Render(hdc, RockShadowPos.x, RockShadowPos.y, true);
		img->Render2(hdc, clientPos.x, clientPos.y, true, size);
		atkCol[0] = GetRectToCenter(clientPos.x+ Camera::GetSingleton()->GetPos().x, clientPos.y + Camera::GetSingleton()->GetPos().y, 100, 100);
	}
	else
	{
		atkCol[0] = GetRectToCenter(-300, -300, 0, 0);
	}

}

void Skill_RockThrow::Skill(Player* player)
{
	angle = DegToRad(player->GetMAngle());
	if (player->mDir == 0)
	{
		sDir = 우단;
		currFrame.y = 4;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x + 70;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y;		
	}
	else if (player->mDir == 1)
	{
		sDir = 좌단;
		currFrame.y = 0;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x - 70;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y;
	}
	else if (player->mDir == 2)
	{
		sDir = 하단;
		currFrame.y = 2;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y + 70;
	}
	else if (player->mDir == 3)
	{
		sDir = 상단;
		currFrame.y = 6;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y - 70;
	}
	else if (player->mDir == 4)
	{
		sDir = 우하단;
		currFrame.y = 3;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x + 40;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y + 40;
	}
	else if (player->mDir == 5)
	{
		sDir = 우상단;
		currFrame.y = 5;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x + 40;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y - 40;
	}
	else if (player->mDir == 6)
	{
		sDir = 우하단;
		currFrame.y = 1;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x - 40;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y + 40;
	}
	else if (player->mDir == 7)
	{
		sDir = 좌상단;
		currFrame.y = 7;
		clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x - 40;
		clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y - 40;
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
	RockShadowPos = clientPos;	
	RockShadowPos.y += 50;
	clientPos.x += 30;
	clientPos.y += 60;
	isFire = true;
	size = 0.5f;
	coolTime = 5.0f;
	elapsedTime = 0.0f;
}
