#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUIMgr.h"
#include "AI.h"
#include "CState.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	//���� �����ӿ��� ����ص� Dead Object���� �����Ѵ�.
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	//Eventó��
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		//lParam : Object Adress
		//wParam : Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj,eType);
		

	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		//lParmam : Object Adress(������ ������Ʈ �ּ�)
		//���� ������ ������Ʈ�ε� �׷�Ÿ�Ա��� �˾ƾ� �� �ʿ�� ����
		//������Ʈ dead���� ����
		//���� ���� ������Ʈ���� ��Ƶд�.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);

	}

		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		//lParam : Next Scene Type
		//Scene����
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		//��Ŀ��UI����(���� Scene�� UI�� ����Ű�� �ֱ� ����)
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
	}
		break;
	case EVENT_TYPE::CHANGE_AI_STATE:
	{
		//lParam : AI
		//wParam : Next State
		AI* pAI = (AI*)_eve.lParam;
		MON_STATE eNextState = (MON_STATE)_eve.wParam;

		pAI->ChangeState(eNextState);
	}
	break;
	}
}