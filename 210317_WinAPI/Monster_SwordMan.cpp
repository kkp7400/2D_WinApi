#include "Monster_SwordMan.h"
#include "Image.h"
#include "Player.h"
#include "Camera.h"
#include "CommonFunction.h"
HRESULT Monster_SwordMan::Init()
{
	pos = startPos;
	ImageManager::GetSingleton()->AddImage("소드맨스폰", "Image/WOL/enemy/SPAWN_CARD_SWORDMAN.bmp", 4800 * 0.7, 230 * 0.7, 32, 1, true, RGB(255, 0, 255));
	spawn = ImageManager::GetSingleton()->FindImage("소드맨스폰");
	ImageManager::GetSingleton()->AddImage("소드맨좌", "Image/WOL/enemy/SWORDMAN_LEFT.bmp", 1376 * 0.7, 1260 * 0.7, 8, 5, true, RGB(255, 0, 255));
	swordManLeft = ImageManager::GetSingleton()->FindImage("소드맨좌");
	ImageManager::GetSingleton()->AddImage("소드맨우", "Image/WOL/enemy/SWORDMAN_RIGHT.bmp", 1376 * 0.7, 1260 * 0.7, 8, 5, true, RGB(255, 0, 255));
	swordManRight = ImageManager::GetSingleton()->FindImage("소드맨우");
	ImageManager::GetSingleton()->AddImage("소드맨이펙트", "Image/WOL/enemy/SWORDMAN_ATTACK_old.bmp", 800, 1200, 4, 6, true, RGB(255, 0, 255));
	effect = ImageManager::GetSingleton()->FindImage("소드맨이펙트");
	dir = LEFT;
	state = NONE;
	atkRange.left = pos.x - 140;
	atkRange.right = pos.x + 140;
	atkRange.top = pos.y - 120;
	atkRange.bottom = pos.y + 120;
	currFrame.y = 0;
	currFrame.x = 0;
	fxCurrFrame.x = 0;
	fxCurrFrame.y = 0;
	moveFrameSpeed = 0.7f;
	moveSpeed = 30.0f;
	hp = 3000 * 3;
	atkCool = 0;
	atk = 500;
	isHit = false;
	fxCurrFrame = { 0, 0 };
	//hitCol {1,1,1,1}
	return S_OK;
}

void Monster_SwordMan::Release()
{

}

void Monster_SwordMan::Update()
{
	if (state != END)
	{
		atkRange.left = pos.x - 140;
		atkRange.right = pos.x + 140;
		atkRange.top = pos.y - 120;
		atkRange.bottom = pos.y + 120;
		
		//if (state != GOHOME&state != ATTACK)
		//{
		FPOINT targetPos;
		angle = GetAngle(pos, player->GetPos());

		//}
		/*else angle = GetAngle(pos, startPos);*/
		elapsedTime += TimerManager::GetSingleton()->GetElapsedTime();
		fxElapsedTime += TimerManager::GetSingleton()->GetElapsedTime();
		if (atkCool >= 0)
		{
			atkCool -= TimerManager::GetSingleton()->GetElapsedTime();
			atkCol = GetRectToCenter(-100, -100, 0, 0);
		}
		//if (state == MOVE)
		{
			float mAngle = angle * 180 / PI;
			if (pos.x <= player->GetPos().x)
			{
				dir = RIGHT;
			}
			else if (pos.x >= player->GetPos().x)
			{
				dir = LEFT;
			}
		}

		if (hp <= 0 && state != END)
		{
			state = DIE;
		}
		else
		{
			if (aggroRange.left < player->GetPos().x &&
				aggroRange.right > player->GetPos().x &&
				aggroRange.top < player->GetPos().y &&
				aggroRange.bottom > player->GetPos().y && !isSpawn)
			{
				state = SPAWN;

			}
			else if (isSpawn && state != DIE)
			{
				/*if (aggroRange.left >= player->GetPos().x ||
					aggroRange.right <= player->GetPos().x ||
					aggroRange.top >= player->GetPos().y ||
					aggroRange.bottom <= player->GetPos().y || state == IDLE)
				{
					state = GOHOME;
				}*/
				if (aggroRange.left < player->GetPos().x &&
					aggroRange.right > player->GetPos().x &&
					aggroRange.top < player->GetPos().y &&
					aggroRange.bottom > player->GetPos().y && state != DIE && state != SPAWN)
				{
					if (isHit && state != DIE && state != END)
					{
						state = HIT;

					}
					else if (RectInRect(atkRange, player->GetHitCol()) && atkCool <= 0 && (state == IDLE || state == MOVE))
					{
						state = ATTACK;
					}
					else if (!RectInRect(atkRange, player->GetHitCol()) )
					{
						state = MOVE;
					}
				}
				else state = IDLE;
			}
		}

		switch (state)
		{
		case Monster_SwordMan::SPAWN:
			Spawn();
			break;
		case Monster_SwordMan::IDLE:
			Idle();
			break;
		case Monster_SwordMan::MOVE:
			Move();
			break;
		case Monster_SwordMan::ATTACK:
			Attack();
			break;
		case Monster_SwordMan::DIE:
			Die();
			break;
			//case Monster_SwordMan::GOHOME:
			//	GoHome();
		case Monster_SwordMan::HIT:
			Hit();
			break;
		}
	}
	
}

void Monster_SwordMan::Render(HDC hdc)
{
	if (state != END)
	{


		FPOINT clientPos;
		if (state != DIE && state != END)
		{
			hitCol = GetRectToCenter(pos.x, pos.y, 70, 120);
		}
		else
		{
			hitCol = GetRectToCenter(-100, -100, 0, 0);
		}
		if (state == ATTACK)
		{
			if (dir == LEFT)	atkCol = GetRectToCenter(pos.x - 70, pos.y, 70, 120);
			if (dir == RIGHT)	atkCol = GetRectToCenter(pos.x + 70, pos.y, 70, 120);
		}
		else if (state != ATTACK || state == DIE || state == END)atkCol = GetRectToCenter(-100, -100, 0, 0);

		//Rectangle(hdc, hitCol.left - Camera::GetSingleton()->GetPos().x, hitCol.top - Camera::GetSingleton()->GetPos().y,
		//	hitCol.right - Camera::GetSingleton()->GetPos().x, hitCol.bottom - Camera::GetSingleton()->GetPos().y);

		//Rectangle(hdc, atkCol.left - Camera::GetSingleton()->GetPos().x, atkCol.top - Camera::GetSingleton()->GetPos().y,
			//atkCol.right - Camera::GetSingleton()->GetPos().x, atkCol.bottom - Camera::GetSingleton()->GetPos().y);

		clientPos.x = pos.x - Camera::GetSingleton()->GetPos().x;
		clientPos.y = pos.y - Camera::GetSingleton()->GetPos().y - 30;
		if (state == SPAWN)
			spawn->FrameRender(hdc,
				clientPos.x,
				clientPos.y,
				currFrame.x,
				currFrame.y,
				true);

		if (dir == LEFT && state != NONE && state != SPAWN && state != END)
			swordManLeft->FrameRender(hdc,
				clientPos.x,
				clientPos.y,
				currFrame.x,
				currFrame.y,
				true);
		else if (dir == RIGHT && state != NONE && state != SPAWN && state != END)
			swordManRight->FrameRender(hdc,
				clientPos.x,
				clientPos.y,
				currFrame.x,
				currFrame.y,
				true);

		if (state == ATTACK)
		{
			FPOINT fxClientPos;
			if(dir==LEFT)
				fxClientPos.x = pos.x - 70 -Camera::GetSingleton()->GetPos().x;
			if (dir == RIGHT)
				fxClientPos.x = pos.x + 70 - Camera::GetSingleton()->GetPos().x;
			fxClientPos.y = pos.y - Camera::GetSingleton()->GetPos().y;
			effect->FrameRender(hdc,
				fxClientPos.x,
				fxClientPos.y,
				fxCurrFrame.x,
				fxCurrFrame.y,
				true);
		}

		/*wsprintf(szText, "커렌X: %d", currFrame.x);
		TextOut(hdc, 400, 20, szText, strlen(szText));
		wsprintf(szText, "스테이트: %d", state);
		TextOut(hdc, 400, 40, szText, strlen(szText));*/
	}
}

void Monster_SwordMan::SetStartPos(FPOINT pos, RECT rc)
{
	startPos = pos;
	aggroRange = rc;

}

void Monster_SwordMan::Spawn()
{
	moveFrameSpeed = 0.05f;
	currFrame.y = 0;	
	if (elapsedTime > moveFrameSpeed)
	{
		currFrame.x++;
		if (currFrame.x >= 32)
		{
			state = IDLE;
			isSpawn = true;
		}
		elapsedTime = 0.0f;
	}
}

void Monster_SwordMan::Idle()
{
	currFrame.y = 0;
	currFrame.x = 0;
	moveFrameSpeed = 0.5f;
	elapsedTime = 0.0f;
}

void Monster_SwordMan::Move()
{
	//if (abs(player->GetPos().x - pos.x) > 40 && abs(player->GetPos().y - pos.y) > 40) return;
	if (currFrame.x >= 6)
	{
		currFrame.x = 0;
	}
	moveFrameSpeed = 0.1;
	if (dir == LEFT)
	{
		currFrame.y = 1;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 5)
			{
				state = IDLE;
				currFrame.x = 0;
			}
			elapsedTime = 0.0f;
		}		
	}
	else if (dir == RIGHT)
	{
		currFrame.y = 1;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 5)
			{
				state = IDLE;
				currFrame.x = 0;
			}
			elapsedTime = 0.0f;
		}
	}
	
	pos.x += cos(angle) * moveSpeed * elapsedTime;
	pos.y -= sin(angle) * moveSpeed * elapsedTime;
	

}

void Monster_SwordMan::Attack()
{
	
	moveFrameSpeed = 0.3;
	if (dir == LEFT)
	{
		currFrame.y = 2;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 1)
			{
				state = IDLE;
				currFrame.x = 0;
				atkCool = 3.0f;
			}
			elapsedTime = 0.0f;
		}
	}
	
	else if (dir == RIGHT)
	{
		currFrame.y = 2;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 1)
			{
				state = IDLE;
				currFrame.x = 0;
				atkCool = 3.0f;
			}
			elapsedTime = 0.0f;
		}
	}
	//이펙트인데 나중에
	if (dir == LEFT)
	{
		fxCurrFrame.y = 0;
		if (fxElapsedTime > 3)
		{
			fxCurrFrame.x++;
			if (fxCurrFrame.x >= 3)
			{
				state = IDLE;
				fxCurrFrame.x = 0;
				//atkCool = 2.0f;
			}
			fxElapsedTime = 0.0f;
		}
	}
	else if (dir == RIGHT)
	{
		fxCurrFrame.y = 1;
		if (fxElapsedTime > 3)
		{
			fxCurrFrame.x++;
			if (fxCurrFrame.x >= 3)
			{
				state = IDLE;
				fxCurrFrame.x = 0;
				//atkCool = 2.0f;
			}
			fxElapsedTime = 0.0f;
		}
	}	
}

void Monster_SwordMan::Die()
{
	moveFrameSpeed = 0.2f;
	if (currFrame.x >= 8) currFrame.x = 0;
	if (dir == LEFT)
	{
		currFrame.y = 4;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 7)
			{
				state = END;
			}
			elapsedTime = 0.0f;
		}
	}
	else if (dir == RIGHT)
	{
		currFrame.y = 4;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 7)
			{		
				state = END;
			}
			elapsedTime = 0.0f;
		}
	}
}

void Monster_SwordMan::GoHome()
{
	if (dir == LEFT)
	{
		
		currFrame.y = 1;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 5)
			{
				//state = IDLE;
				currFrame.x = 0;
			}
			elapsedTime = 0.0f;
		}

	}
	else if (dir == RIGHT)
	{
		
		currFrame.y = 1;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 5)
			{
				//state = IDLE;
				currFrame.x = 0;
			}
			elapsedTime = 0.0f;
		}
	}
	if (pos.x != startPos.x && pos.y != startPos.y)
	{
		pos.x += cos(angle) * moveSpeed * elapsedTime;
		pos.y -= sin(angle) * moveSpeed * elapsedTime;
	}
	else state = IDLE;
}

void Monster_SwordMan::Hit()
{
	if (currFrame.x >= 2)
	{
		currFrame.x = 0;
	}
	if (dir == LEFT)
	{
		
		currFrame.y = 3;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 1)
			{
				state = IDLE;
				hp -= player->GetAtk();
				isHit = false;
				currFrame.x = 0;
			}
			elapsedTime = 0.0f;
		}
	}
	else if (dir == RIGHT)
	{
		/*if (aggroRange.left < player->GetPos().x &&
			aggroRange.right > player->GetPos().x &&
			aggroRange.top < player->GetPos().y &&
			aggroRange.bottom > player->GetPos().y)
		{
			if (abs(player->GetPos().x - pos.x) > 10 && abs(player->GetPos().y - pos.y) > 10)
			pos.x -= 100* TimerManager::GetSingleton()->GetElapsedTime();
		}*/
		currFrame.y = 3;
		if (elapsedTime > moveFrameSpeed)
		{
			currFrame.x++;
			if (currFrame.x >= 1)
			{
				state = IDLE;
				hp -= player->GetAtk();
				isHit = false;
				currFrame.x = 0;
			}
			elapsedTime = 0.0f;
		}
	}
}

//로딩
//플레이어 데미지 방향 전부
//플레이어 스폰