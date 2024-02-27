#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	//텍스처로딩
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\1Hm_success.bmp");
	
	CreateCollider();

	GetCollider()->SetOffsetPos(Vec2(0.f,12.f));
	GetCollider()->SetScale(Vec2(20.f, 40.f));

	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\11linkAni.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);

	GetAnimator()->Play(L"WALK_DOWN",true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");

	for (UINT i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
	
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_CHECK(KEY::W,KEY_STATE::HOLD))
	{
		vPos.y -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::A) == KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::D) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * fDT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);

	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	//int iWidth = (int)m_pTex->Width();
	//int iHeight = (int)m_pTex->Height();

	//Vec2 vPos = GetPos();
	
	//BitBlt(_dc,
	//	(int)(vPos.x - (float)(iWidth / 2)),
	//	(int)(vPos.y - (float)(iHeight / 2)),
	//	iWidth,iHeight,
	//	m_pTex->GetDc(),
	//	0,0,SRCCOPY);

	//TransparentBlt(_dc,
	//	(int)(vPos.x - (float)(iWidth / 2)),
	//	(int)(vPos.y - (float)(iHeight / 2)),
	//	iWidth, iHeight,
	//	m_pTex->GetDc(),
	//	0, 0, iWidth, iHeight,
	//	RGB(255, 0, 255));

	//컴포넌트(충돌체,etc)가 있는 경우 렌더
	component_render(_dc);

	//아래는 알파블렌드 관련내용
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Plane", L"texture\\1Hm_success.bmp");

	//Vec2 vPos = GetPos();
	//vPos = CCamera::GetInst()->GetRenderPos(vPos);

	//float width = (float)pTex->Width();
	//float height = (float)pTex->Height();

	//BLENDFUNCTION bf = {};
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 127; //고정 알파값

	//AlphaBlend(_dc,
	//	int(vPos.x - width / 2.f),
	//	int(vPos.y - height /2.f),
	//	int(width),int(height),
	//	pTex->GetDC(),
	//	0,0, int(width), int(height),
	//	bf);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->setName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile,GROUP_TYPE::PROJ_PLAYER);

	//pMissile->SetDir(true);
	//CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	//pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);

}


