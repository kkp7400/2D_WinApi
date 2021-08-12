#include "BattleScene.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Missile.h"
#include "Image.h"
#include "Player.h"
#include "CommonFunction.h"
#include "CheckCollision.h"
#include "Camera.h"
#include "UI.h"
#include "RandomMap.h"
#include "Monster.h"

TILE_INFO BattleScene::tileInfo[TILE_X * TILE_Y];

HRESULT BattleScene::Init()
{

	bin = new Image();
	bin->Init("Image/WOL/UIs/Loading.bmp", 1280*1.05, 720*1.05);

	player = new Player();
	player->Init();
	
	enemyMgr = new EnemyManager();
	enemyMgr->Init();
	
	cameraRect = Camera::GetSingleton()->GetRect();

	//checkAll = new CheckCollision();
	//checkAll->Init();
	zoomValue = 1;


	//stage = ImageManager::GetSingleton()->AddImage(
	//	"샘플타일", "Image/IceBaseTileSetCustom1.bmp", 88 * 3, 16 * 3,
	//	/*TILE_X*/11, /*TILE_Y*/2);
	stage = ImageManager::GetSingleton()->AddImage(
		"샘플타일", "Image/WOL/map/IceBaseTileSetCustom5.bmp", 960, 560,
		24, 14);
	spawn = ImageManager::GetSingleton()->AddImage(
		"플레이어스폰", "Image/WOL/player/SPAWN_PLAYER.bmp", 1800*0.5, 730*0.5,
		8, 1,true,RGB(255,0,255));
	spawn = ImageManager::GetSingleton()->FindImage("플레이어스폰");
	ui = new UI();
	ui->SetPlayer(player);	
	ui->Init();
	Load();
	randMap = new RandomMap();
	randMap->Init();

	isRandMapStop = false;
//	checkAll = new CheckCollision();

	//SAFE_RELEASE(randMap);
	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(player);
	SAFE_RELEASE(bin);
	SAFE_RELEASE(enemyMgr);
	SAFE_RELEASE(ui);
}

void BattleScene::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('K'))
	{
		Camera::GetSingleton()->Shake(0.1,1);
	}

	if (!isRandMapStop)
	{
		randMap->Update();
	}
	//randMap->Update();
	cameraRect = Camera::GetSingleton()->GetRect();
	if (!isRandMapStop&&randMap->GetIsRandMap())
	{
		//map.resize(randMap->GetMap()->size());
		//map = *randMap->GetMap();
		map2.resize(randMap->GetMap2()->size());
		map2 = *randMap->GetMap2();
		isRandMapStop = true;
		battleZon.resize(10);	
		battleZon = *randMap->GetMapRect();		
		SAFE_RELEASE(randMap);

		mon = new Monster();
		mon->SetPlayer(player);
		mon->Init(battleZon);
		CheckCollision::GetSingleton()->SetMonster(mon);
		CheckCollision::GetSingleton()->SetPlayer(player);
	}
	if (isRandMapStop)
	{
		//if (isSpawn)
		//{
			CheckCollision();
			if (enemyMgr)
			{
				enemyMgr->Update();
			}

			if (player)
			{
				player->Update();
			}

			//for (int i = 0; i < TILE_X * TILE_Y; i++)
			//{
			//	if (!(tileInfo[i].isAlive))
			//	{
			//		tileInfo[i].tileVar = BLANK;
			//		tileInfo[i].rcTile.left = TILESIZE * 10;
			//		tileInfo[i].rcTile.top = TILESIZE * 0;
			//		tileInfo[i].frameX = 10;
			//		tileInfo[i].frameY = 0;
			//	}
			//}
			if (isRandMapStop)
			{
				mon->Update();
			}
		//}
		ui->Update();
	}
}

void BattleScene::Render(HDC hdc)
{
	
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	
	//wsprintf(szText, "rcTile[0].left: %d", tileInfo[0].rcTile.left);
	//TextOut(hdc, 1000, 60, szText, strlen(szText));


	//vector<POINT>mapClientPos;
	int mapClientPosX;
	int mapClientPosY;
	POINT playerClientPos;
	POINT culling;
	culling.y = player->GetPos().y / 40;
	culling.x = player->GetPos().x / 40;
	playerClientPos.x = player->GetPos().x - Camera::GetSingleton()->GetPos().x;
	playerClientPos.y = player->GetPos().y - Camera::GetSingleton()->GetPos().y;
	if (isRandMapStop)
	{
		//if (culling.y - 15 >= 0 && culling.y + 15 <= 124 && culling.x - 30 >= 0 && culling.x + 30 <= 124)
		for (int i = culling.y - 15; i <= culling.y + 15; i++)
		{
			for (int j = culling.x - 30; j <= culling.x + 30; j++)
			{
				if (i < 0 || i > 124 || j < 0 || j > 124) continue;
				mapClientPosX = map2[i][j].rcTile.left - Camera::GetSingleton()->GetPos().x;
				mapClientPosY = map2[i][j].rcTile.top - Camera::GetSingleton()->GetPos().y;

				if (map2[i][j].tileVar != BLANK)
				{
					stage->FrameRender(hdc,
						mapClientPosX,
						mapClientPosY,
						map2[i][j].frameX,
						map2[i][j].frameY
					);
				}
				if (KeyManager::GetSingleton()->IsStayKeyDown('F'))
				{
					if (map2[i][j].tileVar == WALL || map2[i][j].tileVar == WALLTWO)
						Rectangle(hdc, mapClientPosX, mapClientPosY, mapClientPosX + 40, mapClientPosY + 40);
					if (map2[i][j].tileVar == WALL)
					{
						wsprintf(szText, "벽");
						TextOut(hdc, mapClientPosX+20, mapClientPosY+20, szText, strlen(szText));
					}
					if (map2[i][j].tileVar == WALLTWO)
					{
						wsprintf(szText, "벽");
						TextOut(hdc, mapClientPosX + 20, mapClientPosY + 20, szText, strlen(szText));
					}
					if (map2[i][j].tileVar == WAY)
					{
						wsprintf(szText, "길");
						TextOut(hdc, mapClientPosX + 20, mapClientPosY + 20, szText, strlen(szText));
					}
				}
			}
		}

		//for (int i = 0; i < battleZon.size(); i++)
		//{
		//	Rectangle(hdc, battleZon[i].rect.left - Camera::GetSingleton()->GetPos().x, battleZon[i].rect.top - Camera::GetSingleton()->GetPos().y,
		//		battleZon[i].rect.right - Camera::GetSingleton()->GetPos().x, battleZon[i].rect.bottom - Camera::GetSingleton()->GetPos().y);
		//}
		if (player)
		{
			player->Render(hdc);
		}
		if (!isSpawn)
		{
			elapsedTime += TimerManager::GetSingleton()->GetElapsedTime();
			if (elapsedTime >= 0.1)
			{
				currX++;
				if (currX >= 8) isSpawn = true;
				elapsedTime = 0;
			}

			spawn->FrameRender(hdc,
				WINSIZE_X/2,
				WINSIZE_Y / 2-100,
				currX,
				0,
				true);
		}
		if (isSpawn)
		{
			mon->Render(hdc);
			if (player)
			{
				player->Render(hdc);
			}
			ui->Render(hdc);
		}
	}
	//for (int i = 0; i < map.size(); i++)
	//{
	//	mapClientPos[i].x = map[i].rcTile.left - Camera::GetSingleton()->GetPos().x;
	//	mapClientPos[i].y = map[i].rcTile.top - Camera::GetSingleton()->GetPos().y;
	//	
	//	if (mapClientPos[i].x < playerClientPos.x + WINSIZE_X / 2+100 &&
	//		mapClientPos[i].x > playerClientPos.x - WINSIZE_X / 2-100 &&
	//		mapClientPos[i].y < playerClientPos.y + WINSIZE_Y / 2+100 &&
	//		mapClientPos[i].y > playerClientPos.y - WINSIZE_Y / 2-100)
	//	{
	//		if (map[i].tileVar != BLANK)
	//			stage->FrameRender(hdc,
	//				mapClientPos[i].x,
	//				mapClientPos[i].y,
	//				map[i].frameX,
	//				map[i].frameY
	//			);
	//	
	//	}		
	//		// wsprintf(szText, "%d", map[i].tileVar);
	//		// TextOut(hdc, mapClientPos[i].x, mapClientPos[i].y, szText, strlen(szText));
	//}

	
	

	/*if (!isRandMapStop)
		bin->Render(hdc);*/
}

void BattleScene::CheckCollision()
{
	player->SetPos( CheckCollision::GetSingleton()->PlayerVsTile(player->GetMoveCol(), player->GetPos(), map2));
	CheckCollision::GetSingleton()->Update();
}
void BattleScene::Load()
{
	string fileName = "Save/saveMapData";  // 1.map";
	fileName += to_string(0) + ".map";

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

	CloseHandle(hFile);
}
//일단 랜덤맵 꺽이는 부분에 뭔가 추가하고
//대쉬 막고
// 0번맵 위쪽 옵션 맞춰주고
// 뚤린 길 있으면 막아주자