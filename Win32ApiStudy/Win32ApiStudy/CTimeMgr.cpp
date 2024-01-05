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
	//����ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);
	//�ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_llFrequency);//1�ʴ� ī��Ʈ�� �󸶳� ��������
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	//���� ������ ī���� ���� ���� ������ ī���ð��� ���̸� ���Ѵ�.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)(m_llFrequency.QuadPart);

	//= 1. / m_dDT;

	//���� ī��Ʈ���� ���簪���� ����
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
