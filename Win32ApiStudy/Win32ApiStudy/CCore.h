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

class CTexture;

class CCore
{
public:
	SINGLE(CCore);
private:
	HWND m_hWnd;			//���� ������ �ڵ�
	POINT m_ptResolution;	//���� ������ �ػ�
	HDC m_hDC;				//���������쿡 Draw �� DC

	CTexture* m_pMemTex; //����� �ؽ�ó

	//���� ����ϴ� GDI Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

	//�޴�
	HMENU m_hMenu; //Tool_Scene������ ���

public:
	int init(HWND _hWnd,POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC GetMainHDC() { return m_hDC; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
	//HMENU GetMenu() { return m_hMenu; }
};