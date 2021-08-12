#include "MissileManager.h"
#include "Missile.h"

HRESULT MissileManager::Init(Enemy* owner)
{
    this->owner = owner;

    vMissiles.resize(1);
    vector<Missile*>::iterator it;
    for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    {
        (*it) = new Missile();
        (*it)->Init(this->owner);

        // �̻��� �Ŵ����� ��� �ִ� �� ��ü�� ������ ����
    }

    return S_OK;
}

HRESULT MissileManager::Init(Tank* t_Owner)
{
    this->t_Owner = t_Owner;

    vMissiles.resize(1);
    vector<Missile*>::iterator it;
    for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    {
        (*it) = new Missile();
        (*it)->Init(this->t_Owner);

        // �̻��� �Ŵ����� ��� �ִ� �� ��ü�� ������ ����
    }

    return S_OK;
}

void MissileManager::Release()
{
    vector<Missile*>::iterator it;
    for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    {
        (*it)->Release();
        delete (*it);
        (*it) = nullptr;
    }
    vMissiles.clear();
}

void MissileManager::Update()
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->Update();
    }

    //vector<Missile*>::iterator it;
    //for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    //{
    //    (*it)->Update();
    //}
}

void MissileManager::Render(HDC hdc)
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->Render(hdc);
    }
    //vector<Missile*>::iterator it;
    //for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    //{
    //    (*it)->Render(hdc);
    //}
}

void MissileManager::Fire(FPOINT pos, float angle)
{
    vector<Missile*>::iterator it;
    for (it = vMissiles.begin(); it != vMissiles.end(); it++)
    {
        if ((*it)->GetIsFired() == false)
        {
            (*it)->SetIsFired(true, pos);
            (*it)->SetAngle(DegToRad (angle));
            break;
        }
    }
}
