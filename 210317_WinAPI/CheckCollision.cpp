#include "CheckCollision.h"
#include "Player.h"
//#include "CheckCollision.h"
#include "CommonFunction.h"
#include "Monster.h"
#include "Player.h"
#include "MonsterManager.h"
//#include "Enemy.h"
//#include "Tank.h"
//#include "Missile.h"
//#include "MissileManager.h"
//#include "EnemyManager.h"
//
//
//
HRESULT CheckCollision::Init()
{
	return S_OK;
}
//
//void CheckCollision::isObjectDie(Tank* tank, EnemyManager* enemy)
//{
//	for (int i = 0; i < enemy->GetEnemys().size(); i++)
//	{
//		if (RectInRect(enemy->GetEnemys()[i]->GetEnemyShape(), tank->getMissileManager()->GetMissiles()[0]->GetMissileShape()))
//		{
//			enemy->GetEnemys()[i]->SetIsAlive(false);
//			tank->getMissileManager()->GetMissiles()[0]->SetIsFired(false, tank->GetPos());
//		}
//		if (RectInRect(tank->GetShape(), enemy->GetEnemys()[i]->getMissileManager()->GetMissiles()[0]->GetMissileShape()))
//		{
//			tank->SetisAlive(false);
//			enemy->GetEnemys()[i]->getMissileManager()->GetMissiles()[0]->SetIsFired(false, enemy->GetEnemys()[i]->GetPos());
//		}
//	}
//}
//
//void CheckCollision::isTileBreak(Tank* tank, EnemyManager* enemy, TILE_INFO* tileInfo)
//{
//	for (int i = 0; i < TILE_X * TILE_Y; i++)
//	{
//		if (tileInfo[i].tileVar == BRICK)
//		{ 
//			if (RectInRect(tank->getMissileManager()->GetMissiles()[0]->GetMissileShape(), tileInfo[i].rcTile))
//			{
//				tileInfo[i].isAlive = false;
//				tank->getMissileManager()->GetMissiles()[0]->SetIsFired(false, tank->GetPos());
//			}
//			for (int j = 0; j < enemy->GetEnemys().size(); j++)
//			{
//				if (RectInRect(enemy->GetEnemys()[j]->getMissileManager()->GetMissiles()[0]->GetMissileShape(), tileInfo[i].rcTile))
//				{
//					tileInfo[i].isAlive = false;
//					enemy->GetEnemys()[j]->getMissileManager()->GetMissiles()[0]->SetIsFired(false, enemy->GetEnemys()[j]->GetPos());
//				} 
//			}
//		}
//	}
//}
//
//void CheckCollision::MissileToMissile(Tank* tank, EnemyManager* enemy)
//{
//	for (int i = 0; i < enemy->GetEnemys().size(); i++)
//	{
//		if (CircleToCircle(tank->getMissileManager()->GetMissiles()[0]->GetPos(), 
//			enemy->GetEnemys()[i]->getMissileManager()->GetMissiles()[0]->GetPos(),
//			tank->getMissileManager()->GetMissiles()[0]->GetSize(), 
//			enemy->GetEnemys()[i]->getMissileManager()->GetMissiles()[0]->GetSize()))
//		{
//			tank->getMissileManager()->GetMissiles()[0]->SetIsFired(false, tank->GetPos());
//			enemy->GetEnemys()[i]->getMissileManager()->GetMissiles()[0]->SetIsFired(false, enemy->GetEnemys()[i]->GetPos());
//		}
//	}
//}
//
///// 페르마의 마지막 정리()
//void CheckCollision::TankVsTile(Tank* tank, TILE_INFO* tileInfo)
//{
//	tankRC = tank->GetShape();
//	pos = tank->GetPos();
//	for (int i = 0; i < TILE_X * TILE_Y; i++)
//	{
//		if (tileInfo[i].tileVar == BRICK)
//		{
//			if (IntersectRect(&tankVsTile, &tankRC, &tileInfo[i].rcTile))
//			{
//				SetRect(&tankVsTile, 0, 0
//					, tankVsTile.right - tankVsTile.left
//					, tankVsTile.bottom - tankVsTile.top);
//
//				//위 아래 충돌
//				if (tankVsTile.right > tankVsTile.bottom)
//				{
//					if ((tankRC.bottom + tankRC.top) / 2
//						< (tileInfo[i].rcTile.bottom + tileInfo[i].rcTile.top) / 2)
//						pos.y -= tankVsTile.bottom;
//					else
//						pos.y += tankVsTile.bottom;
//				}
//				//오른쪽 왼쪽 충돌
//				else
//				{
//					if ((tankRC.right + tankRC.left) / 2
//						< (tileInfo[i].rcTile.right + tileInfo[i].rcTile.left) / 2)
//						pos.x -= tankVsTile.right;
//					else
//						pos.x += tankVsTile.right;
//				}
//			}
//				tank->SetPos(pos);
//		}
//	}
//} 

FPOINT CheckCollision::PlayerVsTile(RECT rc, FPOINT playerPos, vector<vector<TILE_INFO>>& tile)
{
	playerRc.left = rc.left;
	playerRc.top = rc.top;
	playerRc.right = rc.right;
	playerRc.bottom = rc.bottom;
	POINT culling;
	culling.y = playerPos.y / 40;
	culling.x = playerPos.x / 40;
	this->pos = playerPos;
	POINT tileCenter;
	//if (culling.y - 15 >= 0 && culling.y + 15 <= 124 && culling.x - 20 >= 0 && culling.x + 20 <= 124)
	for (int i = culling.y - 10; i <= culling.y + 10; i++)
	{
		for (int j = culling.x - 10; j <= culling.x + 10; j++)
		{
			if (i < 0 || i > 124 || j < 0 || j > 124) continue;
			RECT interRcet;
			tileCenter.x = tile[i][j].rcTile.left + 20;
			tileCenter.y = tile[i][j].rcTile.top + 20;
			if (tile[i][j].tileVar == WALL || tile[i][j].tileVar == WALLTWO || tile[i][j].tileVar == BLANK)
			{
				if (IntersectRect(&interRcet, &playerRc, &tile[i][j].rcTile))
				{
					SetRect(&interRcet, 0, 0
						, interRcet.right - interRcet.left
						, interRcet.bottom - interRcet.top);

					//위 아래 충돌
					if (interRcet.right > interRcet.bottom)
					{
						if ((playerRc.bottom + playerRc.top) / 2
							< (tile[i][j].rcTile.bottom + tile[i][j].rcTile.top) / 2)
							pos.y -= interRcet.bottom;
						else
							pos.y += interRcet.bottom;
					}
					//오른쪽 왼쪽 충돌
					else//if(interRcet.right < interRcet.bottom)
					{
						if ((playerRc.right + playerRc.left) / 2
							< (tile[i][j].rcTile.right + tile[i][j].rcTile.left) / 2)
							pos.x -= interRcet.right;
						else
							pos.x += interRcet.right;
					}
				}


			}
		}
	}
	return pos;
}



void CheckCollision::Update()
{
	//PlayerHitVsMonHit();
	PlayerAtkVsMonHit();
	PlayerHitVsMonAtk();
}

void CheckCollision::PlayerHitVsMonAtk()
{
	RECT playerRc = player->GetHitCol();
	
	for (int i = 2; i <= 10; i++)
	{		
		RECT monsterRc = monster->GetMonMgr(i, 0)->GetAtkCol();
		RECT interRcet;	
		
		if (IntersectRect(&interRcet, &playerRc, &monsterRc))
		{
			SetRect(&interRcet, 0, 0
				, interRcet.right - interRcet.left
				, interRcet.bottom - interRcet.top);

			//위 아래 충돌
			if (interRcet.right > interRcet.bottom)
			{
				if ((playerRc.bottom + playerRc.top) / 2
					< (monsterRc.bottom + monsterRc.top) / 2)//플레이어가 위
				{					
					player->SetHp(player->GetHp() - monster->GetMonMgr(i, 0)->GetAtk());
					player->SetHitDir("Bottom");
					player->SetIsHit(true);
				}
				else
				{
					player->SetHp(player->GetHp() - monster->GetMonMgr(i, 0)->GetAtk());
					player->SetHitDir("Top");
					player->SetIsHit(true);
				}
			}
			//오른쪽 왼쪽 충돌
			else//if(interRcet.right < interRcet.bottom)
			{
				if ((playerRc.right + playerRc.left) / 2
					< (monsterRc.right + monsterRc.left) / 2)//플레이어가 dhls
				{
					player->SetHp(player->GetHp() - monster->GetMonMgr(i, 0)->GetAtk());
					player->SetHitDir("Right");
					player->SetIsHit(true);
				}
				else
				{
					player->SetHp(player->GetHp() - monster->GetMonMgr(i, 0)->GetAtk());
					player->SetHitDir("Left");
					player->SetIsHit(true);
				}
			}
		}		
	}
}

void CheckCollision::PlayerAtkVsMonHit()
{
	//vector<RECT> rc;
	//rc.resize(player->GetAtkCol(0)->size());
	for (int i = 0; i < 5; i++)
	{		
			for (int k = 2; k <= 10; k++)
				if (RectInRect(player->GetAtkCol(0)[0][i], monster->GetMonMgr(k, 0)->GetHitCol()))
				{
					monster->GetMonMgr(k, 0)->SetHp(monster->GetMonMgr(k, 0)->GetHp() - player->GetAtk());
					monster->GetMonMgr(k, 0)->SetIsHit(true);
				}
				 
	}
	
	for (int k = 2; k <= 10; k++)
		if (RectInRect(player->GetAtkCol(1)[0][0], monster->GetMonMgr(k, 0)->GetHitCol()))
		{
			//monster->GetMonMgr(k, 0)->SetHp(monster->GetMonMgr(k, 0)->GetHp() - player->GetAtk());
			monster->GetMonMgr(k, 0)->SetIsHit(true);
		}

	for (int k = 2; k <= 10; k++)
		if (RectInRect(player->GetAtkCol(2)[0][0], monster->GetMonMgr(k, 0)->GetHitCol()))
		{
			//monster->GetMonMgr(k, 0)->SetHp(monster->GetMonMgr(k, 0)->GetHp() - player->GetAtk());
			monster->GetMonMgr(k, 0)->SetIsHit(true);
		}

	for (int i = 0; i < 5; i++)
	{
		for (int k = 2; k <= 10; k++)
			if (RectInRect(player->GetAtkCol(4)[0][i], monster->GetMonMgr(k, 0)->GetHitCol()))
			{
				monster->GetMonMgr(k, 0)->SetHp(monster->GetMonMgr(k, 0)->GetHp() - player->GetAtk());
				monster->GetMonMgr(k, 0)->SetIsHit(true);
			}

	}


	
}

void CheckCollision::PlayerHitVsMonHit()
{

	RECT playerRc = player->GetHitCol();

	for (int i = 2; i <= 10; i++)
	{
		RECT monsterRc = monster->GetMonMgr(i, 0)->GetAtkCol();
		RECT interRcet;

		if (IntersectRect(&interRcet, &playerRc, &monsterRc))
		{
			SetRect(&interRcet, 0, 0
				, interRcet.right - interRcet.left
				, interRcet.bottom - interRcet.top);

			//위 아래 충돌
			if (interRcet.right > interRcet.bottom)
			{
				if ((playerRc.bottom + playerRc.top) / 2
					< (monsterRc.bottom + monsterRc.top) / 2)
				{
					FPOINT a;
					a.x = player->GetPos().x;
					a.y = player->GetPos().y - interRcet.bottom / 2;
					player->SetPos(a);
					a.x = monster->GetMonMgr(i, 0)->GetPos().x;
					a.y = monster->GetMonMgr(i, 0)->GetPos().y + interRcet.bottom / 2;
					player->SetPos(a);
				}
				else
				{
					FPOINT a;
					a.x = player->GetPos().x;
					a.y = player->GetPos().y + interRcet.bottom / 2;
					player->SetPos(a);
					a.x = monster->GetMonMgr(i, 0)->GetPos().x;
					a.y = monster->GetMonMgr(i, 0)->GetPos().y - interRcet.bottom / 2;
					player->SetPos(a);
				}
			}
			//오른쪽 왼쪽 충돌
			else//if(interRcet.right < interRcet.bottom)
			{
				if ((playerRc.right + playerRc.left) / 2
					< (monsterRc.right + monsterRc.left) / 2)
				{
					FPOINT a;
					a.x = player->GetPos().x - interRcet.right / 2;
					a.y = player->GetPos().y;
					player->SetPos(a);
					a.x = monster->GetMonMgr(i, 0)->GetPos().x + interRcet.right / 2;
					a.y = monster->GetMonMgr(i, 0)->GetPos().y;
					player->SetPos(a);
				}
				else
				{
					FPOINT a;
					a.x = player->GetPos().x + interRcet.right / 2;
					a.y = player->GetPos().y;
					player->SetPos(a);
					a.x = monster->GetMonMgr(i, 0)->GetPos().x - interRcet.right / 2;
					a.y = monster->GetMonMgr(i, 0)->GetPos().y;
					player->SetPos(a);
				}
			}
		}
	}
}
