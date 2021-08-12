#include "TilemapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"

TILE_INFO TilemapTool::tileInfo[TILE_X * TILE_Y];
int TilemapTool::argNum;

HRESULT TilemapTool::Init()
{

	tileSize = TILESIZE;
	imgSize = 1; 
	zoomSize = 1;
	argNum = 0;
	SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);

	sampleTile = ImageManager::GetSingleton()->AddImage(
		"샘플타일", "Image/WOL/map/IceBaseTileSetCustom5.bmp", 960,560,
		SAMPLE_TILE_X, SAMPLE_TILE_Y);

	hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hSelectedPen = CreatePen(PS_SOLID, 1, RGB(100, 100, 100));
	
	// 메인 공간 렉트 설정
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			tileInfo[i * TILE_X + j].frameX = 23;
			tileInfo[i * TILE_X + j].frameY = 13;
			tileInfo[i * TILE_X + j].tileVar = BLANK;
			tileInfo[i * TILE_X + j].isAlive = true;

			tileInfo[i * TILE_X + j].rcTile.left = TILESIZE * j;
			tileInfo[i * TILE_X + j].rcTile.top = TILESIZE * i;
			tileInfo[i * TILE_X + j].rcTile.right =
				tileInfo[i * TILE_X + j].rcTile.left + TILESIZE;
			tileInfo[i * TILE_X + j].rcTile.bottom =
				tileInfo[i * TILE_X + j].rcTile.top + TILESIZE;

			/*tileInfo[i * TILE_X + j].rcTile = GetRectToCenter(j * (TILESIZE), i * (TILESIZE), TILESIZE, TILESIZE);
			gridRc[i * TILE_X + j] = GetRectToCenter(j * (TILESIZE ), i * (TILESIZE), TILESIZE, TILESIZE);*/
		}
	}
	
	// 샘플 공간 렉트 설정
	for (int i = 0; i < SAMPLE_TILE_Y; i++)
	{
		for (int j = 0; j < SAMPLE_TILE_X; j++)
		{
			SetRect(&sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile,
				TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j),
				(TILESIZE * i),
				TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j) + TILESIZE,
				(TILESIZE * i) + TILESIZE);
			

			sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
			sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;

			//sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left =
			//    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j);
			//sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top = (TILESIZE * i);
			//sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.right =
			//    sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left + TILESIZE;
			//sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.bottom =
			//    sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top + TILESIZE;
		}
	}

#pragma region 접혀
	sampleTileInfo[285].tileVar = BLANK;
	sampleTileInfo[286].tileVar = BLANK;
	sampleTileInfo[287].tileVar = BLANK;
	sampleTileInfo[309].tileVar = BLANK;
	sampleTileInfo[310].tileVar = BLANK;
	sampleTileInfo[311].tileVar = BLANK;
	sampleTileInfo[333].tileVar = BLANK;
	sampleTileInfo[334].tileVar = BLANK;
	sampleTileInfo[335].tileVar = BLANK;

	for (int i = 0; i <= 11; i++) sampleTileInfo[i].tileVar = WALL;
	for (int i = 12; i <= 23; i++) sampleTileInfo[i].tileVar = WAY;
	for (int i = 24; i <= 35; i++) sampleTileInfo[i].tileVar = WALL;
	for (int i = 36; i <= 47; i++) sampleTileInfo[i].tileVar = WAY;
	for (int i = 48; i <= 59; i++) sampleTileInfo[i].tileVar = WALL;
	for (int i = 60; i <= 71; i++) sampleTileInfo[i].tileVar = WAY;
	for (int i = 72; i <= 83; i++) sampleTileInfo[i].tileVar = WALL;
	for (int i = 84; i <= 95; i++) sampleTileInfo[i].tileVar = WAY;	
	for (int i = 96; i <= 312; i+=24) sampleTileInfo[i].tileVar = WALL;
	for (int i = 97; i <= 241; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 265; i <= 313; i += 24) sampleTileInfo[i].tileVar = WALL;
	for (int i = 98; i <= 242; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 266; i <= 314; i += 24) sampleTileInfo[i].tileVar = WALL;
	for (int i = 99; i <= 243; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 267; i <= 315; i += 24) sampleTileInfo[i].tileVar = WALL;
	for (int i = 100; i <= 244; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 268; i <= 346; i += 24) sampleTileInfo[i].tileVar = WALL;
	for (int i = 101; i <= 245; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 269; i <= 317; i += 24) sampleTileInfo[i].tileVar = WALL;
	for (int i = 102; i <= 246; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 270; i <= 318; i += 24) sampleTileInfo[i].tileVar = WALL;
	for (int i = 103; i <= 247; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 271; i <= 319; i += 24) sampleTileInfo[i].tileVar = WALL;
	for (int i = 104; i <= 248; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 105; i <= 249; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 106; i <= 250; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 11; i <= 275; i += 24) sampleTileInfo[i].tileVar = WALL;
	for (int i = 296; i <= 299; i++) sampleTileInfo[i].tileVar = BLANK;
	for (int i = 320; i <= 323; i++) sampleTileInfo[i].tileVar = BLANK;
	for (int i = 108; i <= 111; i++) sampleTileInfo[i].tileVar = HOLE;
	for (int i = 132; i <= 135; i++) sampleTileInfo[i].tileVar = HOLE;
	for (int i = 156; i <= 157; i++) sampleTileInfo[i].tileVar = HOLE;
	for (int i = 180; i <= 183; i++) sampleTileInfo[i].tileVar = WAY;
	for (int i = 204; i <= 207; i++) sampleTileInfo[i].tileVar = WAY;
	for (int i = 228; i <= 231; i++) sampleTileInfo[i].tileVar = WAY;
	for (int i = 252; i <= 255; i++) sampleTileInfo[i].tileVar = WAY;
	for (int i = 276; i <= 279; i++) sampleTileInfo[i].tileVar = HOLE;
	for (int i = 300; i <= 303; i++) sampleTileInfo[i].tileVar = HOLE;
	for (int i = 324; i <= 327; i++) sampleTileInfo[i].tileVar = HOLE;
	for (int i = 112; i <= 304; i+=24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 113; i <= 305; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 114; i <= 306; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 115; i <= 307; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 116; i <= 284; i += 24) sampleTileInfo[i].tileVar = WAY;
	for (int i = 328; i <= 329; i ++) sampleTileInfo[i].tileVar = END;
	for (int i = 330; i <= 331; i++) sampleTileInfo[i].tileVar = START;
#pragma endregion 접혀
	 //UI Button
	ImageManager::GetSingleton()->AddImage("저장버튼", "Image/세이브.bmp",
		446 * 0.5, 110 * 0.5, 2, 1);
	ImageManager::GetSingleton()->AddImage("불러오기버튼", "Image/로드.bmp",
		446 * 0.5, 110 * 0.5, 2, 1);
	ImageManager::GetSingleton()->AddImage("다음버튼", "Image/다음.bmp",
		206 * 0.5, 110 * 0.5, 2, 1);
	ImageManager::GetSingleton()->AddImage("이전버튼", "Image/이전.bmp",
		206 * 0.5, 110 * 0.5, 2, 1);
	ImageManager::GetSingleton()->AddImage("다다음버튼", "Image/다다음.bmp",
		206 * 0.5, 110 * 0.5, 2, 1);
	ImageManager::GetSingleton()->AddImage("이전전버튼", "Image/이전전.bmp",
		206 * 0.5, 110 * 0.5, 2, 1);
	btnSave = new Button();
	btnSave->Init("저장버튼", TILEMAPTOOLSIZE_X - sampleTile->GetWidth()- 250 - 520,
		TILEMAPTOOLSIZE_Y - 70);
	btnSave->SetFunc(Save);

	btnLoad = new Button();
	btnLoad->Init("불러오기버튼", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() - 120 - 520,
		TILEMAPTOOLSIZE_Y - 70);
	btnLoad->SetFunc(Load);

	btnNext = new Button();
	btnNext->Init("다음버튼", TILEMAPTOOLSIZE_X - sampleTile->GetWidth()+60- 470,
		TILEMAPTOOLSIZE_Y - 70);
	btnNext->SetFunc(Next);

	btnBack = new Button();
	btnBack->Init("이전버튼", TILEMAPTOOLSIZE_X - sampleTile->GetWidth()- 470,
		TILEMAPTOOLSIZE_Y - 70);
	btnBack->SetFunc(Back);

	btnTenNext = new Button();
	btnTenNext->Init("다다음버튼", TILEMAPTOOLSIZE_X - sampleTile->GetWidth()+120- 470,
		TILEMAPTOOLSIZE_Y - 70);
	btnTenNext->SetFunc(TenNext);

	btnTenBack = new Button();
	btnTenBack->Init("이전전버튼", TILEMAPTOOLSIZE_X - sampleTile->GetWidth()-60- 470,
		TILEMAPTOOLSIZE_Y - 70);
	btnTenBack->SetFunc(TenBack);

	return S_OK;
}

void TilemapTool::Release()
{
	SAFE_RELEASE(btnSave);
	SAFE_RELEASE(btnLoad);
	SAFE_RELEASE(btnNext);
	SAFE_RELEASE(btnBack);
	SAFE_RELEASE(btnTenNext);
	SAFE_RELEASE(btnTenBack);
}

void TilemapTool::Update()
{
	
	// 세이브 F1 F2 F3 ...
	//int stageNum = VK_F1;
	//int currInputKey;

	if (btnSave)    btnSave->Update();
	if (btnLoad)    btnLoad->Update();
	if (btnNext)    btnNext->Update();
	if (btnBack)    btnBack->Update();
	if (btnTenNext)    btnTenNext->Update();
	if (btnTenBack)    btnTenBack->Update();
	/*  if (KeyManager::GetSingleton()->IsStayKeyDown(VK_CONTROL))
	  {
		  if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
		  {
			  Load(1);
		  }
		  else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
		  {
			  Load(2);
		  }
		  else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
		  {
			  Load(3);
		  }
	  }
	  else
	  {
		  if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
		  {
			  Save(1);
		  }
		  else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
		  {
			  Save(2);
		  }
		  else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
		  {
			  Save(3);
		  }
	  }*/

	  // 메인 영역 계산
	rcMain.left = 0;
	rcMain.top = 0;
	rcMain.right = (rcMain.left + (TILESIZE * TILE_X));
	rcMain.bottom = (rcMain.top + (TILESIZE * TILE_Y));

	

	// 샘플 영역 계산
	rcSample.left = TILEMAPTOOLSIZE_X - sampleTile->GetWidth();
	rcSample.top = 0;
	rcSample.right = TILEMAPTOOLSIZE_X;
	rcSample.bottom = sampleTile->GetHeight();
	if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
	{
		for (int i = 0; i < TILE_Y; i++)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				tileInfo[i * TILE_X + j].frameX = 10;
				tileInfo[i * TILE_X + j].frameY = 13;
			}
		}
	}
	if (PtInRect(&rcMain, g_ptMouse))
	{
		// 마우스 왼쪽 버튼 클릭시 좌표 사용
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)
			|| KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < TILE_X * TILE_Y; i++)
			{
				if (PtInRect(&(tileInfo[i].rcTile), g_ptMouse))
				{
					//selectedFrameX = i % TILE_X;
					//selectedFrameY = i / TILE_X;

					tileInfo[i].frameX = ptStartSelectedFrame.x;
					tileInfo[i].frameY = ptStartSelectedFrame.y;

					for (int j = 0; j <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; j++)
					{
						for (int k = 0; k <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; k++)
						{
							if ((i % TILE_X) + k >= TILE_X) continue;
							if ((i / TILE_X) + j >= TILE_Y) continue;

							tileInfo[i + j * TILE_X + k].frameX = ptStartSelectedFrame.x + k;
							tileInfo[i + j * TILE_X + k].frameY = ptStartSelectedFrame.y + j;
							tileInfo[i + j * TILE_X + k].tileVar = ptTileOption;
						}
					}
					break;
				}
			}
		}
	}
	else if (PtInRect(&rcSample, g_ptMouse))
	{
		// 마우스 왼쪽 버튼 클릭시 좌표 사용
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			// 2) 마우스 좌표로 인덱스 계산
			int posX = g_ptMouse.x - rcSample.left;
			int posY = g_ptMouse.y - rcSample.top;
			ptStartSelectedFrame.x = posX / TILESIZE;
			ptStartSelectedFrame.y = posY / TILESIZE;
			int temp = ptStartSelectedFrame.x + (ptStartSelectedFrame.y * SAMPLE_TILE_X);
			ptTileOption = sampleTileInfo[ptStartSelectedFrame.x + (ptStartSelectedFrame.y * SAMPLE_TILE_X)].tileVar;
			ptSelected[0] = g_ptMouse;

			//// 1) 모든 타일을 반복하면서 렉트충돌 확인
			//for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
			//{
			//    if (PtInRect(&(sampleTileInfo[i].rcTile), g_ptMouse))
			//    {
			//        ptStartSelectedFrame.x = i % SAMPLE_TILE_X;
			//        ptStartSelectedFrame.y = i / SAMPLE_TILE_X;

			//        break;
			//    }
			//}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - rcSample.left;
			int posY = g_ptMouse.y - rcSample.top;
			ptEndSelectedFrame.x = posX / TILESIZE;
			ptEndSelectedFrame.y = posY / TILESIZE;
			
			// 선택영역 초기화
			ptSelected[0].x = -1;
			ptSelected[0].y = -1;
			ptSelected[1].x = -1;
			ptSelected[1].y = -1;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
		{
			ptSelected[1] = g_ptMouse;
		}
		
	}

}

void TilemapTool::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0,
		TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

	// 샘플타일 전체
	sampleTile->Render(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth(), 0);

	// 선택 영역 표시
	hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);
	Rectangle(hdc, ptSelected[0].x, ptSelected[0].y, ptSelected[1].x, ptSelected[1].y);
	SelectObject(hdc, hOldSelectedBrush);

	// UI Button
	if (btnSave)    btnSave->Render(hdc);
	if (btnLoad)    btnLoad->Render(hdc);
	if (btnNext)    btnNext->Render(hdc);
	if (btnBack)    btnBack->Render(hdc);
	if (btnTenNext)    btnTenNext->Render(hdc);
	if (btnTenBack)    btnTenBack->Render(hdc);
	// 메인영역 전체
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{		
		sampleTile->FrameRender(hdc,
			tileInfo[i].rcTile.left,
			tileInfo[i].rcTile.top,
			tileInfo[i].frameX,
			tileInfo[i].frameY,
			0, zoomSize);
		
	}
	
	if (KeyManager::GetSingleton()->IsStayKeyDown('Q'))
	{
		for (int i = 0; i < TILE_X * TILE_Y; i++)
		{
			hOldSelectedPen = (HPEN)SelectObject(hdc, hSelectedPen);
			hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);
			Rectangle(hdc, tileInfo[i].rcTile.left, tileInfo[i].rcTile.left, tileInfo[i].rcTile.right, tileInfo[i].rcTile.bottom);
			SelectObject(hdc, hOldSelectedBrush);
			SelectObject(hdc, hOldSelectedPen);	
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		int k = 0; 
		for (int i = 0; i < TILE_X; i++)
		{
			wsprintf(szText, "%d", i+1);
			TextOut(hdc, tileInfo[i].rcTile.left + TILESIZE / 2-10,
				(tileInfo[i].rcTile.top + TILESIZE / 2)*40-30, szText, strlen(szText));
		}
		for (int i = 0; i < TILE_X * TILE_Y; i++)
		{
			if (i%20==0)
			{
				k++;
				wsprintf(szText, "%d", k);
				TextOut(hdc, tileInfo[i].rcTile.left + TILESIZE / 2 * 40 - 30,
					(tileInfo[i].rcTile.top + TILESIZE / 2) - 10, szText, strlen(szText));
			}

		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('E'))
	{

		for (int i = 0; i < TILE_X * TILE_Y; i++)
		{
			
			if (tileInfo[i].tileVar == BLANK)
			{
				wsprintf(szText2, "B");
				TextOut(hdc, tileInfo[i].rcTile.left + TILESIZE / 2,
					(tileInfo[i].rcTile.top + TILESIZE / 2), szText2, strlen(szText2));
			}
			if (tileInfo[i].tileVar == HOLE)
			{
				wsprintf(szText2, "H");
				TextOut(hdc, tileInfo[i].rcTile.left + TILESIZE / 2,
					(tileInfo[i].rcTile.top + TILESIZE / 2), szText2, strlen(szText2));
			}
			if (tileInfo[i].tileVar == WAY)
			{
				wsprintf(szText2, "R");
				TextOut(hdc, tileInfo[i].rcTile.left + TILESIZE / 2,
					(tileInfo[i].rcTile.top + TILESIZE / 2), szText2, strlen(szText2));
			}
			if (tileInfo[i].tileVar == WALL)
			{
				wsprintf(szText2, "W");
				TextOut(hdc, tileInfo[i].rcTile.left + TILESIZE / 2,
					(tileInfo[i].rcTile.top + TILESIZE / 2), szText2, strlen(szText2));
			}
			if (tileInfo[i].tileVar == END)
			{
				wsprintf(szText2, "E");
				TextOut(hdc, tileInfo[i].rcTile.left + TILESIZE / 2,
					(tileInfo[i].rcTile.top + TILESIZE / 2), szText2, strlen(szText2));
			}
		}
	}
	
	// 선택된 타일
	if (ptStartSelectedFrame.x == ptEndSelectedFrame.x &&
		ptStartSelectedFrame.y == ptEndSelectedFrame.y)
	{
		sampleTile->FrameRender(hdc,
			TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
			sampleTile->GetHeight() + 15,
			ptStartSelectedFrame.x, ptStartSelectedFrame.y, false, 3);
	}
	else
	{
		for (int i = 0; i <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; i++)
		{
			for (int j = 0; j <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; j++)
			{
				sampleTile->FrameRender(hdc,
					TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (j * TILESIZE),
					sampleTile->GetHeight() + 15 + (i * TILESIZE),
					ptStartSelectedFrame.x + j, ptStartSelectedFrame.y + i, false, 1);

			}
		}
	}
	wsprintf(szText, "지금 스테이지 %d", argNum);
	TextOut(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + 50,
		TILEMAPTOOLSIZE_Y - 140, szText, strlen(szText));
	
	
	//for (int i = 0; i < TILE_X * TILE_Y; i++)
	//{
	//	hSelectedPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	//	hOldSelectedPen = (HPEN)SelectObject(hdc, hSelectedPen);
	//	Rectangle(hdc, gridRect[i].left, gridRect[i].top, gridRect[i].right, gridRect[i].top);
	//	hSelectedPen = (HPEN)SelectObject(hdc, hOldSelectedPen);
	//	DeleteObject(hSelectedPen);
	//}
}

/*
	실습1. F1, F2, F3  각 키를 눌렀을 때
	Save/saveMapData1.map, Save/saveMapData2.map, Save/saveMapData3.map
	각 각 파일에 저장될 수 있도록 코드 구현

	실습2. 로드는 Ctrl + F1, ...
*/

void TilemapTool::Save()
{
	/*for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			tileInfo[i * TILE_X + j].index = argNum;
			tileInfo[i * TILE_X + j].rcTile = GetRectToCenter(j * (TILESIZE*2), i * (TILESIZE*2), TILESIZE*2, TILESIZE*2);
		}
	}*/
	string fileName = "Save/saveMapData";  // 1.map";
	fileName += to_string(argNum) + ".map";

	DWORD writtenBytes;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0,
		0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	/*void**/
	WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
		&writtenBytes, NULL);

	CloseHandle(hFile);

}

void TilemapTool::Load()
{
	string fileName = "Save/saveMapData";  // 1.map";
	fileName += to_string(argNum) + ".map";

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

void TilemapTool::Next()
{
	argNum++;
	if (argNum >= 30)
	{
		argNum = 0;
	}
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			tileInfo[i * TILE_X + j].frameX = 10;
			tileInfo[i * TILE_X + j].frameY = 13;
		}
	}
	//Load();
}

void TilemapTool::Back()
{
	argNum--;
	if (argNum < 0)
	{
		argNum = 30;
	}
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			tileInfo[i * TILE_X + j].frameX = 10;
			tileInfo[i * TILE_X + j].frameY = 13;
		}
	}
}

void TilemapTool::TenNext()
{
	argNum+=10;
	if (argNum >= 30)
	{
		argNum = 0;
	}
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			tileInfo[i * TILE_X + j].frameX = 10;
			tileInfo[i * TILE_X + j].frameY = 13;
		}
	}
}

void TilemapTool::TenBack()
{
	argNum-=10;
	if (argNum < 0)
	{
		argNum = 30;
	}
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			tileInfo[i * TILE_X + j].frameX = 10;
			tileInfo[i * TILE_X + j].frameY = 13;
		}
	}
}



