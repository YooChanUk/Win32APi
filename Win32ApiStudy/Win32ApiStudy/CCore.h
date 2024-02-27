#pragma once
#include "Resource.h"
#include "pch.h"

//싱글톤
//객체의 생성을 1개로 제한
//언제 어디서든 쉽게 접근이 가능해야한다.

//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	static CCore* GetInstance()
//	{
//		// 이 함수가 최초 호출됐을 경우
//		//static의 초기화는 한번만 일어난다.
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
	HWND m_hWnd;			//메인 윈도우 핸들
	POINT m_ptResolution;	//메인 윈도우 해상도
	HDC m_hDC;				//메인윈도우에 Draw 할 DC

	CTexture* m_pMemTex; //백버퍼 텍스처

	//자주 사용하는 GDI Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

	//메뉴
	HMENU m_hMenu; //Tool_Scene에서만 사용

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