#pragma once

class CMonster;
class CState;

class AI
{
private:
	map<MON_STATE, CState*> m_mapState;
	CMonster*				m_pOwner;
	CState*					m_pCurState;
	
public:
	void update();

public:
	void AddState(CState* _pState);
	CState* GetState(MON_STATE _eState);
	void SetCurState(MON_STATE _eState);

	void ChangeState(MON_STATE _eNextState);

	CMonster* GetOwner() { return m_pOwner; }

public:
	AI();
	~AI();

	friend class CMonster;
};
