#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

//CCore* CCore::g_pInst = nullptr;




CCore::CCore()
	:m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
}

CObject g_obj;


int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = {0,0,m_ptResolution.x,m_ptResolution.y};

	//해상도에 맞게 윈도우 크기 조정
	AdjustWindowRect(&rt,WS_OVERLAPPEDWINDOW,true);//윈도우 크기를 내가 지정해놓은 사이즈만큼 잡아주는 함수
	//rt.right - rt.left;
	//rt.bottom - rt.top;
	SetWindowPos(m_hWnd,nullptr,100,100, rt.right - rt.left, rt.bottom - rt.top,0);

	m_hDC = GetDC(m_hWnd);
	//Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	//CKeyMgr::GetInst->init();

	g_obj.SetPos(Vec2(((float)m_ptResolution.x / 2),((float)m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2(100,100));


	return S_OK;
}



void CCore::progress()
{
	//manager update
	CTimeMgr::GetInst()->update();

	update();

	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 200.f * fDT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 100.f * CTimeMgr::GetInst()->GetfDT();
	}

	g_obj.SetPos(vPos);
	
}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_hDC, 
		int(vPos.x - vScale.x / 2.f), 
		int(vPos.y - vScale.y / 2.f), 
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));
}
