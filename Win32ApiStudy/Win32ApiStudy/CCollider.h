#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject* m_pOwner; //콜라이더를 소유하게 될 오브젝트
	Vec2 m_vOffsetPos; //오브젝트로 부터 상대적인 위치
	Vec2 m_vFinalPos; //파이널 업데이트에서 매 프레임마다 계산

	Vec2 m_vScale; //총돌체의 크기
	UINT m_iID; //충돌체 고유 ID값
	UINT m_iCol;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos;  }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID()	{ return m_iID; }
public:
	void finalupdate();
	void render(HDC _dc);
	
public:
	//충돌 시점 함수
	void OnCollision(CCollider* _pOther); //충돌중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator = (CCollider& _origin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;

};

