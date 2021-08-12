#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT Enemy::Init(int posX, int posY)
{
    ImageManager::GetSingleton()->AddImage("Enemy1", "Image/BattleCity/Enemy/Enemy.bmp", 512 * 0.8, 384 * 0.8, 8, 6, true, RGB(255, 0, 255));
    image = ImageManager::GetSingleton()->FindImage("Enemy1");    
    if (image == nullptr)
    {
        MessageBox(g_hWnd, 
            "Enemy에 해당하는 이미지가 추가되지 않았음!", "경고", MB_OK);
        return E_FAIL;
    }

    currFrameX = 0;
    updateCount = 0;

    pos.x =  (float)posX;
    pos.y = (float)posY;
    startPos.x = (float)posX;
    startPos.y = (float)posY;
    size = 40;
    name = "NormalEnemy";
    enemyShape = { (int)startPos.x - 25, (int)startPos.y - 25, (int)startPos.x + 25, (int)startPos.y + 25 };
    isAlive = true;
    angle = 0.0f;
    target = nullptr;
    dir = 1;

    // 미사일 매니저
    missileMgr = new MissileManager();
    missileMgr->Init(this);

    fireCount = 0;

    return S_OK;
}

void Enemy::Release()
{
    SAFE_RELEASE(missileMgr);
}

void Enemy::Update()
{
    if (isAlive)
    {
        //HorizonMove();
        //Move();
        enemyShape = { (int)pos.x - 25, (int)pos.y - 25, (int)pos.x + 25, (int)pos.y + 25 };
        // 미사일 발사
        if (missileMgr)
        {
            // 함수 호출 주기를 바꿔보자.
            fireCount++;
            if (fireCount % 20 == 0)
            {
                fireCount = 0;
                missileMgr->Fire(pos, -90);
            }
            missileMgr->Update();
        }

        //HorizonMove();
        // 애니메이션 프레임
      /*  updateCount++;
        if (updateCount == 5)
        {
            currFrameX++;
            if (currFrameX >= 10)
            {
                currFrameX = 0;
            }

            updateCount = 0;
        }*/
    }
    if (!isAlive)
    {
       /* currTimer += TimerManager::GetSingleton()->GetElapsedTime();
        if (currTimer >= 3.0f)
            isAlive = true;*/
        pos = { -100, -100 };
        enemyShape = { 0, 0, 0, 0 };
    }
    currTimer2++;
    
    if (currTimer2 % 100 == 0)
    {
        if (currFrameX < 3)
        currFrameX++;
        if(currFrameX>=2)
        currFrameX = 0;
    }
    //pos.x -= moveSpeed;
}

void Enemy::Render(HDC hdc)
{
    if (isAlive)
    {
        Rectangle(hdc, enemyShape.left, enemyShape.top, enemyShape.right, enemyShape.bottom /*shape.left, shape.top, shape.right, shape.bottom*/);
  
        if (image)
        {            
            image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
        }

        if (missileMgr)
        {
            missileMgr->Render(hdc);
        }
        currTimer = 0;
    }
    if (!isAlive)
    {
        if (image)
        {
            image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
        }
    }
}

void Enemy::Move()
{
    if (target)
    {
        FPOINT targetPos = target->GetPos();

        // 현재 위치에서 타겟 위치로 이동할 수 있는 각도 구하기
        float x = targetPos.x - pos.x;
        float y = targetPos.y - pos.y;

        angle = atan2(y, x);

        pos.x += cosf(angle) * moveSpeed;
        pos.y += sinf(angle) * moveSpeed;
    }
}

void Enemy::HorizonMove()
{
    if (startPos.x > WINSIZE_X || startPos.x < 0)
    {
        dir *= -1;
    }
    startPos.x += moveSpeed * dir;
}

