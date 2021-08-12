#include "Skill_IceCrystal.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Camera.h"

HRESULT Skill_IceCrystal::Init(Player* player)
{
	ImageManager::GetSingleton()->AddImage("얼음크리스탈", "Image/WOL/player/iceCrystal.bmp", 700, 199, 5, 1, true, RGB(255, 0, 255));
	for (int i = 0; i < 16; i++)
	{
		img[i] = ImageManager::GetSingleton()->FindImage("얼음크리스탈");//32
		currFrame[i].x = 4;
		isFx[i] = false;
		elapsedTime[i] = 0.0f;
		clientPos2[i].x = 0;
		clientPos2[i].y = 0;
	}
	
	clientPos.x = 0;
	clientPos.y = 0;

	moveSpeed = player->GetMoveSpeed();
	pos = player->GetPos();
	moveframespeed = player->GetMoveFrameSpeed();
	attackCount = 0;
	attackDIr = "Right";


	maxFrame = 0;
	isFire = false;
	sDir = 상단;
	size = 0.5f;
	coolTime = 0.0f;
	timer = 0.f;
	return S_OK;
}

void Skill_IceCrystal::Release()
{
}

void Skill_IceCrystal::Update(Player* player)
{
	//if (isFire)
	//{
	//	isFx[0] = true;
	//	for (int i = 1; i < 10; i++)
	//	{
	//		for (int j = i - 1; j < 10; j++)
	//			if (currFrame[i].x == 2)
	//			{
	//				isFx[j] = true;
	//			}
	//	}
	//}
	for (int i = 0; i < 16; i++)
	if (isFx[i])
	{
		elapsedTime[i] += TimerManager::GetSingleton()->GetElapsedTime()*100;
		if (elapsedTime[i] > 5.f)
		{

			currFrame[i].x--;
			if (currFrame[i].x < 0)
			{
				currFrame[i].x = 4;
				isFx[i] = false;
			}
			elapsedTime[i] = 0.0f;
		}	
	}
	if (coolTime >= 0) coolTime -= TimerManager::GetSingleton()->GetElapsedTime();

	
	//	currFrame = player->GetCurrFrame();
	atkDir = player->GetAtkDir();
	moveSpeed = player->GetMoveSpeed();
	pos = player->GetPos();
	moveframespeed = player->GetMoveFrameSpeed();
	if(isFire)	timer += TimerManager::GetSingleton()->GetElapsedTime()*100;


	
	
	if (timer < 160.0f)
	{
		clientPos.x += cos(angle) * TimerManager::GetSingleton()->GetElapsedTime() * 500;
		clientPos.y -= sin(angle) * TimerManager::GetSingleton()->GetElapsedTime() * 500;
	}
	else if (timer >= 160.0f)
	{
		clientPos.x -= cos(angle) * TimerManager::GetSingleton()->GetElapsedTime() * 500;
		clientPos.y += sin(angle) * TimerManager::GetSingleton()->GetElapsedTime() * 500;
	}

	for (int i = 1; i <= 16; i++)
	{
		if (timer >= 320/i)
		{
			clientPos2[i].x = clientPos.x;
			clientPos2[i].y = clientPos.y;
			isFx[i] = true;
		}
	}

	if (timer >= 320)
	{
		isFire = false;
		timer = 0.f;
	}

}

void Skill_IceCrystal::Render(HDC hdc, Player* player)
{
	for (int i = 0; i < 16; i++)
	if (isFx[i])
	{
		for (int j = 0; j < 5; j++)
		{
			if (timer < 160.0f && currFrame[i].x == j)
			{
				clientPos2[i].x -= j;
				clientPos2[i].y += j;
			}
			else if (timer >= 160.0f && currFrame[i].x == j)
			{
				clientPos2[i].x += j;
				clientPos2[i].y -= j;
			}
			else
			{

			}
		}
		img[i]->FrameRender(hdc, clientPos2[i].x, clientPos2[i].y, currFrame[i].x, 0, true);
	}

}

void Skill_IceCrystal::Skill(Player* player)
{
	angle = DegToRad(player->GetMAngle());

	clientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x;
	clientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y;
	isFire = true;
	//coolTime = 5.0f;
	for (int i = 0; i < 16; i++)
	elapsedTime[i] = 0.0f;
}