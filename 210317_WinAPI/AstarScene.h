#pragma once
#include "GameNode.h"

#define ASTAR_TILE_SIZE		40
#define ASTAR_TILE_COUNT	(ASTARSIZE_Y / ASTAR_TILE_SIZE)

enum class AstarTileType { Start, End, Wall, None };

class AstarTile : public GameNode
{
private:
	int idX, idY;
	POINT center;
	RECT rc;
	TILEOPTION type;

	int costFromStart;	// g : ���������� ���� �������� ���
	int costToGoal;		// h : ���� ������ ������������ ������
	int totalCost;		// f : g + h

	AstarTile* parentTile;	// g�� ���ŵ� ������ ���� ��带 ����

	int frameX;
	int frameY;
	

	bool isInOpenlist;
	bool isClosed;

	COLORREF color;
	//HBRUSH hBrush;
	//HBRUSH hOldBrush;

	// heap ����
	int heapIndex;

public:
	virtual HRESULT Init();
	HRESULT Init(int idX, int idY);
	HRESULT ClearAstarTile(int idX, int idY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	POINT GetCenter() { return center; }
	
	void SetColor(COLORREF color);
	COLORREF GetColor() { return color; }
	void SetType(TILEOPTION type) { this->type = type; }
	TILEOPTION GetType() { return this->type; }
	int GetIdX() { return this->idX; }
	int GetIdY() { return this->idY; }

	void SetFrameX(int frameX) { this->frameX = frameX; }
	void SetFrameY(int frameY) { this->frameY = frameY; }

	int GetFrameX() { return this->frameX; }
	int GetFrameY() { return this->frameY; }



	void SetParentTile(AstarTile* parent) { this->parentTile = parent; }
	AstarTile* GetParentTile() { return this->parentTile; }

	void SetG(int g) { this->costFromStart = g; }
	int GetG() { return this->costFromStart; }

	void SetH(int h) { this->costToGoal = h; }
	int GetH() { return this->costToGoal; }

	void SetF(int f) { this->totalCost = f; }
	int GetF() { return this->totalCost; }

	void SetIsInOpenlist(bool b) { this->isInOpenlist = b; }
	bool GetIsInOpenlist() { return this->isInOpenlist; }
	void SetIsClosed(bool b) { this->isClosed = b; }
	bool GetIsClosed() { return this->isClosed; }

	void SetHeapIndex(int id) { this->heapIndex = id; }
	int GetHeapIndex() { return this->heapIndex; }

	virtual ~AstarTile() {};

};

class AstarScene : public GameNode
{
	// ������ �迭 ���� ����
	AstarTile map[ASTAR_TILE_COUNT][ASTAR_TILE_COUNT];

	AstarTile* startTile;	// ������
	AstarTile* destTile;	// �Ķ���
	AstarTile* parentTile;	// �Ķ���

	AstarTile* currTile;	// (���) �ĺ�Ÿ���� ������ ���� ����Ÿ��
		
	vector<AstarTile*> openList;
	vector<AstarTile*> closeList;
	vector<AstarTile*> heap;
	char szText[128];
	POINT start;
	POINT End;
	vector<POINT>wayPos;
	vector<POINT>frame;
	vector<TILEOPTION>type;
	HBRUSH hBrush[TILEOPTION::MAX_COUNT];
	HBRUSH hOldBrush;
	vector<int>checkIdX;
	vector<int>checkIdY;
	bool isAstarOk;
	int stackOverCheck;
	vector<POINT> wallPoint;
	vector<POINT> wallFrame;

	vector<TILE_INFO>typeTile;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	

	void SetWay(RECT rect);

	vector<POINT> GetWallPOINT() { return wallPoint; }
	vector<POINT> GetWallFrame() { return wallFrame; }
	int GetStackOverCheck() { return stackOverCheck; }

	bool GetIsAstarOk() { return isAstarOk; }

	AstarTile GetAstarMap(int indexX, int indexY) { return this->map[indexX][indexY]; }

	void SetStartTile(POINT start);
	void SetEndTile(POINT End);

	void SetType(RECT rc, TILEOPTION tileOption);
	void SetType2(RECT rc, TILEOPTION tileOption, int frameX, int frameY);

	void SetWall(RECT rect);

	vector<POINT> GetWayPos();
	vector<POINT> GetFrame();
	vector<TILEOPTION> GetType();

	POINT GetWayPos2(int indexX, int indexY) { return this->map[indexX][indexY].GetCenter(); }
	POINT GetFrame2(int indexX, int indexY) { POINT a; a.x = map[indexX][indexY].GetFrameX(); a.y = map[indexX][indexY].GetFrameY(); return a; }
	TILEOPTION GetType2(int indexX, int indexY) { return this->map[indexX][indexY].GetType(); }
	
	void FindPath();
	void AddOpenList(AstarTile* currTile);
	AstarTile* GetMinTotalCostTile();
	// heap ���
	AstarTile* GetMinTotalCostTileWithHeap();
	void UpdateLower(AstarTile* tile);
	void Swap(AstarTile* tile1, AstarTile* tile2);
	void InsertOpenlistWithHeap(AstarTile* tile);
	void UpdateUpper(AstarTile* tile);

	void DeleteTileInOpenlist(AstarTile* tile);
	int CalcEdgeCost(int x, int y);
	int CalcHeuristics(int x, int y);
	void MarkTileToType();

	virtual ~AstarScene() {};
};