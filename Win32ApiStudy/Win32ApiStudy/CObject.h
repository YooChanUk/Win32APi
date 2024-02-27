#pragma once

#include "global.h"
#include "CCamera.h"


class CCollider;
class CAnimator;



class CObject //������Ʈ�� �����ϴ� ������Ʈ���� �θ�
{
private:
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;
	CAnimator* m_pAnimator;

	bool m_bAlive;//�ڱ��ڽ��� Ȱ��ȭ���� Ȱ��ȭ ���� �� ���������� ���� bool��

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
	//IsDead() ���°� �ƹ��� �� �� ������ �״°��� �����ϴ°� �ƹ��� �����ϸ� �ȵȴ�.\
	//�ڽ� ������ �˸�ȵǱ⿡ private ���� �ڽ��� �˰��ϰ� ������ protected

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

	friend class CEventMgr;//EventMgr�� SetDead()�Լ��� ����� �� �־�� �ϱ⿡ friend class�� �ϸ� prviate�ΰ� ��� �����ȴ�
};

