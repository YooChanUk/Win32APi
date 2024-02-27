#pragma once
#include "CObject.h"

struct tMonInfo
{
    float fSpeed;
    float iHP;
    float fRecogRange;
    float fAttRange;
    float fAtt;
};

class AI;

class CMonster :
    public CObject
{
private:
    //Vec2 m_vCenterPos; //최초의 중앙점
    //float m_fSpeed;
    //float m_fMaxDistance; //최대 이동 거리
    //int m_iDir; //진행 방향 정보 1 오 -1 왼
    //int m_iHP;

    tMonInfo m_tInfo;
    AI* m_pAI;


public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
    void SetAI(AI* _AI);
    const tMonInfo& GetInfo() { return m_tInfo; }

    //void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    //void SetMoveDistance(float _f) { m_fMaxDistance = _f; }

    CMonster* clone() { return new CMonster(*this); }

private:
    void SetMonInfo(const tMonInfo& _info)
    {
        m_tInfo = _info;
    }

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual void update();

public:
    CMonster();
    ~CMonster();

    friend class CMonFactory;
};

