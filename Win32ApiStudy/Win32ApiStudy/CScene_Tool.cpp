#include "pch.h"
#include "CScene_Tool.h"

#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "resource.h"
#include "CSceneMgr.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CUIMgr.h"
#include "CPathMgr.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
	:m_pUI(nullptr)
{

}

CScene_Tool::~CScene_Tool()
{

}

void CScene_Tool::Enter()
{
	//신에서 사용할 메뉴를 붙인다.
	CCore::GetInst()->DockMenu();


	CreateTile(5,5);

	//UI
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->setName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->setName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	((CBtnUI*)pBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
	pPanelUI->AddChild(pBtnUI);
	AddObject(pPanelUI, GROUP_TYPE::UI);

	//CUI* pClonePanel = pPanelUI->clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-500.f, 0.f));
	//((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene,0,0);

	//AddObject(pClonePanel, GROUP_TYPE::UI);

	//m_pUI = pClonePanel;

	//Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2);
}

void CScene_Tool::Exit()
{
	CCore::GetInst()->DivideMenu();

	DeleteAll();
}



void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

	//if (KEY_TAP(KEY::LSHIFT))
	//{
	//	//CUIMgr::GetInst()->SetFocusedUI(m_pUI);
	//	SaveTileData();
	//}

	if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}
}


void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0.f || iTileX <= iCol
			|| vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;
		}

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}
}

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0"; //목록처럼 필터가 뜸 ALL을 고를시 오른쪽 .
	//Tile을 고를시 오른쪽 .tile
	ofn.nFilterIndex = 0; //처음 필터 지정
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();//초기경로

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//경로와 파일이 무조건 존재해야함
	
	if (GetSaveFileName(&ofn))//우리가 위의 지정한 설정을 이용해 창을 여는 함수(모달방식)
	{
		SaveTile(szName);
		//CPathMgr::GetInst()->GetRelativePath(szName);
	}
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	//커널오브젝트 FILE, 파일 열기 성공하면 pFile에 주소값이 채워짐
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strFilePath.c_str(),L"wb");//2바이트 오픈
	assert(pFile);

	//데이터 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	const vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0"; //목록처럼 필터가 뜸 ALL을 고를시 오른쪽 .
	//Tile을 고를시 오른쪽 .tile
	ofn.nFilterIndex = 0; //처음 필터 지정
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();//초기경로

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//경로와 파일이 무조건 존재해야함

	if (GetOpenFileName(&ofn))//우리가 위의 지정한 설정을 이용해 창을 여는 함수(모달방식)
	{
		//szName은 절대경로를 붙여서 경로를 전달하기에 다른곳에서도 사용하는 LoadTile은
		//상대경로를 사용하게끔 놔두는게 좋다. 그렇기에 szName에서 절대경로 부분은 자르고
		//상대경로만 넘기는게 좋다.
		//
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);

		LoadTile(strRelativePath);
	}
}

void ChangeScene(DWORD_PTR,DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}

//
// Tile Count Window Proc
//

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) 
		{
			UINT iXCount = GetDlgItemInt(hDlg,IDC_EDIT1,nullptr,false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if(LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

