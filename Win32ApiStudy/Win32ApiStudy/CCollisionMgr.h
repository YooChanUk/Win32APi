#pragma once

class CCollider;

union COLLIDER_ID
{
	struct
	{
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	//충돌체간 이전 프레임 충돌정보
	map<ULONGLONG, bool> m_mapColInfo;
	UINT m_arrCheck[(UINT)GROUP_TYPE::END]; //그룹간의 충돌체크 매트릭스
	


public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset()
	{
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);	
	}


private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _Right);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

