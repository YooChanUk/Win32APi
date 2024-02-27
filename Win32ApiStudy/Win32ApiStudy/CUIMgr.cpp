#include "pch.h"
#include "CUIMgr.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	:m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	//1. FocusedUI 확인
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
	{
		return;
	}


	//2. FocusedUI 내에서, 부모UI포함 자식UI들중 실제 타겟팅 된 UI를 가져온다.
	CUI* pTargetUI = GetTargetUI(m_pFocusedUI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}

			//왼쪽버튼 떼면, 눌렸던 체크를 다시 해제
			pTargetUI->m_bLbtnDown = false;
		}
	}

}

//특정 키 눌렸을때 그 UI를 즉시 포커스 하게 해주는 함수
void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	//이미 포커싱 중인 경우 or 포커싱 해제요청인 경우
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	//벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	//기존 포커싱UI를 받아두고 변경되었는지 확인한다.
	CUI* pFocusedUI = m_pFocusedUI;


	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	//왼쪽 버튼 Tap이 발생했다는 전제하
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for(; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	//이번에 focus된 UI가 없다.
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	//벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	//1.부모 UI포함 모든 자식들을 검사해야한다.
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;
	//매번 호출될때마다 이만큼의 동적할당이 일어날텐데, 그것을 방지하기위해 static선언(한번만 선언하면
	//그 뒤에 호출해도 다시 할당되지 않기때문에)
	
	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		//큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();

		//큐에서 꺼내온 UI가 TargetUI인지 확인
		//2. 타겟 UI들중 더 우선순위가 높은 기준은 더 낮은 계층의 자식UIs
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}
		

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			//왼쪽버튼 떼면, 눌렸던 체크를 다시 해제
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}


	return pTargetUI;
}
