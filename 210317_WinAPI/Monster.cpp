#include "Monster.h"

#include "Monster_SwordMan.h"
#include "Monster_Archer.h"
#include "MonsterManager.h"

HRESULT Monster::Init(vector<BATTLE_ZONE> rc)
{
	stage02Mon[0] = new Monster_SwordMan();
	stage03Mon[0] = new Monster_SwordMan();
	stage04Mon[0] = new Monster_SwordMan();
	stage05Mon[0] = new Monster_SwordMan();
	stage06Mon[0] = new Monster_SwordMan();
	stage07Mon[0] = new Monster_SwordMan();
	stage08Mon[0] = new Monster_SwordMan();
	stage09Mon[0] = new Monster_SwordMan();
	stage10Mon[0] = new Monster_SwordMan();
	FPOINT a;
	for (int i = 0; i < rc.size(); i++)
	{		
		if (rc[i].index == 2)
		{
			a.x = rc[i].rect.left + 40 *5;
			a.y = rc[i].rect.top + 40 * 5;
			stage02Mon[0]->SetStartPos(a,rc[i].rect);
		}
		if (rc[i].index == 3)
		{
			a.x = rc[i].rect.left + 40 * 3;
			a.y = rc[i].rect.top + 40 * 3;
			stage03Mon[0]->SetStartPos(a, rc[i].rect);
		}
		if (rc[i].index == 4)
		{
			a.x = rc[i].rect.left + 40 * 2 ;
			a.y = rc[i].rect.top + 40 * 2;
			stage04Mon[0]->SetStartPos(a, rc[i].rect);\
		}
		if (rc[i].index == 5)
		{
			a.x = rc[i].rect.left + 40 * 7;
			a.y = rc[i].rect.top + 40 * 2;
			stage05Mon[0]->SetStartPos(a, rc[i].rect);
		}
		if (rc[i].index == 6)
		{
			a.x = rc[i].rect.left + 40 * 7;
			a.y = rc[i].rect.top + 40 * 7;
			stage06Mon[0]->SetStartPos(a, rc[i].rect);
		}
		if (rc[i].index == 7)
		{
			a.x = rc[i].rect.left + 40 * 6;
			a.y = rc[i].rect.top + 40 * 4;
			stage07Mon[0]->SetStartPos(a, rc[i].rect);
			
		}
		if (rc[i].index == 8)
		{
			a.x = rc[i].rect.left + 40 * 3;
			a.y = rc[i].rect.top + 40 * 7;
			stage08Mon[0]->SetStartPos(a, rc[i].rect);			
		}
		if (rc[i].index == 9)
		{
			a.x = rc[i].rect.left + 40 * 7;
			a.y = rc[i].rect.top + 40 * 7;
			stage09Mon[0]->SetStartPos(a, rc[i].rect);
		}
		if (rc[i].index == 10)
		{
			a.x = rc[i].rect.left + 40 * 3;
			a.y = rc[i].rect.top + 40 * 3;
			stage10Mon[0]->SetStartPos(a, rc[i].rect);
		}		
	}
	stage02Mon[0]->SetPlayer(player);
	stage03Mon[0]->SetPlayer(player);
	stage04Mon[0]->SetPlayer(player);
	stage05Mon[0]->SetPlayer(player);
	stage06Mon[0]->SetPlayer(player);
	stage07Mon[0]->SetPlayer(player);
	stage08Mon[0]->SetPlayer(player);
	stage09Mon[0]->SetPlayer(player);
	stage10Mon[0]->SetPlayer(player);

	stage02Mon[0]->Init();
	stage03Mon[0]->Init();
	stage04Mon[0]->Init();
	stage05Mon[0]->Init();
	stage06Mon[0]->Init();
	stage07Mon[0]->Init();
	stage08Mon[0]->Init();
	stage09Mon[0]->Init();
	stage10Mon[0]->Init();


//	for (int i = 0; i < 3; i++)
//	{
//		if (i < 3 && i % 2 == 0)
//			stage1Mon[i] = new Monster_Archer();
//		else
//			stage1Mon[i] = new Monster_SwordMan();
//
//		stage2Mon[0] = new Monster_SwordMan();		
//		stage3Mon[0] = new Monster_SwordMan();
//		
//
//		if (i < 2 && i % 1 == 0)
//			stage4Mon[i] = new Monster_Archer();
//		else
//			stage4Mon[i] = new Monster_SwordMan();
//
//
//		if (i < 3 && i % 2 == 0)
//			stage5Mon[i] = new Monster_Archer();
//		else
//			stage5Mon[i] = new Monster_SwordMan();
//
//		if (i < 4 && i % 2 == 0)
//			stage6Mon[i] = new Monster_Archer();
//		else
//			stage6Mon[i] = new Monster_SwordMan();
//		
//
//		if (i < 3 && i % 2 == 0)
//			stage7Mon[i] = new Monster_Archer();
//		else
//			stage7Mon[i] = new Monster_SwordMan();
//
//
//		if (i < 2 && i % 2 == 0)
//			stage8Mon[i] = new Monster_Archer();
//		else
//		
//			stage8Mon[i] = new Monster_SwordMan();
//
//
//		stage9Mon[0] = new Monster_SwordMan();
//	}
//	//pos.resize(rc.size(),vector<FPOINT>(3));
//	RECT thisRc;
//
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < rc.size(); j++)
//		{
//			if (i < 3)
//			{
//
//				if (rc[j].index == 1)
//				{
//					pos.x = rc[j].rect.left + (((rc[j].rect.right - rc[j].rect.left) / 3) * (i + 1));
//					pos.y = rc[j].rect.left + (((rc[j].rect.bottom - rc[j].rect.top) / 3) * (i + 1));
//					thisRc = rc[j].rect;
//					stage1Mon[i]->SetStartPos(pos, thisRc);
//				}
//			}
//
//
//			if (rc[j].index == 2)
//			{
//				pos.x = rc[j].rect.left + (((rc[j].rect.right - rc[j].rect.left) / 2));
//				pos.y = rc[j].rect.left + (((rc[j].rect.bottom - rc[j].rect.top) / 2));
//				thisRc = rc[j].rect;
//				stage2Mon[0]->SetStartPos(pos, thisRc);
//			}
//
//
//			if (rc[j].index == 3)
//			{
//				pos.x = rc[j].rect.left + (((rc[j].rect.right - rc[j].rect.left) / 2));
//				pos.y = rc[j].rect.left + (((rc[j].rect.bottom - rc[j].rect.top) / 2));
//				thisRc = rc[j].rect;
//				stage3Mon[0]->SetStartPos(pos, thisRc);
//			}
//
//
//
//			if (i < 2)
//			{
//				if (rc[j].index == 4)
//				{
//					pos.x = rc[j].rect.left + (((rc[j].rect.right - rc[j].rect.left) / 2) * (i + 1));
//					pos.y = rc[j].rect.left + (((rc[j].rect.bottom - rc[j].rect.top) / 2) * (i + 1));
//					thisRc = rc[j].rect;
//					stage4Mon[i]->SetStartPos(pos, thisRc);
//				}
//			}
//
//
//			if (i < 3)
//			{
//
//				if (rc[j].index == 5)
//				{
//					pos.x = rc[j].rect.left + (((rc[j].rect.right - rc[j].rect.left) / 3) * (i + 1));
//					pos.y = rc[j].rect.left + (((rc[j].rect.bottom - rc[j].rect.top) / 3) * (i + 1));
//					thisRc = rc[j].rect;
//					stage5Mon[i]->SetStartPos(pos, thisRc);
//				}
//			}
//
//			if (i < 4)
//			{
//
//				if (rc[j].index == 6)
//				{
//					pos.x = rc[j].rect.left + (((rc[j].rect.right - rc[j].rect.left) / 4) * (i + 1));
//					pos.y = rc[j].rect.left + (((rc[j].rect.bottom - rc[j].rect.top) / 4) * (i + 1));
//					thisRc = rc[j].rect;
//					stage6Mon[i]->SetStartPos(pos, thisRc);
//				}
//			}
//
//
//			if (i < 3)
//			{
//
//				if (rc[j].index == 7)
//				{
//					pos.x = rc[j].rect.left + (((rc[j].rect.right - rc[j].rect.left) / 3) * (i + 1));
//					pos.y = rc[j].rect.left + (((rc[j].rect.bottom - rc[j].rect.top) / 3) * (i + 1));
//					thisRc = rc[j].rect;
//					stage7Mon[i]->SetStartPos(pos, thisRc);
//				}
//			}
//
//
//			if (i < 2)
//			{
//				if (rc[j].index == 8)
//				{
//					pos.x = rc[j].rect.left + (((rc[j].rect.right - rc[j].rect.left) / 2) * (i + 1));
//					pos.y = rc[j].rect.left + (((rc[j].rect.bottom - rc[j].rect.top) / 2) * (i + 1));
//					thisRc = rc[j].rect;
//					stage8Mon[i]->SetStartPos(pos, thisRc);
//				}
//			}
//
//			if (rc[j].index == 3)
//			{
//				pos.x = rc[j].rect.left + (((rc[j].rect.right - rc[j].rect.left) / 2));
//				pos.y = rc[j].rect.left + (((rc[j].rect.bottom - rc[j].rect.top) / 2));
//				thisRc = rc[j].rect;
//				stage9Mon[0]->SetStartPos(pos, thisRc);
//			}
//		}
//	}
//	for (int i = 0; i < 3; i++)
//	{
//
//
//		if (i < 3)
//			stage1Mon[i]->SetPlayer(player);
//
//		stage2Mon[0]->SetPlayer(player);
//		stage3Mon[0]->SetPlayer(player);
//
//
//		if (i < 2)
//			stage4Mon[i]->SetPlayer(player);
//
//
//		if (i < 3)
//			stage5Mon[i]->SetPlayer(player);
//
//		if (i < 4)
//			stage6Mon[i]->SetPlayer(player);
//
//
//		if (i < 3)
//			stage7Mon[i]->SetPlayer(player);
//
//
//		if (i < 2)
//			stage8Mon[i]->SetPlayer(player);
//
//
//		stage9Mon[0]->SetPlayer(player);
//	}
//	
//	for (int i = 0; i < 3; i++)
//	{
//		
//		
//		if (i < 3)
//			stage1Mon[i]->Init();
//
//		stage2Mon[0]->Init();
//		stage3Mon[0]->Init();
//
//
//		if (i < 2)
//			stage4Mon[i]->Init();
//
//
//		if (i < 3)
//			stage5Mon[i]->Init();
//
//		if (i < 4)
//			stage6Mon[i]->Init();
//
//
//		if (i < 3)
//			stage7Mon[i]->Init();
//
//
//		if (i < 2)
//			stage8Mon[i]->Init();
//
//
//		stage9Mon[0]->Init();
//	}
//
//	
	return S_OK;
}

void Monster::Release()
{
	SAFE_RELEASE(stage02Mon[0]);
	SAFE_RELEASE(stage03Mon[0]);
	SAFE_RELEASE(stage04Mon[0]);
	SAFE_RELEASE(stage05Mon[0]);
	SAFE_RELEASE(stage06Mon[0]);
	SAFE_RELEASE(stage07Mon[0]);
	SAFE_RELEASE(stage08Mon[0]);
	SAFE_RELEASE(stage09Mon[0]);
	SAFE_RELEASE(stage10Mon[0]);
}

void Monster::Update()
{
	stage02Mon[0]->Update();
	stage03Mon[0]->Update();
	stage04Mon[0]->Update();
	stage05Mon[0]->Update();
	stage06Mon[0]->Update();
	stage07Mon[0]->Update();
	stage08Mon[0]->Update();
	stage09Mon[0]->Update();
	stage10Mon[0]->Update();
	/*for (int i = 0; i < 3; i++)
	{
		if (i < 3)
			stage1Mon[i]->Update();

		stage2Mon[1]->Update();
		stage3Mon[1]->Update();


		if (i < 2)
			stage4Mon[i]->Update();


		if (i < 3)
			stage5Mon[i]->Update();

		if (i < 4)
			stage6Mon[i]->Update();


		if (i < 3)
			stage7Mon[i]->Update();


		if (i < 2)
			stage8Mon[i]->Update();


		stage9Mon[0]->Update();
	}*/
}

void Monster::Render(HDC hdc)
{
	stage02Mon[0]->Render(hdc);
	stage03Mon[0]->Render(hdc);
	stage04Mon[0]->Render(hdc);
	stage05Mon[0]->Render(hdc);
	stage06Mon[0]->Render(hdc);
	stage07Mon[0]->Render(hdc);
	stage08Mon[0]->Render(hdc);
	stage09Mon[0]->Render(hdc);
	stage10Mon[0]->Render(hdc);
	/*for (int i = 0; i < 3; i++)
	{
		if (i < 3)
			stage1Mon[i]->Render(hdc);

		stage2Mon[1]->Render(hdc);
		stage3Mon[1]->Render(hdc);


		if (i < 2)
			stage4Mon[i]->Render(hdc);


		if (i < 3)
			stage5Mon[i]->Render(hdc);

		if (i < 4)
			stage6Mon[i]->Render(hdc);


		if (i < 3)
			stage7Mon[i]->Render(hdc);


		if (i < 2)
			stage8Mon[i]->Render(hdc);


		stage9Mon[0]->Render(hdc);
	}*/
}

MonsterManager* Monster::GetMonMgr(int i, int j)
{
	switch (i)
	{
	case 2:
		return stage02Mon[j];
		break;
	case 3:
		return stage03Mon[j];
		break;
	case 4:
		return stage04Mon[j];
		break;
	case 5:
		return stage05Mon[j];
		break;
	case 6:
		return stage06Mon[j];
		break;
	case 7:
		return stage07Mon[j];
		break;
	case 8:
		return stage08Mon[j];
		break;
	case 9:
		return stage09Mon[j];
		break;
	case 10:
		return stage10Mon[j];
		break;
	}
	return nullptr;
}
