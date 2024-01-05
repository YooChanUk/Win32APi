#pragma once
#include "Resource.h"
#include "pch.h"

//�̱���
//��ü�� ������ 1���� ����
//���� ��𼭵� ���� ������ �����ؾ��Ѵ�.

//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	static CCore* GetInstance()
//	{
//		// �� �Լ��� ���� ȣ����� ���
//		//static�� �ʱ�ȭ�� �ѹ��� �Ͼ��.
//
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore;
//		}
//
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (nullptr != g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//		
//	}
//
//
//private:
//	CCore();
//	~CCore();
//
//};


class CCore
{
public:
	SINGLE(CCore);
private:
	HWND m_hWnd;			//���� ������ �ڵ�
	POINT m_ptResolution;	//���� ������ �ػ�
	HDC m_hDC;				//���������쿡 Draw �� DC

public:
	int init(HWND _hWnd,POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hWnd; }
};