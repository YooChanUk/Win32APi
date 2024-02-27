#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CTexture.h"
#include "CPathMgr.h"

#include "CCore.h"

#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"



CScene_Start::CScene_Start()
{

}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::update()
{
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
		
	}
}

void CScene_Start::Enter()
{
	//Object �߰�
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CCamera::GetInst()->SetTarget(pObj);

	//Ŭ�а��á�
	//CObject* pOtehrPlayer = pObj->clone();
	//pOtehrPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtehrPlayer, GROUP_TYPE::PLAYER);

	////Monster �߰�
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	//int iMonCount = 1;
	///*float fMoveDist = 0.f;*/
	//float fObjScale = 50.f;
	//
	//
	//Vec2 vResolution = CCore::GetInst()->GetResolution();
	//
	//CMonster* pMonsterObj = nullptr;

	///*float fTerm = (vResolution.x - ((fMoveDist + (fObjScale / 2.f)) * 2)) / (float)(iMonCount -1);*/

	//AI* pAI = new AI;
	//pAI->AddState(new CIdleState);
	//pAI->AddState(new CTraceState);

	//for (int i = 0; i < iMonCount; ++i)
	//{
	//	//���� ������Ʈ �߰�
	//	CMonster* pMonsterObj = new CMonster;
	//	pMonsterObj->setName(L"Monster");
	//	pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
	//	pMonsterObj->SetPos(vResolution / 2.f - Vec2(0.f, 300.f));

	//	pMonsterObj->SetAI(pAI);

	//	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);

	//	//pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
	//	//pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + (float)i * fTerm, 50.f));
	//	//pMonsterObj->SetMoveDistance(fMoveDist);
	//}

	//Ÿ�Ϸε�
	//LoadTile(L"Tile\\Start.tile");
	
	//�浹 ����
	//player�׷�� monster�׷찣�� �浹üũ
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	//Camera Look ����
	CCamera::GetInst()->SetLookAt(vResolution / 2);

	//Camera ȿ�� ����
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}
