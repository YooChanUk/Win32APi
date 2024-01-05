#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	//현재카운트
	QueryPerformanceCounter(&m_llPrevCount);
	//초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);//1초당 카운트가 얼마나 나오는지
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//이전 프레임 카운팅 값과 현재 프레임 카운팅값의 차이를 구한다.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)(m_llFrequency.QuadPart);

	//= 1. / m_dDT;

	//이전 카운트값을 현재값으로 갱신
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	m_dAcc += m_dDT;

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;

		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer,L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(),szBuffer);
	}
}
