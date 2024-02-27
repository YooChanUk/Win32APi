#pragma once

#include "global.h"
#include "CCamera.h"


class CCollider;
class CAnimator;



class CObject //오브젝트를 관리하는 오브젝트들의 부모
{
private:
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;
	CAnimator* m_pAnimator;

	bool m_bAlive;//자기자신이 활성화인지 활성화 중지 될 예정인지에 대한 bool값

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	 
	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void setName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }

	bool IsDead() { return !m_bAlive; }
	

	void CreateCollider();
	void CreateAnimator();

private:
	void SetDead() { m_bAlive = false; }
	//IsDead() 묻는건 아무나 할 수 있지만 죽는것을 설정하는건 아무나 설정하면 안된다.\
	//자식 조차도 알면안되기에 private 설정 자식을 알게하고 싶으면 protected

public:
	virtual void update() = 0;
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	virtual CObject* clone() = 0;

	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class CEventMgr;//EventMgr은 SetDead()함수를 사용할 수 있어야 하기에 friend class를 하면 prviate인게 모두 공개된다
};

