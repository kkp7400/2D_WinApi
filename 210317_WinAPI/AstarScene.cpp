#include "AstarScene.h"
#include "CommonFunction.h"
#include "Camera.h"
HRESULT AstarTile::Init()
{
	return E_NOTIMPL;
}

HRESULT AstarTile::Init(int idX, int idY)
{
	isInOpenlist = false;
	isClosed = false;

	this->idX = idX;
	this->idY = idY;

	frameX = 23;
	frameY = 13;

	center.x = idX * ASTAR_TILE_SIZE + (ASTAR_TILE_SIZE / 2);
	center.y = idY * ASTAR_TILE_SIZE + (ASTAR_TILE_SIZE / 2);

	rc.left = idX * ASTAR_TILE_SIZE;
	rc.right = rc.left + ASTAR_TILE_SIZE;
	rc.top = idY * ASTAR_TILE_SIZE;
	rc.bottom = rc.top + ASTAR_TILE_SIZE;

	costFromStart = 0.0f;
	costToGoal = 0.0f;
	totalCost = 0.0f;

	type = TILEOPTION::BLANK;

	parentTile = nullptr;

	color = RGB(100, 100, 100);
	//hBrush = CreateSolidBrush(color);

	return S_OK;
}

HRESULT AstarTile::ClearAstarTile(int idX, int idY)
{
	isInOpenlist = false;
	isClosed = false;

	costFromStart = 0.0f;
	costToGoal = 0.0f;
	totalCost = 0.0f;

	parentTile = nullptr;

	color = RGB(100, 100, 100);
	//hBrush = CreateSolidBrush(color);

	return S_OK;
}

void AstarTile::Release()
{
	//DeleteObject(hBrush);
}

void AstarTile::Update()
{
}

void AstarTile::Render(HDC hdc)
{
	//hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	//FillRect(hdc, &rc, hBrush); 
	POINT screenPos;
	screenPos.x = (rc.left + 20) - Camera::GetSingleton()->GetPos().x;
	screenPos.y = (rc.top + 20) - Camera::GetSingleton()->GetPos().y;
	RenderRectToCenter(hdc, screenPos.x, screenPos.y, 40, 40);

	//SelectObject(hdc, hOldBrush);

	if (type != TILEOPTION::WALL)
	{
		// F, G, H 출력
		//wsprintf(szText, "F : %d", totalCost);
		//TextOut(hdc, rc.left + 5, rc.top + 5, szText, strlen(szText));

//wsprintf(szText, "G : %d", costFromStart);
//TextOut(hdc, rc.left + 5, rc.top + 25, szText, strlen(szText));

//wsprintf(szText, "H : %d", costToGoal);
//TextOut(hdc, rc.right - 55, rc.top + 45, szText, strlen(szText));
	}
}

void AstarTile::SetColor(COLORREF color)
{
	//if(this)
	//this->color = color;
	//DeleteObject(hBrush);

	//hBrush = CreateSolidBrush(color);
}

HRESULT AstarScene::Init()
{
	stackOverCheck = 0;
	isAstarOk = false;
	//SetClientRect(g_hWnd, ASTARSIZE_X, ASTARSIZE_Y);

	// 브러시 종류
	//for (int i = 0; i < TILEOPTION::MAX_COUNT; i++)
	//{
	hBrush[TILEOPTION::START] = CreateSolidBrush(RGB(255, 0, 0));
	hBrush[TILEOPTION::END] = CreateSolidBrush(RGB(0, 0, 255));
	hBrush[TILEOPTION::HOLE] = CreateSolidBrush(RGB(150, 150, 150));
	hBrush[TILEOPTION::BLANK] = CreateSolidBrush(RGB(100, 100, 100));
	hBrush[TILEOPTION::WAY] = CreateSolidBrush(RGB(0, 255, 0));
	hBrush[TILEOPTION::WALL] = CreateSolidBrush(RGB(50, 50, 50));
	hBrush[TILEOPTION::MAX_COUNT] = CreateSolidBrush(RGB(130, 200, 130));
	//}

	for (int i = 0; i < ASTAR_TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)	// 가로반복 (x)
		{
			map[i][j].Init(j, i);
		}
	}

	//startTile = &(map[start.x][start.y]);
	//startTile = &(map[2][2]);
	//startTile->SetColor(RGB(255, 0, 0));
	//startTile->SetType(TILEOPTION::START);// 와 스타트 타일 어떻게 하냐

//	currTile = startTile;

	//destTile = &(map[End.x][End.y]);
	//destTile = &(map[ASTAR_TILE_COUNT - 2 ][ASTAR_TILE_COUNT - 2]);
	//destTile->SetColor(RGB(0, 0, 255));
	//destTile->SetType(TILEOPTION::END);

	return S_OK;
}

void AstarScene::Release()
{
}

void AstarScene::Update()
{
	// 화면 전환 테스트
	//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
	//{
	//	SceneManager::GetSingleton()->ChangeScene("전투_1");
	//	return;
	//}
	//else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
	//{
	//	SceneManager::GetSingleton()->ChangeScene("타일맵툴", "로딩씬_1");
	//	return;
	//}

	//if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	//{
	//	// g_ptMouse로 인덱스를 계산
	//	int x, y;
	//	x = g_ptMouse.x / ASTAR_TILE_SIZE;
	//	y = g_ptMouse.y / ASTAR_TILE_SIZE;

	//	if (0 <= x && x < ASTAR_TILE_COUNT &&
	//		0 <= y && y < ASTAR_TILE_COUNT)
	//	{
	//		// 시작이나 목적지가 아닐 때
	//		if (map[y][x].GetType() != AstarTileType::Start &&
	//			map[y][x].GetType() != AstarTileType::End)
	//		{
	//			map[y][x].SetColor(RGB(50, 50, 50));
	//			map[y][x].SetType(AstarTileType::Wall);
	//		}
	//	}
	//}


	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		FindPath();
	}

	if ((currTile == destTile))
	{
		MarkTileToType();
	}
}

void AstarScene::Render(HDC hdc)
{
	TILEOPTION tileOption;
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)	// 가로반복 (x)
		{
			tileOption = map[i][j].GetType();
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush[tileOption]);

			map[i][j].Render(hdc);

			SelectObject(hdc, hOldBrush);
			//wsprintf(szText, "%d %d", i, j);
			//TextOut(hdc, map[i][j].GetCenter().x - Camera::GetSingleton()->GetPos().x , map[i][j].GetCenter().y - Camera::GetSingleton()->GetPos().y, szText, strlen(szText));
		}
	}
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)	// 가로반복 (x)
		{
			if (map[i][j].GetType() == TILEOPTION::START)
			{
				wsprintf(szText, "S");
				TextOut(hdc, map[i][j].GetCenter().x - Camera::GetSingleton()->GetPos().x, map[i][j].GetCenter().y - Camera::GetSingleton()->GetPos().y, szText, strlen(szText));
			}
		}
	}
}



void AstarScene::SetStartTile(POINT start)
{
	for (int i = 1; i <= 6; i++)
	{
		if (start.y + i >= ASTAR_TILE_COUNT)	continue;
		if (start.y - i < 0)	continue;
		if (start.x + i >= ASTAR_TILE_COUNT)	continue;
		if (start.x - i < 0)	continue;

		map[start.y + i][start.x].SetType(TILEOPTION::BLANK);
		map[start.y - i][start.x].SetType(TILEOPTION::BLANK);
		map[start.y][start.x + i].SetType(TILEOPTION::BLANK);
		map[start.y][start.x - i].SetType(TILEOPTION::BLANK);
	}
	startTile = &(map[start.y][start.x]);
	//startTile->SetColor(RGB(255, 0, 0));
	startTile->SetType(TILEOPTION::START);// 와 스타트 타일 어떻게 하냐	
	if (!startTile && !currTile) return;

	currTile = startTile;

}

void AstarScene::SetEndTile(POINT End)
{
	for (int i = 1; i <= 6; i++)
	{
		if (End.y + i >= ASTAR_TILE_COUNT)	continue;
		if (End.y - i < 0)	continue;
		if (End.x + i >= ASTAR_TILE_COUNT)	continue;
		if (End.x - i < 0)	continue;

		map[End.y + i][End.x].SetType(TILEOPTION::BLANK);
		map[End.y - i][End.x].SetType(TILEOPTION::BLANK);
		map[End.y][End.x + i].SetType(TILEOPTION::BLANK);
		map[End.y][End.x - i].SetType(TILEOPTION::BLANK);
	}

	destTile = &(map[End.y][End.x]);
	//destTile->SetColor(RGB(0, 0, 255));
	if (!destTile) return;
	if (destTile==nullptr) return;
	if (!destTile->GetIdX()) return;
	destTile->SetType(TILEOPTION::END);

}

void AstarScene::SetType(RECT rc, TILEOPTION tileOption)
{
	POINT a;
	a.x = rc.left + 20;
	a.y = rc.top + 20;
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)	// 가로반복 (x)
		{
			if (map[i][j].GetCenter().x == a.x && map[i][j].GetCenter().y == a.y)
			{
				if (tileOption != TILEOPTION::WAY) continue;
				map[i][j].SetType(tileOption);
			}
		}
	}
}

void AstarScene::SetType2(RECT rc, TILEOPTION tileOption, int frameX, int frameY)
{
	POINT a;
	a.x = rc.left + 20;
	a.y = rc.top + 20;
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)	// 가로반복 (x)
		{
			if (map[i][j].GetCenter().x-20 == rc.left && map[i][j].GetCenter().y+20 == rc.bottom && map[i][j].GetCenter().x + 20 == rc.right && map[i][j].GetCenter().y - 20 == rc.top)
			{
				map[i][j].SetType(tileOption);
				map[i][j].SetFrameX(frameX);
				map[i][j].SetFrameY(frameY);
			}
		}
	}
}



void AstarScene::SetWall(RECT rect)
{
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)	// 가로반복 (x)
		{
			if (map[i][j].GetCenter().x > rect.left
				&& map[i][j].GetCenter().x < rect.right
				&& map[i][j].GetCenter().y > rect.top
				&& map[i][j].GetCenter().y < rect.bottom)
				map[i][j].SetType(TILEOPTION::WALL);
		}
	}
	int wallValue = 6;
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)	// 가로반복 (x)
		{
			// 좌
			if (map[i][j].GetCenter().x > rect.left
				&& map[i][j].GetCenter().x < rect.left + 40
				&& map[i][j].GetCenter().y > rect.top
				&& map[i][j].GetCenter().y < rect.bottom)
			{
				for (int k = 1; k <= wallValue; k++)
				{
					if (j - k <= 0) continue;
					map[i][j - k].SetType(TILEOPTION::WALL);
				}
			}
			// 우
			else if (map[i][j].GetCenter().x < rect.right
				&& map[i][j].GetCenter().x > rect.right - 40
				&& map[i][j].GetCenter().y > rect.top
				&& map[i][j].GetCenter().y < rect.bottom)
			{
				for (int k = 1; k <= wallValue; k++)
				{
					if (j + k >= ASTAR_TILE_COUNT) continue;
					map[i][j + k].SetType(TILEOPTION::WALL);
				}
			}
			// 상
			if (map[i][j].GetCenter().x > rect.left - 40 * wallValue
				&& map[i][j].GetCenter().x < rect.right + 40 * wallValue
				&& map[i][j].GetCenter().y <= rect.top
				&& map[i][j].GetCenter().y > rect.top - 40)
			{
				for (int k = 0; k < wallValue; k++)
				{
					if (i - k <= 0) continue;
					map[i - k][j].SetType(TILEOPTION::WALL);
				}
			}
			// 하
			else if (map[i][j].GetCenter().x > rect.left - 40 * wallValue
				&& map[i][j].GetCenter().x < rect.right + 40 * wallValue
				&& map[i][j].GetCenter().y > rect.bottom
				&& map[i][j].GetCenter().y <= rect.bottom + 40)
			{
				for (int k = 0; k < wallValue; k++)
				{
					if (i + k >= ASTAR_TILE_COUNT) continue;
					map[i + k][j].SetType(TILEOPTION::WALL);
				}
			}
		}
	}

	// 타일 색 지정
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)	// 세로반복 (y)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)	// 가로반복 (x)
		{
			// 시작이나 목적지가 아닐 때
			if (/*map[i][j].GetType() != TILEOPTION::START &&
				map[i][j].GetType() != TILEOPTION::END &&*/
				map[i][j].GetType() == TILEOPTION::WALL)
			{
				map[i][j].SetColor(RGB(50, 50, 50));
			}
		}
	}

}

vector<POINT> AstarScene::GetWayPos()
{
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)
		{
			if (map[i][j].GetType() == TILEOPTION::WAY || map[i][j].GetType() == TILEOPTION::WALLTWO)
				if (map[i][j].GetType() != TILEOPTION::WALL && map[i][j].GetType() != TILEOPTION::BLANK)
					wayPos.push_back(map[i][j].GetCenter());
		}
	}
	return wayPos;
}

vector<POINT> AstarScene::GetFrame()
{
	POINT a;
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)
		{
			if (map[i][j].GetType() == TILEOPTION::WAY || map[i][j].GetType() == TILEOPTION::WALLTWO)
			{
				a.x = map[i][j].GetFrameX();
				a.y = map[i][j].GetFrameY();
				if (map[i][j].GetType() != TILEOPTION::WALL && map[i][j].GetType() != TILEOPTION::BLANK)
					frame.push_back(a);
			}
		}
	}
	return frame;
}

vector<TILEOPTION> AstarScene::GetType()
{
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)
		{
			if (map[i][j].GetType() == TILEOPTION::WAY || map[i][j].GetType() == TILEOPTION::WALLTWO)
				if (map[i][j].GetType() != TILEOPTION::WALL && map[i][j].GetType() != TILEOPTION::BLANK)
					type.push_back(map[i][j].GetType());
		}
	}
	return type;
}

void AstarScene::FindPath()
{
	stackOverCheck++;
	if (stackOverCheck >= 3980)
	{

		isAstarOk = true;
		return;
	}
	if (currTile)
	{
		// 주위에 있는 이동가능한 타일들을 F값 계산 후보에 넣는다.
		AddOpenList(currTile);
		currTile->SetIsClosed(true);
		//DeleteTileInOpenlist(currTile);

		// 후보들 중 F값이 가장 작은 타일을 다음 currTile 선정
		//currTile = GetMinTotalCostTile();
		currTile = GetMinTotalCostTileWithHeap();

		if (currTile == nullptr)	return;

		currTile->SetColor(RGB(130, 200, 130));
		//currTile->SetType(TILEOPTION::WAY);
		// 도착여부 판단
		if (currTile == destTile)
		{
			//MarkTileToType();
			return;
		}

		// 반복
		FindPath();
	}
}

void AstarScene::AddOpenList(AstarTile* currTile)
{
	int currIdX = currTile->GetIdX();
	int currIdY = currTile->GetIdY();

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i != 0 && j != 0) continue;
			if (i == 0 && j == 0)	continue;

			if (currIdY + i < 0 || currIdY + i >= ASTAR_TILE_COUNT ||
				currIdX + j < 0 || currIdX + j >= ASTAR_TILE_COUNT)
				continue;

			// TODO : 오픈리스트에 추가하면 안되는 조건
			// 1. 타입이 wall 일 때
			// 2. 이미 확인된 타일일 때 ( closeList에 있을 때 )
			if (map[currIdY + i][currIdX + j].GetIsClosed())
				continue;

			if (map[currIdY + i][currIdX + j].GetType() ==
				TILEOPTION::WALL)	continue;
			//if (map[currIdY + i][currIdX + j].GetType() ==
			//	TILEOPTION::WAY)	continue;

			// 3. 이미 오픈리스트에 있을 때
			// 조건에 따라 다른 처리
			int F, G, H;
			if (map[currIdY + i][currIdX + j].GetIsInOpenlist())
			{
				G = map[currIdY + i][currIdX + j].GetG();
				if (G > currTile->GetG() + CalcEdgeCost(i, j))
				{
					G = currTile->GetG() + CalcEdgeCost(i, j);
					map[currIdY + i][currIdX + j].SetG(G);

					F = G + map[currIdY + i][currIdX + j].GetH();
					map[currIdY + i][currIdX + j].SetF(F);

					// parentNode도 함께 갱신한다.
					map[currIdY + i][currIdX + j].SetParentTile(currTile);
				}
			}
			else
			{
				// F, G, H를 갱신한다.
				// 대각선인지 상하좌우인지 판단
				G = currTile->GetG() + CalcEdgeCost(i, j);
				H = CalcHeuristics(currIdX + j, currIdY + i);
				F = G + H;
				map[currIdY + i][currIdX + j].SetG(G);
				map[currIdY + i][currIdX + j].SetH(H);
				map[currIdY + i][currIdX + j].SetF(F);

				// parentNode도 함께 갱신한다.
				map[currIdY + i][currIdX + j].SetParentTile(currTile);

				// openList에 추가
				map[currIdY + i][currIdX + j].SetIsInOpenlist(true);
				//openList.push_back(&(map[currIdY + i][currIdX + j]));

				// heap 자료구조에 추가
				InsertOpenlistWithHeap(&(map[currIdY + i][currIdX + j]));
			}

			map[currIdY + i][currIdX + j].SetType(TILEOPTION::MAX_COUNT);//그 탐색 영역?
		}
	}
}

AstarTile* AstarScene::GetMinTotalCostTile()
{
	// TODO : heap 정렬을 통한 효율성 증대
	int minF = INT_MAX;
	AstarTile* minFTile = nullptr;
	for (int i = 0; i < openList.size(); i++)
	{
		if (minF > openList[i]->GetF())
		{
			minF = openList[i]->GetF();
			minFTile = openList[i];
		}
	}

	return minFTile;
}

AstarTile* AstarScene::GetMinTotalCostTileWithHeap()
{
	if (heap.empty()) return nullptr;

	AstarTile* tile = heap[0];

	heap[0] = heap.back();
	heap[0]->SetHeapIndex(0);
	heap.pop_back();

	// 자식과 비교하면서 정렬한다
	if (heap.empty() == false)
	{
		UpdateLower(heap[0]);
	}

	return tile;
}

void AstarScene::UpdateLower(AstarTile* tile)	// 인덱스 : 3
{
	int lChildIndex = tile->GetHeapIndex() * 2 + 1;

	if (lChildIndex >= heap.size())
		return;

	AstarTile* lChild = heap[lChildIndex];	// 부모의 인덱스 * 2

	AstarTile* minChild = lChild;
	int rChildIndex = tile->GetHeapIndex() * 2 + 2;
	if (rChildIndex < heap.size())
	{
		AstarTile* rChild = heap[rChildIndex];	// 부모의 인덱스 * 2 + 1
		// 비교
		if (lChild->GetF() > rChild->GetF())
		{
			minChild = rChild;
		}
	}

	if (tile->GetF() > minChild->GetF())
	{
		Swap(tile, minChild);
		UpdateLower(tile);
	}
}

void AstarScene::Swap(AstarTile* tile1, AstarTile* tile2)
{
	heap[tile1->GetHeapIndex()] = tile2;
	heap[tile2->GetHeapIndex()] = tile1;

	int temp = tile1->GetHeapIndex();
	tile1->SetHeapIndex(tile2->GetHeapIndex());
	tile2->SetHeapIndex(temp);
}

void AstarScene::InsertOpenlistWithHeap(AstarTile* tile)
{
	tile->SetHeapIndex(heap.size());
	heap.push_back(tile);

	// 부모 타일과 비교하면서 갱신
	UpdateUpper(tile);
}

void AstarScene::UpdateUpper(AstarTile* tile)
{
	if (tile->GetHeapIndex() == 0)
		return;

	int parentIndex = (tile->GetHeapIndex() - 1) / 2;
	AstarTile* parentTile = heap[parentIndex];
	if (parentTile->GetF() > tile->GetF())
	{
		Swap(parentTile, tile);
		UpdateUpper(tile);
	}
}

void AstarScene::DeleteTileInOpenlist(AstarTile* tile)
{
	// TODO : heap 구조를 통해서 개선
	vector<AstarTile*>::iterator it;
	for (it = openList.begin(); it != openList.end();)
	{
		if ((*it) == tile)
		{
			it = openList.erase(it);
			break;
		}
		else
		{
			it++;
		}
	}
}

int AstarScene::CalcEdgeCost(int x, int y)
{
	int edgeCost = 14;
	int temp = abs(x + y);
	if (temp == 1)
	{
		edgeCost = 10;
	}
	return edgeCost;
}

int AstarScene::CalcHeuristics(int x, int y)
{
	int distX = destTile->GetIdX() - x;
	int distY = destTile->GetIdY() - y;

	return sqrt(distX * distX + distY * distY) * 10;
}

void AstarScene::MarkTileToType()
{
	/*static AstarTile**/
	if (parentTile == nullptr)
	{
		parentTile = destTile;
	}
	while (parentTile != startTile)
	{
		if (parentTile)
		{
			parentTile->SetColor(RGB(255, 0, 255));
			parentTile->SetType(TILEOPTION::WAY);
			parentTile->SetFrameX(5);
			parentTile->SetFrameY(6);
			map[parentTile->GetIdY()][parentTile->GetIdX() + 1].SetType(TILEOPTION::WAY);
			map[parentTile->GetIdY()][parentTile->GetIdX() + 1].SetFrameX(5);
			map[parentTile->GetIdY()][parentTile->GetIdX() + 1].SetFrameY(6);
			map[parentTile->GetIdY()][parentTile->GetIdX() - 1].SetType(TILEOPTION::WAY);
			map[parentTile->GetIdY()][parentTile->GetIdX() - 1].SetFrameX(5);
			map[parentTile->GetIdY()][parentTile->GetIdX() - 1].SetFrameY(6);
			map[parentTile->GetIdY() + 1][parentTile->GetIdX()].SetType(TILEOPTION::WAY);
			map[parentTile->GetIdY() + 1][parentTile->GetIdX()].SetFrameX(5);
			map[parentTile->GetIdY() + 1][parentTile->GetIdX()].SetFrameY(6);
			map[parentTile->GetIdY() - 1][parentTile->GetIdX()].SetType(TILEOPTION::WAY);
			map[parentTile->GetIdY() - 1][parentTile->GetIdX()].SetFrameX(5);
			map[parentTile->GetIdY() - 1][parentTile->GetIdX()].SetFrameY(6);
			
			
			if (map[parentTile->GetIdY()][parentTile->GetIdX() - 2].GetType() != TILEOPTION::WAY&&
				map[parentTile->GetIdY()][parentTile->GetIdX() - 2].GetType() != TILEOPTION::WALLTWO)
			{
				map[parentTile->GetIdY()][parentTile->GetIdX() - 2].SetType(TILEOPTION::WALLTWO);
				map[parentTile->GetIdY()][parentTile->GetIdX() - 2].SetFrameX(0);
				map[parentTile->GetIdY()][parentTile->GetIdX() - 2].SetFrameY(9);
			}
			if (map[parentTile->GetIdY()][parentTile->GetIdX() + 2].GetType() != TILEOPTION::WAY &&
				map[parentTile->GetIdY()][parentTile->GetIdX() + 2].GetType() != TILEOPTION::WALLTWO)
			{
				map[parentTile->GetIdY()][parentTile->GetIdX() + 2].SetType(TILEOPTION::WALLTWO);

				map[parentTile->GetIdY()][parentTile->GetIdX() + 2].SetFrameX(11);
				map[parentTile->GetIdY()][parentTile->GetIdX() + 2].SetFrameY(9);
			}
			if (map[parentTile->GetIdY() + 2][parentTile->GetIdX()].GetType() != TILEOPTION::WAY)
			{
				map[parentTile->GetIdY() + 2][parentTile->GetIdX()].SetType(TILEOPTION::WALLTWO);
				map[parentTile->GetIdY() + 2][parentTile->GetIdX()].SetFrameX(2);
				map[parentTile->GetIdY() + 2][parentTile->GetIdX()].SetFrameY(11);
			}
			if (map[parentTile->GetIdY() - 2][parentTile->GetIdX()].GetType() != TILEOPTION::WAY&&
				map[parentTile->GetIdY() - 2][parentTile->GetIdX()].GetType() != TILEOPTION::WALLTWO)
			{
				for (int k = 2; k <= 5; k++)
				{
					//if (map[parentTile->GetIdY() - k][parentTile->GetIdX()].GetType() == TILEOPTION::END &&
					//	map[parentTile->GetIdY() - k][parentTile->GetIdX()].GetType() == TILEOPTION::START) break;
					//	
					if(parentTile->GetIdY() - k>=0)
					map[parentTile->GetIdY() - k][parentTile->GetIdX()].SetType(TILEOPTION::WALLTWO);
					if (k == 2)
					{
						
						map[parentTile->GetIdY() - k][parentTile->GetIdX()].SetFrameX(2);
						map[parentTile->GetIdY() - k][parentTile->GetIdX()].SetFrameY(3);

					}
					else if (k == 3)
					{
						map[parentTile->GetIdY() - k][parentTile->GetIdX()].SetFrameX(2);
						map[parentTile->GetIdY() - k][parentTile->GetIdX()].SetFrameY(2);

					}
					else if (k == 4)
					{
						map[parentTile->GetIdY() - k][parentTile->GetIdX()].SetFrameX(2);
						map[parentTile->GetIdY() - k][parentTile->GetIdX()].SetFrameY(1);

					}
					else if (k == 5)
					{
						map[parentTile->GetIdY() - k][parentTile->GetIdX()].SetFrameX(2);
						map[parentTile->GetIdY() - k][parentTile->GetIdX()].SetFrameY(0);

					}
				}
			}			
			parentTile = parentTile->GetParentTile();
			if (map[parentTile->GetIdY() + 2][parentTile->GetIdX()+2].GetType() != TILEOPTION::WAY &&
				map[parentTile->GetIdY() + 2][parentTile->GetIdX() + 2].GetType() != TILEOPTION::WALLTWO)
			{
				map[parentTile->GetIdY() + 2][parentTile->GetIdX()+2].SetType(TILEOPTION::BLANK);
			}
			if (map[parentTile->GetIdY() - 2][parentTile->GetIdX() - 2].GetType() != TILEOPTION::WAY &&
				map[parentTile->GetIdY() - 2][parentTile->GetIdX() - 2].GetType() != TILEOPTION::WALLTWO)
			{				
				map[parentTile->GetIdY() - 2][parentTile->GetIdX() - 2].SetType(TILEOPTION::BLANK);
			}
			if (map[parentTile->GetIdY() + 2][parentTile->GetIdX() - 2].GetType() != TILEOPTION::WAY &&
				map[parentTile->GetIdY() + 2][parentTile->GetIdX() - 2].GetType() != TILEOPTION::WALLTWO)
			{
				map[parentTile->GetIdY() + 2][parentTile->GetIdX() - 2].SetType(TILEOPTION::BLANK);
			}
			if (map[parentTile->GetIdY() - 2][parentTile->GetIdX() + 2].GetType() != TILEOPTION::WAY &&
				map[parentTile->GetIdY() - 2][parentTile->GetIdX() + 2].GetType() != TILEOPTION::WALLTWO)
			{
				map[parentTile->GetIdY() - 2][parentTile->GetIdX() + 2].SetType(TILEOPTION::BLANK);
			}
		}
	}
	if (stackOverCheck >= 3990)isAstarOk = true;
	if (parentTile == startTile)
	{
		isAstarOk = true;
	}
}

