#include "RandomMap.h"
#include "Image.h"
#include "CommonFunction.h"
#include "CheckCollision.h"
#include "config.h"
#include "Camera.h"
#include "AstarScene.h"
#include <algorithm>

TILE_INFO RandomMap::tileInfo[TILE_X * TILE_Y];

HRESULT RandomMap::Init()
{
	
	img = ImageManager::GetSingleton()->AddImage("EnemyMissile",
		"Image/구슬.bmp", 20, 20, true, RGB(255, 0, 255));
	bin = new Image();
	bin->Init("Image/unknown.bmp", 10000, 10000);
	stage = ImageManager::GetSingleton()->AddImage(
		"샘플타일", "Image/WOL/map/IceBaseTileSetCustom5.bmp", 960*zoomPoint, 560*zoomPoint,
		24, 14);
	vMap.resize(10);
	compareRect.resize(900);
	compareRect2.resize(900);
	minRange = 10;
	maxSelect = 40;
	zoomValue = 1.0f;
	pos.x = WORLDSIZE_X / 2;
	pos.y = WORLDSIZE_Y / 2;
#pragma region 접혀
	vMap[0].sizeX = 20 * TILESIZE;
	vMap[0].sizeY = 20 * TILESIZE;
	vMap[1].sizeX = 20 * TILESIZE;
	vMap[1].sizeY = 20 * TILESIZE;
	vMap[2].sizeX = 11 * TILESIZE;
	vMap[2].sizeY = 12 * TILESIZE;
	vMap[3].sizeX = 9 * TILESIZE;
	vMap[3].sizeY = 10 * TILESIZE;
	vMap[4].sizeX = 20 * TILESIZE;
	vMap[4].sizeY = 10 * TILESIZE;
	vMap[5].sizeX = 20 * TILESIZE;
	vMap[5].sizeY = 17 * TILESIZE;
	vMap[6].sizeX = 16 * TILESIZE;
	vMap[6].sizeY = 14 * TILESIZE;
	vMap[7].sizeX = 12 * TILESIZE;
	vMap[7].sizeY = 20 * TILESIZE;
	vMap[8].sizeX = 17 * TILESIZE;
	vMap[8].sizeY = 17 * TILESIZE;
	vMap[9].sizeX = 12 * TILESIZE;
	vMap[9].sizeY = 14 * TILESIZE;
	//vMap[10].sizeX = 77;
	//vMap[10].sizeY = 55;
	//vMap[11].sizeX = 38;
	//vMap[11].sizeY = 76;
	//vMap[12].sizeX = 86;
	//vMap[12].sizeY = 41;
	//vMap[13].sizeX = 39;
	//vMap[13].sizeY = 84;
	//vMap[14].sizeX = 76;
	//vMap[14].sizeY = 52;
	//vMap[15].sizeX = 53;
	//vMap[15].sizeY = 74;
	//vMap[16].sizeX = 44;
	//vMap[16].sizeY = 66;
	//vMap[17].sizeX = 69;
	//vMap[17].sizeY = 38;
	//vMap[18].sizeX = 76;
	//vMap[18].sizeY = 48;
	//vMap[19].sizeX = 51;
	//vMap[19].sizeY = 76;
	//vMap[20].sizeX = 42;
	//vMap[20].sizeY = 59;
	//vMap[21].sizeX = 63;
	//vMap[21].sizeY = 41;
	//vMap[22].sizeX = 72;
	//vMap[22].sizeY = 54;
	//vMap[23].sizeX = 55;
	//vMap[23].sizeY = 71;
	//vMap[24].sizeX = 39;
	//vMap[24].sizeY = 48;
	//vMap[25].sizeX = 41;
	//vMap[25].sizeY = 39;
	//vMap[26].sizeX = 88;
	//vMap[26].sizeY = 44;
	//vMap[27].sizeX = 47;
	//vMap[27].sizeY = 80;
	//vMap[28].sizeX = 53;
	//vMap[28].sizeY = 52;
	//vMap[29].sizeX = 52;
	//vMap[29].sizeY = 56;
#pragma endregion 접혀
	for (int i = 0; i < 10; i++)
	{
		Load(i);
		for (int j = 0; j < TILE_X * TILE_Y; j++)
		{
			randTile[i][j] = tileInfo[j];
			if (randTile[i][j].tileVar == TILEOPTION::BLANK)randTile[i][j].isAlive = false;
		}
	}

	phaseStart = false;
	phase1 = true;
	phase2 = true;
	phase3 = true;
	phase4 = true;
	phase5 = true;
	phase6 = true;
	phase7 = true;
	phase8 = true;
	phase9 = true;
	phase10 = true;
	viewWorldMap = false;
	for (int i = 0; i < compareRect.size(); i++)
	{
		compareRect[i].left = 0;
		compareRect[i].right = 0;
		compareRect[i].top = 0;
		compareRect[i].bottom = 0;
	}

	int size;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < vMap.size(); i++)
	{

		//int weightX = 0;
		//int weightY = 0;
		//int leftCountX = 0;
		//int rightCountX = 0;
		//int upCountY = 0;
		//int downCountY = 0;		
		//for (int i = 1; i < vMap.size(); i++)
		//{
		//	if (vMap[i].pos.x > WORLDSIZE_X / 2 - WINSIZE_X / 2) rightCountX++;
		//	if (vMap[i].pos.x < WORLDSIZE_X / 2 + WINSIZE_X / 2) leftCountX++;
		//	if (vMap[i].pos.y > WORLDSIZE_Y / 2 - WINSIZE_Y / 2) downCountY++;
		//	if (vMap[i].pos.y < WORLDSIZE_Y / 2 + WINSIZE_Y / 2) upCountY++;
		//}
		//if (rightCountX < leftCountX)weightX = 50;
		//else weightX = -100;
		//if (downCountY < upCountY)weightY = 50;
		//else weightY = -100;
		////int size = rand() % 30 + 70;
		//int verRand = rand() % 50 - weightX;
		//int horRand = rand() % 50 - weightY;
		vMap[i].pos.x = WORLDSIZE_X / 2 + (rand() % 100 - 50);
		vMap[i].pos.y = WORLDSIZE_Y / 2 + (rand() % 200 - 100);
		vMap[i].rect.left = vMap[i].pos.x - (vMap[i].sizeX / 2);
		vMap[i].rect.top = vMap[i].pos.y - (vMap[i].sizeY / 2);
		vMap[i].rect.right = vMap[i].pos.x + (vMap[i].sizeX / 2);
		vMap[i].rect.bottom = vMap[i].pos.y + (vMap[i].sizeY / 2);
		vMap[i].dirV = "void";
		vMap[i].dirH = "void";
		vMap[i].index = i;
		vMap[i].select = false;
	}
	for (int i = 0; i < vShop.size(); i++)
	{
		vShop[i].index = i;
		vShop[i].size = 50;
		vShop[i].dirH = "void";
		vShop[i].dirV = "void";
		vShop[i].pos.x = 0;
		vShop[i].pos.y = 0;
		vShop[i].select = false;
	}
	isAstarOn = false;
	astar = new AstarScene();
	astar->Init();
	isViewAstar = false;
	isRandMapOK = false;
	return S_OK;
}

void RandomMap::Release()
{
}

void RandomMap::Update()
{
	if (astar)
	{
		for (int i = 0; i < creatRoad2.size(); i++)
		{
			astar->SetType(creatRoad2[i].rcTile, creatRoad2[i].tileVar);
		}
		//for (int i = 0; i < creatRoad2.size(); i++)
		//{
		//	astar->SetType(creatRoad2[i].rcTile, creatRoad2[i].tileVar);
		//}
		if (astar->GetIsAstarOk())
		{
			SetEnd2();
			for (int i = 0; i < creatRoad.size(); i++)
			{
				creatRoad2.push_back(creatRoad[i]);
			}

			SAFE_RELEASE(astar);
		}
		if (TotalTileIndex.size() <= 2)
		{
			for (int i = 0; i < creatRoad2.size(); i++)
			{
				if (creatRoad2[i].tileVar == TILEOPTION::WAY)
				{
					creatRoad2[i].frameX = 5;
					creatRoad2[i].frameY = 6;
				}
			}
		}
	}
	Camera::GetSingleton()->SetTarget(this);
	for (int i = 0; i < vMap.size(); i++)
	{
		int size = vMap[i].rect.right - vMap[i].rect.left;
		vMap[i].rect.left = vMap[i].pos.x - (vMap[i].sizeX / 2);
		vMap[i].rect.top = vMap[i].pos.y - (vMap[i].sizeY / 2);
		vMap[i].rect.right = vMap[i].pos.x + (vMap[i].sizeX / 2);
		vMap[i].rect.bottom = vMap[i].pos.y + (vMap[i].sizeY / 2);
	}
	for (int i = 0; i < compareRect.size(); i++)
	{
		compareRect[i].left = 0;
		compareRect[i].top = 0;
		compareRect[i].right = 0;
		compareRect[i].bottom = 0;
	}
#pragma region 촬영 키입력 절차
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		pos.x -= 10;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		pos.x += 10;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
		pos.y -= 10;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
		pos.y += 10;


	//if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
	//{
	//	CheckCollision();//마지막에 한번 더 해주는게 이쁘게 퍼지네
	//	RemewalRect();
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))
	//{
	//	CheckCollisionAS();
	//	RemewalRect();

	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown('D'))
	//{
	//	CheckCollisionAS2();
	//	RemewalRect();
	//}
	//if (KeyManager::GetSingleton()->IsStayKeyDown('F'))
	//{
	//	CheckCollisionAS3();//나중에 너무 멀면 골라서 좀 더 모아주는걸로
	//	RemewalRect();
	//}
	//if (KeyManager::GetSingleton()->IsStayKeyDown('G'))
	//{
	//	CheckCollisionAS4();
	//	RemewalRect();
	//	SelectMap();
	//	RemewalRect();
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown('H'))
	//{
	//	EraseMap();
	//	RemewalRect();
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
	//{
	//	farMap();
	//	RemewalRect();
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown('K'))
	//{
	//	MatchRect();
	//	RemewalRect();
	//	FillTile();
	//	RemewalRect();
	//	//eraseRect();
	//	phase8 = false;
	//}
	//if (KeyManager::GetSingleton()->IsOnceKeyDown('L'))
	//{
	//	SetStart();
	//	RemewalRect();
	//}	
	//if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
	//{
	//	if (phase9 && !phase8 && TotalTileIndex.size() > 1)
	//	{
	//		SetEnd();
	//		//if (TotalTileIndex.size() <= 1) phase9 = false;
	//	}
	//	else
	//	{
	//		if (astar)
	//		{
	//			SAFE_RELEASE(astar);

	//		}
	//		addWall();
	//		RemainderTile();
	//		
	//		isRandMapOK = true;
	//	}
	//	viewWorldMap = true;
	//}
#pragma endregion 촬영 키입력 절차

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
		phaseStart = true;
	if (KeyManager::GetSingleton()->IsStayKeyDown('Q'))
	{
		isViewAstar = true;
	}
	else isViewAstar = false;


	//if (phaseStart)
	{

		if (phase1)
		{
			for (int i = 0; i < 30; i++)
				CheckCollision();//마지막에 한번 더 해주는게 이쁘게 퍼지네
			RemewalRect();
			phase1 = false;
		}
		if (phase2)
		{
			CheckCollisionAS();
			RemewalRect();
			phase2 = false;
		}
		if (phase3)
		{
			for (int i = 0; i < 10; i++)
				CheckCollisionAS2();
			RemewalRect();
			phase3 = false;
		}
		if (phase4)
		{
			for (int i = 0; i < 10; i++)
				CheckCollisionAS3();//나중에 너무 멀면 골라서 좀 더 모아주는걸로
			RemewalRect();
			phase4 = false;
		}
		if (phase5)
		{
			for (int i = 0; i < 10; i++)
			{
				CheckCollisionAS4();

			}
			SelectMap();
			RemewalRect();
			phase5 = false;
		}
		if (phase6)
		{
			EraseMap();
			RemewalRect();
			phase6 = false;
		}
		if (phase7)
		{
			for (int i = 0; i < 5; i++)
				farMap();
			RemewalRect();
			phase7 = false;
		}
		if (phase8)
		{
			MatchRect();
			RemewalRect();
			FillTile();
			SetStart();
			//eraseRect();
			//if (isAstarOn) astar->Init();

			phase8 = false;
		}
		if (phase9 && !phase8 && TotalTileIndex.size() > 1)
		{
			SetEnd();
			//if (TotalTileIndex.size() <= 1) phase9 = false;
		}
		else
		{
			if (astar)
			{
				SAFE_RELEASE(astar);

			}
			addWall();
			RemainderTile();
			isRandMapOK = true;
		}
	}
	if (!phase8)
	{
		if (astar)	astar->Update();
	}

}



void RandomMap::Render(HDC hdc)
{
	POINT screenPos;
	screenPos.x = pos.x - Camera::GetSingleton()->GetPos().x;
	screenPos.y = pos.y - Camera::GetSingleton()->GetPos().y;

	img->Render(hdc, screenPos.x, screenPos.y, true);
	bin->Render(hdc);
	PatBlt(hdc, 0, 0, WORLDSIZE_X, WORLDSIZE_Y, BLACKNESS);
	//HBRUSH brush = CreateSolidBrush(NULL_BRUSH);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
	POINT rectPos[10];
	FPOINT randTilePos[10];
	
	if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		if(astar)	astar->Render(hdc);
	}

	//if (!viewWorldMap)
	{
		//if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
		if(!viewWorldMap)
			for (int i = 0; i < vMap.size(); i++)
			{
				rectPos[i].x = vMap[i].pos.x - Camera::GetSingleton()->GetPos().x;
				rectPos[i].y = vMap[i].pos.y - Camera::GetSingleton()->GetPos().y;
				//Rectangle(hdc, vMap[i].pos.x - vMap[i].width, vMap[i].pos.y - vMap[i].height, vMap[i].pos.x + vMap[i].width, vMap[i].pos.y + vMap[i].height);
				int width = vMap[i].rect.right - vMap[i].rect.left;
				int height = vMap[i].rect.bottom - vMap[i].rect.top;
				if (vMap[i].select == true)
				{
					brush = CreateSolidBrush(RGB(0, 200, 0));
					oldBrush = (HBRUSH)SelectObject(hdc, brush);
				}

				RenderRectToCenter(hdc, rectPos[i].x* zoomPoint, rectPos[i].y* zoomPoint, width* zoomPoint, height* zoomPoint);
				//Rectangle(hdc, vMap[i].rect.left, vMap[i].rect.top, vMap[i].rect.right, vMap[i].rect.bottom);
				if (vMap[i].select == true)
				{
					SelectObject(hdc, oldBrush);
					DeleteObject(brush);
					//wsprintf(szText, "당첨 , %d", i);
					//TextOut(hdc, rectPos[i].x, rectPos[i].y, szText, strlen(szText));
				}
				else
				{
					//wsprintf(szText, "%d", i);
					//TextOut(hdc, rectPos[i].x, rectPos[i].y, szText, strlen(szText));
				}
			}
		//wsprintf(szText, "월드X%d , 월드X%d", (int)pos.x, (int)pos.y);
		//TextOut(hdc, 500, 50, szText, strlen(szText));



		//Rectangle(hdc, sibal.left, sibal.top, sibal.right, sibal.bottom);

		//SelectObject(hdc, oldBrush);
		//DeleteObject(brush);

		if (!phase8 && isViewAstar)
		{
			//if (astar)	astar->Render(hdc);
		}
		vector<POINT>createWayPos;
		createWayPos.resize(creatRoad2.size());
		for (int i = 0; i < creatRoad2.size(); i++)
		{
			createWayPos[i].x = creatRoad2[i].rcTile.left - Camera::GetSingleton()->GetPos().x;
			createWayPos[i].y = creatRoad2[i].rcTile.top - Camera::GetSingleton()->GetPos().y;
			stage->FrameRender(hdc,
				createWayPos[i].x* zoomPoint,
				createWayPos[i].y* zoomPoint,
				creatRoad2[i].frameX,
				creatRoad2[i].frameY, zoomPoint
			);
			//	wsprintf(szText, "%d", creatRoad2[i].tileVar);
				//TextOut(hdc, createWayPos[i].x+20, createWayPos[i].y+20, szText, strlen(szText));
		}
		if (!phase8 && !isViewAstar)
		{
			for (int i = 0; i < matchRC.size(); i++)
			{
				for (int j = 0; j < TILE_X * TILE_Y; j++) {
					if (randTile[matchRC[i]][j].tileVar != BLANK && randTile[matchRC[i]][j].isAlive)
					{
						randTilePos[i].x = randTile[matchRC[i]][j].rcTile.left - Camera::GetSingleton()->GetPos().x;
						randTilePos[i].y = randTile[matchRC[i]][j].rcTile.top - Camera::GetSingleton()->GetPos().y;
						stage->FrameRender(hdc,
							randTilePos[i].x* zoomPoint,
							randTilePos[i].y* zoomPoint,
							randTile[matchRC[i]][j].frameX,
							randTile[matchRC[i]][j].frameY, zoomPoint);
					}
					//wsprintf(szText, "%d", randTile[matchRC[i]][j].tileVar);
					//TextOut(hdc, randTilePos[i].x + 20, randTilePos[i].y + 20, szText, strlen(szText));
				}
			}
		}
	}

	

	if (viewWorldMap&& worldTile.size())
	{
		int mapClientPosX;
		int mapClientPosY;
		POINT playerClientPos;
		POINT culling;
		culling.y = pos.y / 40;
		culling.x = pos.x / 40;		
		//if (culling.y - 15 >= 0 && culling.y + 15 <= 124 && culling.x - 30 >= 0 && culling.x + 30 <= 124)
		for (int i = 0; i <= 125; i++)
		{
			for (int j = 0; j <=125; j++)
			{
				if (i < 0 || i > 124 || j < 0 || j > 124) continue;
				mapClientPosX = worldTile[i][j].rcTile.left - Camera::GetSingleton()->GetPos().x;
				mapClientPosY = worldTile[i][j].rcTile.top - Camera::GetSingleton()->GetPos().y;

				if (worldTile[i][j].tileVar != BLANK)
				{
					stage->FrameRender(hdc,
						mapClientPosX* zoomPoint,
						mapClientPosY* zoomPoint,
						worldTile[i][j].frameX,
						worldTile[i][j].frameY, zoomPoint
					);
				}
				//wsprintf(szText, "%d", map2[i][j].tileVar);
				//TextOut(hdc, mapClientPosX, mapClientPosY, szText, strlen(szText));
				//if (map2[i][j].tileVar == WALL || map2[i][j].tileVar == WALLTWO)
				//Rectangle(hdc, mapClientPosX, mapClientPosY, mapClientPosX+40, mapClientPosY+40);
			}
		}
	}
}

vector<BATTLE_ZONE>* RandomMap::GetMapRect()
{

	battleZone.resize(10);
	int index = -1;
	for (int i = 1; i < vMap.size(); i++)
	{

		if (vMap[i].sizeX == 20 * TILESIZE &&
			vMap[i].sizeY == 20 * TILESIZE)//2
		{
			index++;
			

			battleZone[index].index = 2;
			battleZone[index].rect.left = vMap[i].rect.left + TILESIZE * 3;
			battleZone[index].rect.right = vMap[i].rect.right - TILESIZE;
			battleZone[index].rect.top = vMap[i].rect.top + TILESIZE*4;
			battleZone[index].rect.bottom = vMap[i].rect.bottom - TILESIZE*1;			
			
		}		

		if (vMap[i].sizeX == 11 * TILESIZE &&
			vMap[i].sizeY == 12 * TILESIZE)//3
		{
			index++;
			battleZone[index].index = 3;
			battleZone[index].rect.left = vMap[i].rect.left + TILESIZE * 1;
			battleZone[index].rect.right = vMap[i].rect.right;
			battleZone[index].rect.top = vMap[i].rect.top + TILESIZE * 4;
			battleZone[index].rect.bottom = vMap[i].rect.bottom - TILESIZE * 1;
		}
		if (vMap[i].sizeX == 9 * TILESIZE &&
			vMap[i].sizeY == 10 * TILESIZE)//4
		{
			index++;
			battleZone[index].index = 4;
			battleZone[index].rect.left = vMap[i].rect.left + TILESIZE * 1;
			battleZone[index].rect.right = vMap[i].rect.right - TILESIZE * 1;
			battleZone[index].rect.top = vMap[i].rect.top + TILESIZE * 4;
			battleZone[index].rect.bottom = vMap[i].rect.bottom - TILESIZE * 1;
		}
		if (vMap[i].sizeX == 20 * TILESIZE &&
			vMap[i].sizeY == 10 * TILESIZE)//5
		{
			index++;
			battleZone[index].index = 5;
			battleZone[index].rect.left = vMap[i].rect.left + TILESIZE * 1;
			battleZone[index].rect.right = vMap[i].rect.right - TILESIZE * 1;
			battleZone[index].rect.top = vMap[i].rect.top + TILESIZE * 4;
			battleZone[index].rect.bottom = vMap[i].rect.bottom - TILESIZE * 1;
		}
		if (vMap[i].sizeX == 20 * TILESIZE &&
			vMap[i].sizeY == 17 * TILESIZE)
		{
			index++;
			battleZone[index].index = 6;
			battleZone[index].rect.left = vMap[i].rect.left + TILESIZE * 5;
			battleZone[index].rect.right = vMap[i].rect.right - TILESIZE * 4;
			battleZone[index].rect.top = vMap[i].rect.top + TILESIZE * 4;
			battleZone[index].rect.bottom = vMap[i].rect.bottom - TILESIZE * 1;
		}
		if (vMap[i].sizeX == 16 * TILESIZE &&
			vMap[i].sizeY == 14 * TILESIZE)
		{
			index++;
			battleZone[index].index = 7;
			battleZone[index].rect.left = vMap[i].rect.left + TILESIZE * 1;
			battleZone[index].rect.right = vMap[i].rect.right - TILESIZE * 1;
			battleZone[index].rect.top = vMap[i].rect.top + TILESIZE * 4;
			battleZone[index].rect.bottom = vMap[i].rect.bottom - TILESIZE * 1;
		}
		if (vMap[i].sizeX == 12 * TILESIZE &&
			vMap[i].sizeY == 20 * TILESIZE)
		{
			index++;
			battleZone[index].index = 8;
			battleZone[index].rect.left = vMap[i].rect.left + TILESIZE * 1;
			battleZone[index].rect.right = vMap[i].rect.right - TILESIZE * 1;
			battleZone[index].rect.top = vMap[i].rect.top + TILESIZE * 4;
			battleZone[index].rect.bottom = vMap[i].rect.bottom - TILESIZE *1;
		}
		if (vMap[i].sizeX == 17 * TILESIZE &&
			vMap[i].sizeY == 17 * TILESIZE)
		{
			index++;
			battleZone[index].index = 9;
			battleZone[index].rect.left = vMap[i].rect.left + TILESIZE * 1;
			battleZone[index].rect.right = vMap[i].rect.right - TILESIZE * 1;
			battleZone[index].rect.top = vMap[i].rect.top + TILESIZE * 4;
			battleZone[index].rect.bottom = vMap[i].rect.bottom - TILESIZE * 1;
		}

		if (vMap[i].sizeX == 12 * TILESIZE &&
			vMap[i].sizeY == 14 * TILESIZE)
		{
			index++;
			battleZone[index].index = 10;
			battleZone[index].rect.left = vMap[i].rect.left + TILESIZE * 1;
			battleZone[index].rect.right = vMap[i].rect.right - TILESIZE * 1;
			battleZone[index].rect.top = vMap[i].rect.top + TILESIZE * 4;
			battleZone[index].rect.bottom = vMap[i].rect.bottom + TILESIZE * 1;
		}
	}
	return &battleZone;
}

void RandomMap::CheckCollision()
{

	for (int i = 1; i < vMap.size(); i++)
	{
		for (int j = 0; j < vMap.size(); j++)
		{
			if (i == j) continue;
			if (i == 0) continue;

			int currIndex = i * vMap.size() + j;
			//if (compareRect[currIndex].right > 0 || compareRect[currIndex].bottom > 0)
			if (IntersectRect(&compareRect[currIndex], &vMap[i].rect, &vMap[j].rect))
			{
				SetRect(&compareRect[currIndex], 0, 0
					, compareRect[currIndex].right - compareRect[currIndex].left
					, compareRect[currIndex].bottom - compareRect[currIndex].top);

				if (compareRect[currIndex].right > 0 || compareRect[currIndex].bottom > 0)
				{
					{
						if (compareRect[currIndex].right > compareRect[currIndex].bottom)
						{
							if ((vMap[i].rect.bottom + vMap[i].rect.top) / 2
								< (vMap[j].rect.bottom + vMap[j].rect.top) / 2)
							{
								vMap[i].pos.y -= TILESIZE;
								compareRect[currIndex].right = 0;
								compareRect[currIndex].bottom = 0;
								vMap[i].dirV = "Top";
							}
							else
							{
								vMap[i].pos.y += TILESIZE;
								compareRect[currIndex].right = 0;
								compareRect[currIndex].bottom = 0;
								vMap[i].dirV = "Bottom";
							}
						}
						//오른쪽 왼쪽 충돌
						else
						{
							if ((vMap[i].rect.right + vMap[i].rect.left) / 2
								< (vMap[j].rect.right + vMap[j].rect.left) / 2)
							{
								vMap[i].pos.x -= TILESIZE;
								compareRect[currIndex].right = 0;
								compareRect[currIndex].bottom = 0;
								vMap[i].dirH = "Left";
							}
							else
							{
								vMap[i].pos.x += TILESIZE;
								compareRect[currIndex].right = 0;
								compareRect[currIndex].bottom = 0;
								vMap[i].dirH = "Right";
							}
						}
					}

					// 바뀐 위치에 따라 렉트 값 재설정
					vMap[i].rect = GetRectToCenter(vMap[i].pos.x, vMap[i].pos.y
						, vMap[i].sizeX, vMap[i].sizeY);

				}

			}//break;
		}

	}
}

void RandomMap::CheckCollisionAS()
{
	for (int i = 1; i < vMap.size(); i++)
	{
		for (int j = 0; j < vMap.size(); j++)
		{
			if (i == j) continue;
			if (i == 0) continue;

			int currIndex = i * vMap.size() + j;
			//if (compareRect[currIndex].right > 0 || compareRect[currIndex].bottom > 0)
			if (IntersectRect(&compareRect[currIndex], &vMap[i].rect, &vMap[j].rect))
			{
				SetRect(&compareRect[currIndex], 0, 0
					, compareRect[currIndex].right - compareRect[currIndex].left
					, compareRect[currIndex].bottom - compareRect[currIndex].top);
				if (compareRect[currIndex].right > 0 || compareRect[currIndex].bottom > 0)
				{
					asIndex.push_back(i);
				}
			}

		}
	}
	asIndex.erase(unique(asIndex.begin(), asIndex.end()), asIndex.end());
	//for (int i = asIndex.size() - 1; i >= 0; i--)
	//{
	//	vMap.erase(vMap.begin() + asIndex[i]);
	//}
	phase2 = false;
}
void RandomMap::CheckCollisionAS2()
{
	for (int i = 0; i < asIndex.size(); i++)
	{
		for (int j = 0; j < vMap.size(); j++)
		{
			if (asIndex[i] == j) continue;
			if (asIndex[i] == 0) continue;

			int currIndex = i * vMap.size() + j;
			//if (compareRect[currIndex].right > 0 || compareRect[currIndex].bottom > 0)
			if (IntersectRect(&compareRect[currIndex], &vMap[asIndex[i]].rect, &vMap[j].rect))
			{
				SetRect(&compareRect[currIndex], 0, 0
					, compareRect[currIndex].right - compareRect[currIndex].left
					, compareRect[currIndex].bottom - compareRect[currIndex].top);

				if (compareRect[currIndex].right > 0 || compareRect[currIndex].bottom > 0)
				{
					if (vMap[asIndex[i]].dirV == "Top")
					{
						vMap[asIndex[i]].pos.y -= compareRect[currIndex].bottom;
						compareRect[currIndex].right = 0;
						compareRect[currIndex].bottom = 0;
					}
					if (vMap[asIndex[i]].dirV == "Bottom")
					{
						vMap[asIndex[i]].pos.y += compareRect[currIndex].bottom;
						compareRect[currIndex].right = 0;
						compareRect[currIndex].bottom = 0;
					}


					if (vMap[asIndex[i]].dirH == "Left")
					{
						vMap[asIndex[i]].pos.x -= compareRect[currIndex].right;
						compareRect[currIndex].right = 0;
						compareRect[currIndex].bottom = 0;
					}
					if (vMap[asIndex[i]].dirH == "Right")
					{
						vMap[asIndex[i]].pos.x += compareRect[currIndex].right;
						compareRect[currIndex].right = 0;
						compareRect[currIndex].bottom = 0;
					}
					//if (vMap[asIndex[i]].dirV == "Top" || vMap[asIndex[i]].dirH == "Left")
					//{
					//	vMap[asIndex[i]].pos.y -= compareRect[currIndex].bottom;
					//	vMap[asIndex[i]].pos.x -= compareRect[currIndex].right;
					//	compareRect[currIndex].right = 0;
					//	compareRect[currIndex].bottom = 0;
					//}
					//if (vMap[asIndex[i]].dirV == "Top" || vMap[asIndex[i]].dirH == "Right")
					//{
					//	vMap[asIndex[i]].pos.y -= compareRect[currIndex].bottom;
					//	vMap[asIndex[i]].pos.x += compareRect[currIndex].right;
					//	compareRect[currIndex].right = 0;
					//	compareRect[currIndex].bottom = 0;
					//}
					//if (vMap[asIndex[i]].dirV == "Bottom" || vMap[asIndex[i]].dirH == "Left")
					//{
					//	vMap[asIndex[i]].pos.y += compareRect[currIndex].bottom;
					//	vMap[asIndex[i]].pos.x -= compareRect[currIndex].right;
					//	compareRect[currIndex].right = 0;
					//	compareRect[currIndex].bottom = 0;
					//}
					//if (vMap[asIndex[i]].dirV == "Bottom" || vMap[asIndex[i]].dirH == "Right")
					//{
					//	vMap[asIndex[i]].pos.y += compareRect[currIndex].bottom;
					//	vMap[asIndex[i]].pos.x += compareRect[currIndex].right;
					//	compareRect[currIndex].right = 0;
					//	compareRect[currIndex].bottom = 0;
					//}					
				}
			}

			// 바뀐 위치에 따라 렉트 값 재설정
			vMap[asIndex[i]].rect = GetRectToCenter(vMap[asIndex[i]].pos.x, vMap[asIndex[i]].pos.y
				, vMap[asIndex[i]].sizeX, vMap[asIndex[i]].sizeY);
		}//break;
	}
	asIndex.clear();

}


void RandomMap::CheckCollisionAS3()
{
	for (int i = 1; i < vMap.size(); i++)
	{
		int compare = 0;
		for (int j = 0; j < vMap.size(); j++)
		{
			if (i == j) continue;
			if (i == 0) continue;

			int currIndex = i * vMap.size() + j;
			//if (compareRect[currIndex].right > 0 || compareRect[currIndex].bottom > 0)
			if (!IntersectRect(&compareRect[currIndex], &vMap[i].rect, &vMap[j].rect))
			{
				compare++;
			}
			else if (IntersectRect(&compareRect[currIndex], &vMap[i].rect, &vMap[j].rect))
			{
				continue;
			}


			// 바뀐 위치에 따라 렉트 값 재설정
			vMap[i].rect = GetRectToCenter(vMap[i].pos.x, vMap[i].pos.y
				, vMap[i].sizeX, vMap[i].sizeY);

		}
		if (compare == vMap.size() - 1)
		{
			if (vMap[i].pos.x < vMap[0].pos.x) vMap[i].pos.x += TILESIZE;
			if (vMap[i].pos.x > vMap[0].pos.x) vMap[i].pos.x -= TILESIZE;
			if (vMap[i].pos.y < vMap[0].pos.y) vMap[i].pos.y += TILESIZE;
			if (vMap[i].pos.y > vMap[0].pos.y) vMap[i].pos.y -= TILESIZE;
		}

	}

}

void RandomMap::CheckCollisionAS4()
{
	for (int i = vMap.size() - 1; i >= 0; i--)
	{
		if (vMap[i].rect.left < vMap[0].rect.left - (vMap[0].rect.right - vMap[0].rect.left) * 4 || vMap[i].rect.right > vMap[0].rect.right + (vMap[0].rect.right - vMap[0].rect.left) * 4 ||
			vMap[i].rect.top < vMap[0].rect.top - (vMap[0].rect.bottom - vMap[0].rect.top) * 4 || vMap[i].rect.bottom > vMap[0].rect.bottom + (vMap[0].rect.bottom - vMap[0].rect.top) * 4)
		{
			vMap.erase(vMap.begin() + i);
		}
	}
}
//5.12 하다 말았음 5.13부터 다시 해야지
void RandomMap::SelectMap()
{

	bool isPerfectNot = false;
	int q = 0;
	vMap[0].select = true;
	for (int k = 0; k < compareRect.size(); k++)
	{
		compareRect[k].left = 0;
		compareRect[k].top = 0;
		compareRect[k].right = 0;
		compareRect[k].bottom = 0;
	}
	for (int i = 0; i < vMap.size(); i++)
	{
		isPerfectNot = false;
		if (q > maxSelect)
		{
			break;
		}
		//if (vMap[i].select == true) continue;			
		for (int j = 0; j < vMap.size(); j++)
		{

			int currIndex = i * vMap.size() + j;
			if (i == 0) continue;
			if (i == j) continue;
			//if (!vMap[j].select) continue;
			//if (vMap[j].select) continue;
			if (vMap[j].select)
			{
				if (IntersectRect(&compareRect[currIndex], &vMap[i].rect, &vMap[j].rect))
				{
					//if (vMap[i].rect.bottom < vMap[j].rect.top)
					//{
					//	if (vMap[j].rect.top - vMap[i].rect.bottom < 5) continue;//i가 위
					//}
					//if (vMap[i].rect.top > vMap[j].rect.bottom)
					//{
					//	if (vMap[i].rect.top - vMap[j].rect.bottom < 5) continue;//i가 아래
					//}
					//if (vMap[i].rect.right < vMap[j].rect.left)
					//{
					//	if (vMap[j].rect.left - vMap[i].rect.right < 5) continue;//i가 왼쪽
					//}
					//if (vMap[i].rect.left > vMap[j].rect.right)
					//{
					//	if (vMap[i].rect.left - vMap[j].rect.right < 5) continue;//i가 왼쪽
					//}
					isPerfectNot = true;
					vMap[i].select = false;
					break;
				}
				if (vMap[i].rect.bottom < vMap[j].rect.top)
				{
					if (vMap[j].rect.top - vMap[i].rect.bottom < minRange)
					{
						isPerfectNot = true;
						vMap[i].select = false;
						break;//i가 위						
					}
				}
				if (vMap[i].rect.top > vMap[j].rect.bottom)
				{
					if (vMap[i].rect.top - vMap[j].rect.bottom < minRange)
					{
						isPerfectNot = true;
						vMap[i].select = false;
						break;//i가 위						
					}
				}
				if (vMap[i].rect.right < vMap[j].rect.left)
				{
					if (vMap[j].rect.left - vMap[i].rect.right < minRange)
					{
						isPerfectNot = true;
						vMap[i].select = false;
						break;//i가 위						
					}
				}
				if (vMap[i].rect.left > vMap[j].rect.right)
				{
					if (vMap[i].rect.left - vMap[j].rect.right < minRange)
					{
						isPerfectNot = true;
						vMap[i].select = false;
						break;//i가 위						
					}
				}
			}


			//0을 선택하고 0에서
			//일정 범위 안에서
			//인접한 면이 없는 거 1개를 선택하고
			//그 1개가 다른 트루인 것과 면이 닿지 않으면 그걸 트루
			//트루가 되면 i++
			//

		}


		if (!isPerfectNot)
		{
			vMap[i].select = true;
			if (vMap[i].select)q++;
		}
	}
}

void RandomMap::CheckMap()
{

	for (int k = 0; k < compareRect.size(); k++)
	{
		compareRect[k].left = -1;
		compareRect[k].top = -1;
		compareRect[k].right = -1;
		compareRect[k].bottom = -1;
	}
	for (int i = 1; i < vMap.size(); i++)
	{
		if (!vMap[i].select) continue;
		if (vMap[i].select)
		{
			for (int j = 0; j < vMap.size(); j++)
			{
				if (!vMap[j].select) continue;
				int currIndex = i * vMap.size() + j;
				if (vMap[j].select == true)
				{
					if (IntersectRect(&compareRect[currIndex], &vMap[i].rect, &vMap[j].rect))
					{
						SetRect(&sibal, compareRect[currIndex].left, compareRect[currIndex].top, compareRect[currIndex].right, compareRect[currIndex].bottom);
						vMap[i].select = false;
					}
				}
				if (vMap[i].rect.bottom < vMap[j].rect.top)
				{
					if (vMap[j].rect.top - vMap[i].rect.bottom < minRange)
					{
						vMap[i].select = false;
						break;
					}
				}
				if (vMap[i].rect.top > vMap[j].rect.bottom)
				{
					if (vMap[i].rect.top - vMap[j].rect.bottom < minRange)
					{
						vMap[i].select = false;
						break;
					}
				}
				if (vMap[i].rect.right < vMap[j].rect.left)
				{
					if (vMap[j].rect.left - vMap[i].rect.right < minRange)
					{
						vMap[i].select = false;
						break;
					}
				}
				if (vMap[i].rect.left > vMap[j].rect.right)
				{
					if (vMap[i].rect.left - vMap[j].rect.right < minRange)
					{
						vMap[i].select = false;
						break;
					}
				}

			}
		}
	}
}
//셀렉트랑 체크 좀 이상한데 일단 냅두고 담주에 교수님께 여쭤보자
void RandomMap::EraseMap()
{
	vector<int>eraseIndex;
	for (int i = 0; i < vMap.size(); i++)
	{
		if (!vMap[i].select)
		{
			eraseIndex.push_back(i);
		}
	}
	for (int i = eraseIndex.size() - 1; i >= 0; i--)
	{
		vMap.erase(vMap.begin() + eraseIndex[i]);
	}

}

void RandomMap::AddShop()
{
	vector<int>q;
	for (int i = 1; i < vMap.size(); i++)
		q.push_back(vMap[i].index);
	for (int i = 1; i < vMap.size() - 1; i++)
	{
		for (int j = i + 1; j < vMap.size(); j++)
		{
			q.insert(q.begin() + j, q[i]);
			q.erase(q.begin() + i + 1);
			break;
		}
	}
	//정렬까지 했는데 이제 뒤에 정렬된걸 앞으로 뽑아서 상점 어디 설치할 지 선택해야함
}
void RandomMap::FillTile()
{
	for (int i = 0; i < vMap.size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (vMap[i].index == j)
			{
				matchRC.push_back(j);
				diffPointX.push_back(vMap[i].rect.left - randTile[j][0].rcTile.left);
				diffPointY.push_back(vMap[i].rect.top - randTile[j][0].rcTile.top);
			}
		}
	}
	for (int i = 0; i < matchRC.size(); i++)
	{
		for (int o = 0; o < TILE_Y; o++)
		{
			for (int p = 0; p < TILE_X; p++)
			{

				randTile[matchRC[i]][o * TILE_X + p].rcTile.left += diffPointX[i];
				randTile[matchRC[i]][o * TILE_X + p].rcTile.top += diffPointY[i];
				randTile[matchRC[i]][o * TILE_X + p].rcTile.right += diffPointX[i];
				randTile[matchRC[i]][o * TILE_X + p].rcTile.bottom += diffPointY[i];
			}
		}
	}

}
void RandomMap::farMap()
{
	for (int i = 0; i < vMap.size(); i++)
	{
		for (int j = 0; j < vMap.size(); j++)
		{

			if (i == 0) continue;
			if (i == j) continue;

			if (vMap[j].select)
			{

			}
			if (vMap[i].rect.bottom < vMap[j].rect.top)
			{
				if (vMap[j].rect.top - vMap[i].rect.bottom < 500)
				{
					//i가 위인데 거리거 400미만;
					vMap[i].pos.y -= 200;
				}
			}
			if (vMap[i].rect.top > vMap[j].rect.bottom)
			{
				if (vMap[i].rect.top - vMap[j].rect.bottom < 500)
				{
					//i가 밑인데 거리거 400미만
					vMap[i].pos.y += 200;
				}
			}
			if (vMap[i].rect.right < vMap[j].rect.left)
			{
				if (vMap[j].rect.left - vMap[i].rect.right < 500)
				{
					//i가 왼인데 거리거 400미만
					vMap[i].pos.x -= 200;
				}
			}
			if (vMap[i].rect.left > vMap[j].rect.right)
			{
				if (vMap[i].rect.left - vMap[j].rect.right < 500)
				{
					//i가 오른인데 거리거 400미만
					vMap[i].pos.x += 200;
				}
			}
		}
		vMap[i].rect = GetRectToCenter(vMap[i].pos.x, vMap[i].pos.y
			, vMap[i].sizeX, vMap[i].sizeY);
	}

	//for (int i = 0; i < vMap.size(); i++)
	//{
	//	for (int j = 0; j < vMap.size(); j++)
	//	{

	//		if (i == 0) continue;
	//		if (i == j) continue;

	//		if (vMap[j].select)
	//		{

	//		}
	//		if (vMap[i].rect.bottom < vMap[j].rect.top)
	//		{
	//			if (vMap[j].rect.top - vMap[i].rect.bottom < 500)
	//			{
	//				//i가 위인데 거리거 400미만;
	//				vMap[i].pos.y -= 100;
	//			}
	//		}		

	//	}
	//}
	//for (int i = 0; i < vMap.size(); i++)
	//{
	//	for (int j = 0; j < vMap.size(); j++)
	//	{

	//		if (i == 0) continue;
	//		if (i == j) continue;
	//		
	//		if (vMap[i].rect.top > vMap[j].rect.bottom)
	//		{
	//			if (vMap[i].rect.top - vMap[j].rect.bottom < 500)
	//			{
	//				//i가 밑인데 거리거 400미만
	//				vMap[i].pos.y += 100;
	//			}
	//		}
	//	}
	//}
	//for (int i = 0; i < vMap.size(); i++)
	//{
	//	for (int j = 0; j < vMap.size(); j++)
	//	{

	//		if (i == 0) continue;
	//		if (i == j) continue;
	//					
	//		if (vMap[i].rect.right < vMap[j].rect.left)
	//		{
	//			if (vMap[j].rect.left - vMap[i].rect.right < 500)
	//			{
	//				//i가 왼인데 거리거 400미만
	//				vMap[i].pos.x -= 100;
	//			}
	//		}			
	//	}
	//}
	//for (int i = 0; i < vMap.size(); i++)
	//{
	//	for (int j = 0; j < vMap.size(); j++)
	//	{

	//		if (i == 0) continue;
	//		if (i == j) continue;

	//		if (vMap[i].rect.left > vMap[j].rect.right)
	//		{
	//			if (vMap[i].rect.left - vMap[j].rect.right < 500)
	//			{
	//				//i가 오른인데 거리거 400미만
	//				vMap[i].pos.x += 100;
	//			}
	//		}
	//	}
	//}

}
void RandomMap::eraseRect()
{
	//for(int i = 0; i< vMap.size(); i++)
	vMap.clear();
}
void RandomMap::RemewalRect()
{
	for (int i = 0; i < vMap.size(); i++)
	{
		vMap[i].rect = GetRectToCenter(vMap[i].pos.x, vMap[i].pos.y
			, vMap[i].sizeX, vMap[i].sizeY);
	}
}
void RandomMap::MatchRect()
{
	for (int i = 0; i < vMap.size(); i++)
	{
		vMap[i].pos.x -= vMap[i].rect.left % 40;
		vMap[i].pos.y -= vMap[i].rect.top % 40;
	}
}
void RandomMap::SetStart()
{
	//배열에 E랑 E가 속한 인덱스 넣음
	POINT inputPos;
	ENDTILEINDEX inputEndIndex;
	for (int i = 0; i < matchRC.size(); i++)
	{
		for (int j = 0; j < TILE_X * TILE_Y; j++) {
			if (randTile[matchRC[i]][j].tileVar == END)
			{

				inputEndIndex.endPos.x = randTile[matchRC[i]][j].rcTile.left + TILESIZE / 2;
				inputEndIndex.endPos.y = randTile[matchRC[i]][j].rcTile.top + TILESIZE / 2;

				//endTileIndex.push_back(inputEndIndex);
				for (int k = 0; k < vMap.size(); k++)
				{
					if (inputEndIndex.endPos.x >= vMap[k].rect.left && inputEndIndex.endPos.x <= vMap[k].rect.right &&
						inputEndIndex.endPos.y >= vMap[k].rect.top && inputEndIndex.endPos.y <= vMap[k].rect.bottom)
					{
						inputEndIndex.index = vMap[k].index;
						//randTile[matchRC[i]][j].index = inputEndIndex.index;
					}
				}
				TotalTileIndex.push_back(inputEndIndex);
			}
		}
	}
	//거리 비교해서 정렬함 잴 뒤가 잴 먼거임
	POINT centerPos{ WORLDSIZE_X / 2 , WORLDSIZE_Y / 2 };
	ENDTILEINDEX save1;
	ENDTILEINDEX save2;
	for (int i = 0; i < TotalTileIndex.size(); i++)
	{
		for (int j = i - 1; j < TotalTileIndex.size(); j++)
		{
			if (j < 0) continue;
			if (lineDistance(centerPos, TotalTileIndex[i].endPos) <= lineDistance(centerPos, TotalTileIndex[j].endPos))
			{
				save1 = TotalTileIndex[j];
				save2 = TotalTileIndex[i];
				TotalTileIndex[j] = save2;
				TotalTileIndex[i] = save1;
			}
		}
	}
}

void RandomMap::SetEnd()
{
	if (!astar)
	{
		astar = new AstarScene();
		astar->Init();
	}

	ENDTILEINDEX save1;
	ENDTILEINDEX save2;
	startTile.push_back(TotalTileIndex[0]);
	for (int i = 1; i < TotalTileIndex.size(); i++)
	{
		endTile.push_back(TotalTileIndex[i]);
	}
	for (int i = 0; i < endTile.size(); i++)
	{
		if (startTile[0].index == endTile[i].index)	endTile.erase(endTile.begin() + i);
		for (int j = i - 1; j < endTile.size(); j++)
		{
			if (startTile[0].index == endTile[j].index)	endTile.erase(endTile.begin() + j);
			if (j < 0) continue;
			if (endTile.size() <= 0 || endTile.size() <= i || endTile.size() <= j) continue;
			if (lineDistance(startTile[0].endPos, endTile[i].endPos) <= lineDistance(startTile[0].endPos, endTile[j].endPos))
			{
				save1 = endTile[j];
				save2 = endTile[i];
				endTile[j] = save2;
				endTile[i] = save1;
			}
		}
	}

	if (endTile.size() <= 0) phase9 = false;
	if (phase9)
	{
		endTile.erase(endTile.begin() + 1, endTile.end());
		TotalTileIndex.erase(TotalTileIndex.begin());
		for (int i = 0; i < TotalTileIndex.size(); i++)
		{
			if (endTile[0].endPos.x == TotalTileIndex[i].endPos.x && endTile[0].endPos.y == TotalTileIndex[i].endPos.y)
			{
				TotalTileIndex.erase(TotalTileIndex.begin() + i);
			}
		}
		POINT start;
		POINT end;
		start.x = startTile[0].endPos.x / 40;
		start.y = startTile[0].endPos.y / 40;
		end.x = endTile[0].endPos.x / 40;
		end.y = endTile[0].endPos.y / 40;

		if (astar)
		{

			for (int i = 0; i < vMap.size(); i++)
			{
				astar->SetWall(vMap[i].rect);
			}
			if (startTile.size() >= 1)
			{
				astar->SetStartTile(start);
			}
			else phase9 = false;
			astar->SetEndTile(end);
			astar->FindPath();
		}
		startTile.clear();
		endTile.clear();
	}
}

void RandomMap::SetEnd2()
{
	if (astar)
	{
		astarFrame.resize(astar->GetFrame().size());
		astarFrame = astar->GetFrame();

		astarType.resize(astar->GetType().size());
		astarType = astar->GetType();

		wayPos.resize(astar->GetWayPos().size());
		wayPos = astar->GetWayPos();
	}
	creatRoad.resize(wayPos.size());
	for (int i = 0; i < creatRoad.size(); i++)
	{

		creatRoad[i].rcTile.left = wayPos[i].x - 20;
		creatRoad[i].rcTile.right = wayPos[i].x + 20;
		creatRoad[i].rcTile.top = wayPos[i].y - 20;
		creatRoad[i].rcTile.bottom = wayPos[i].y + 20;
		creatRoad[i].tileVar = astarType[i];
		creatRoad[i].index = i;
		creatRoad[i].frameY = astarFrame[i].y;
		creatRoad[i].frameX = astarFrame[i].x;
		creatRoad[i].isAlive = true;
	}
}

void RandomMap::RemainderTile()
{
	//for (int k = 0; k < creatRoad2.size(); k++)
	//{
	//	for (int i = 0; i < matchRC.size(); i++)
	//	{			
	//		for (int j = 0; j < TILE_X * TILE_Y; j++)
	//		{	
	//			if (randTile[i][j].tileVar == TILEOPTION::BLANK)
	//			{
	//				randTile[i][j].isAlive = false;
	//			}
	//			//if(k< creatRoad2.size())
	//			if (creatRoad2[k].rcTile.left == randTile[i][j].rcTile.left &&
	//				creatRoad2[k].rcTile.top == randTile[i][j].rcTile.top &&
	//				creatRoad2[k].rcTile.right == randTile[i][j].rcTile.right &&
	//				creatRoad2[k].rcTile.bottom == randTile[i][j].rcTile.bottom)
	//			{					
	//				creatRoad2[k].tileVar = TILEOPTION::WAY;
	//				creatRoad2[k].isAlive = false;										
	//			}
	//			if (creatRoad2[k].tileVar == TILEOPTION::BLANK)
	//			{
	//				creatRoad2[k].isAlive = false;
	//			}
	//		}
	//	}		
	//}

	//for (int i = 0; i < matchRC.size(); i++)
	//{
	//	for (int j = 0; j < TILE_X * TILE_Y; j++)
	//	{
	//		creatRoad2.push_back(randTile[matchRC[i]][j]);
	//	}
	//}
	worldTile.clear();
	worldTile.resize(125, vector<TILE_INFO>(125));



	for (int i = 0; i < ASTAR_TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)	// 가로반복 (x)
		{
			worldTile[i][j].frameX = astar->GetFrame2(i, j).x;
			worldTile[i][j].frameY = astar->GetFrame2(i, j).y;
			worldTile[i][j].tileVar = astar->GetType2(i, j);
			worldTile[i][j].rcTile.left = astar->GetWayPos2(i, j).x - 20;
			worldTile[i][j].rcTile.right = astar->GetWayPos2(i, j).x + 20;
			worldTile[i][j].rcTile.top = astar->GetWayPos2(i, j).y - 20;
			worldTile[i][j].rcTile.bottom = astar->GetWayPos2(i, j).y + 20;
			worldTile[i][j].index = i * ASTAR_TILE_COUNT + j;
			if (worldTile[i][j].tileVar != BLANK) worldTile[i][j].isAlive = true;
		}
	}


}

void RandomMap::addWall()
{
	if (!astar)
	{
		astar = new AstarScene();
		astar->Init();
	}
	for (int i = 0; i < creatRoad2.size(); i++)
	{
		astar->SetType2(creatRoad2[i].rcTile, creatRoad2[i].tileVar, creatRoad2[i].frameX, creatRoad2[i].frameY);

	}
	randTile[0][10].tileVar = TILEOPTION::WAY; randTile[0][9].tileVar = TILEOPTION::WAY; randTile[0][11].tileVar = TILEOPTION::WAY;
	randTile[0][29].tileVar = TILEOPTION::WAY; randTile[0][30].tileVar = TILEOPTION::WAY; randTile[0][31].tileVar = TILEOPTION::WAY;
	randTile[0][49].tileVar = TILEOPTION::WAY; randTile[0][50].tileVar = TILEOPTION::WAY; randTile[0][51].tileVar = TILEOPTION::WAY;
	randTile[0][69].tileVar = TILEOPTION::WAY; randTile[0][70].tileVar = TILEOPTION::WAY; randTile[0][71].tileVar = TILEOPTION::WAY;
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < TILE_X * TILE_Y; j++)
		{
			if (randTile[i][j].tileVar == BLANK) continue;

			astar->SetType2(randTile[i][j].rcTile, randTile[i][j].tileVar, randTile[i][j].frameX, randTile[i][j].frameY);
		}

	}
}

float RandomMap::lineDistance(POINT a, POINT b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

//일단 타일 30개 빠르게 찍어보고 입구 만든 다음에 그걸 통해서 통로를 만들어 보자 그 전에 상점 설치부터

void RandomMap::Load(int saveNum)
{
	string fileName = "Save/saveMapData";  // 1.map";
	fileName += to_string(saveNum) + ".map";

	DWORD readBytes;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0,
		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	/*void**/
	if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
		&readBytes, NULL))
	{

	}
	else
	{
		MessageBox(g_hWnd, "저장파일 로드 실패", "실패", MB_OK);
	}

















	//bhs알고리즘

	CloseHandle(hFile);
}
