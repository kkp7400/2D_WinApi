#include "Skill_Ice.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Camera.h"
HRESULT Skill_Ice::Init(Player* player)
{
	ImageManager::GetSingleton()->AddImage("얼음", "Image/WOL/player/iceCrystal.bmp", 700, 199, 5, 1, true, RGB(255, 0, 255));
	elapsedTime = 0.0f;
	currentFrame.x = 4;
	for (int i = 0; i < 5; i++)
	{
		img[i] = ImageManager::GetSingleton()->FindImage("얼음");//32
	}
	isFire = false;
	skillPos.x = player->GetPos().x;
	skillPos.y = player->GetPos().y;
	coolTime = 0.0f;
	angle = 0.0f;
	skillTime = 0.0f;
	atkCol.resize(5);
	for(int i =0; i<5;i++)
	atkCol[i] = GetRectToCenter(-200, -200, 0, 0);
    return S_OK;
}

void Skill_Ice::Release()
{
}

void Skill_Ice::Update(Player* player)
{
	if (coolTime >= 0) coolTime -= TimerManager::GetSingleton()->GetElapsedTime();
	{
		if (isFire)
		{
			skillTime += TimerManager::GetSingleton()->GetElapsedTime();
			elapsedTime += TimerManager::GetSingleton()->GetElapsedTime();
			if (elapsedTime > 0.05f)
			{
				currentFrame.x--;
				if (skillTime < 0.7f)
				{
					skillPos.x += cos(angle) * 50;
					skillPos.y -= sin(angle) * 50;
				}
				else if (skillTime >= 0.7f)
				{
					skillPos.x -= cos(angle) * 50;
					skillPos.y += sin(angle) * 50;
				}
				if (skillTime >= 1.4f)
				{
					isFire = false;
					skillTime = 0.0f;
					skillPos.x = player->GetPos().x;
					skillPos.y = player->GetPos().y;

				}
				if (currentFrame.x < 0)
				{
					currentFrame.x = 4;
					//isFire = false;
					//skillPos = { 0,0 };
				}
				elapsedTime = 0.0f;
			}
		}
		else
		{
			skillPos.x = player->GetPos().x;
			skillPos.y = player->GetPos().y;
		}
	}
}

void Skill_Ice::Render(HDC hdc, Player* player)
{	
	//if (isFire)
	//{
	//	for (int i = 0; i < 5; i++)
	//	{
	//		if (skillTime < 0.7f)
	//		{
	//			clientPos.x = (skillPos.x - (cos(angle) * (i * 40) + 30)) - Camera::GetSingleton()->GetPos().x;
	//			clientPos.y = (skillPos.y + (sin(angle) * (i * 40) + 30)) - Camera::GetSingleton()->GetPos().y;
	//		}
	//		else if (skillTime >= 0.7f)
	//		{
	//			clientPos.x = (skillPos.x + (cos(angle) * (i * 40) + 30)) - Camera::GetSingleton()->GetPos().x;
	//			clientPos.y = (skillPos.y - (sin(angle) * (i * 40) + 30)) - Camera::GetSingleton()->GetPos().y;
	//		}
	//		/*clientPos.x += cos(angle) * (player->GetPos().x + skillPos.x - i * 50) - Camera::GetSingleton()->GetPos().x;
	//		clientPos.y -= sin(angle) * (player->GetPos().y + skillPos.y - i * 50) - Camera::GetSingleton()->GetPos().y;*/
	//	//	if (currentFrame.x + i < 0 || currentFrame.x + i > 5)	continue;
	//		img[i]->FrameRender(hdc, clientPos.x, clientPos.y,i, 0,true);
	//	}
	//}
	if (isFire)
	{
		for (int i = 0; i < 5; i++)
		{
			
			if (skillTime < 0.7f)
			{
				clientPos.x = (skillPos.x - (cos(angle) * (i * 40))) - Camera::GetSingleton()->GetPos().x;
				clientPos.y = (skillPos.y + (sin(angle) * (i * 40))) - Camera::GetSingleton()->GetPos().y;
				atkCol[i] = GetRectToCenter((skillPos.x - (cos(angle) * (i * 40))), (skillPos.y + (sin(angle) * (i * 40))), 70, 150);
			}
			else if (skillTime >= 0.7f)
			{
				clientPos.x = (skillPos.x + (cos(angle) * (i * 40))) - Camera::GetSingleton()->GetPos().x;
				clientPos.y = (skillPos.y - (sin(angle) * (i * 40))) - Camera::GetSingleton()->GetPos().y;
				atkCol[i] = GetRectToCenter((skillPos.x + (cos(angle) * (i * 40))), (skillPos.y - (sin(angle) * (i * 40))), 70, 150);
			}
			/*clientPos.x += cos(angle) * (player->GetPos().x + skillPos.x - i * 50) - Camera::GetSingleton()->GetPos().x;
			clientPos.y -= sin(angle) * (player->GetPos().y + skillPos.y - i * 50) - Camera::GetSingleton()->GetPos().y;*/
			//	if (currentFrame.x + i < 0 || currentFrame.x + i > 5)	continue;
			//Rectangle(hdc, atkCol[i].left - Camera::GetSingleton()->GetPos().x, atkCol[i].top - Camera::GetSingleton()->GetPos().y,
			//	atkCol[i].right - Camera::GetSingleton()->GetPos().x, atkCol[i].bottom - Camera::GetSingleton()->GetPos().y);
			img[i]->FrameRender(hdc, clientPos.x, clientPos.y, i, 0, true);
			
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		atkCol[i] = GetRectToCenter(-200, -200, 0, 0);
	}
}

void Skill_Ice::Skill(Player* player)
{	
	angle = DegToRad(player->GetMAngle());
	isFire = true;
	degAngle = angle * 180 / PI;
	coolTime = 5.0f;

	if (degAngle < 0)	degAngle += 360;

	if (degAngle > 337.5 || degAngle <= 22.5) skillPos.x += 100; //mDir = MDir::우단;
	else if (degAngle > 22.5 && degAngle <= 67.5)
	{
		skillPos.x += 75;
		skillPos.y -= 75;
	}//mDir = MDir::우상단;
	else if (degAngle > 67.5 && degAngle<= 112.5)skillPos.y -= 100; //mDir = MDir::상단;
	else if (degAngle > 112.5 && degAngle <= 157.5)
	{
		skillPos.x -= 75;
		skillPos.y -= 75;
	}//mDir = MDir::좌상단;
	else if (degAngle > 157.5 && degAngle <= 202.5)skillPos.x -= 100; //mDir = MDir::좌단;
	else if (degAngle > 202.5 && degAngle <= 247.5)
	{
		skillPos.x -= 75;
		skillPos.y += 75;
	}//mDir = MDir::좌하단;
	else if (degAngle > 247.5 && degAngle <= 292.5)skillPos.y += 100; //mDir = MDir::하단;
	else if (degAngle > 292.5 && degAngle <= 337.5)
	{
		skillPos.x += 75;
		skillPos.y += 75;
	}//mDir = MDir::우하단;
}