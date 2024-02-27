#include "pch.h"
#include "CCore.h"


#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"

#include "resource.h"

//CCore* CCore::g_pInst = nullptr;

CCore::CCore()
	:m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	,m_arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);//딜릿트는 메뉴항목제거 디스트로이가 메뉴전체제거
}

//CObject g_obj;

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	//해상도에 맞게 윈도우 크기 조정
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	//메뉴바 생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WIN32APISTUDY));

	m_hDC = GetDC(m_hWnd);


	//이중 버퍼링 용도의 비트맵과 DC를 만든다.
	//m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	//m_memDC = CreateCompatibleDC(m_hDC);

	//HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	//DeleteObject(hOldBit);
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer",(UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
	//이중버퍼링 용도는 위의 한줄로 대체됨

	//자주 사용할 펜 및 브러쉬 생성
	CreateBrushPen();

	//Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();

	//g_obj.SetPos(Vec2(((float)m_ptResolution.x / 2),((float)m_ptResolution.y / 2)));
	//g_obj.SetScale(Vec2(100,100));


	return S_OK;
}



void CCore::progress()
{
	//manager update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	//
	//Scene Update
	//
	CSceneMgr::GetInst()->update();

	//충돌체크
	CCollisionMgr::GetInst()->update();


	//UI이벤트체크
	CUIMgr::GetInst()->update();

	//=======
	//Rendering
	//=======
	//화면clear
	Clear();


	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMemTex->GetDC(), 0, 0, SRCCOPY); //비트를 옮길 수 있게 해주는 함수

	CTimeMgr::GetInst()->render();

	//이벤트 지연처리
	CEventMgr::GetInst()->update();
}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//이미 저장된 스톡 오브젝트를 가져오는것이기에 지울 필요없음

	//red pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	//해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0,0,(long)_vResolution.x,(long)_vResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);//윈도우 크기를 내가 지정해놓은 사이즈만큼 잡아주는 함수
	//rt.right - rt.left;
	//rt.bottom - rt.top;
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}

//void CCore::update()
//{
//	Vec2 vPos = g_obj.GetPos();
//
//	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
//	{
//		vPos.x -= 200.f * fDT;
//	}
//
//	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
//	{
//		vPos.x += 200.f * CTimeMgr::GetInst()->GetfDT();
//	}
//
//	g_obj.SetPos(vPos);
//	
//}

//void CCore::render()
//{
//	//화면 clear
//
//
//	Vec2 vPos = g_obj.GetPos();
//	Vec2 vScale = g_obj.GetScale();
//
//	Rectangle(m_memDC, 
//		int(vPos.x - vScale.x / 2.f), 
//		int(vPos.y - vScale.y / 2.f), 
//		int(vPos.x + vScale.x / 2.f),
//		int(vPos.y + vScale.y / 2.f));
//
//}
