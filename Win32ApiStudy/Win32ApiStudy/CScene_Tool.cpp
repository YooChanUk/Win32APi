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
	//�ſ��� ����� �޴��� ���δ�.
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

	//Camera Look ����
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
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0"; //���ó�� ���Ͱ� �� ALL�� ���� ������ .
	//Tile�� ���� ������ .tile
	ofn.nFilterIndex = 0; //ó�� ���� ����
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();//�ʱ���

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//��ο� ������ ������ �����ؾ���
	
	if (GetSaveFileName(&ofn))//�츮�� ���� ������ ������ �̿��� â�� ���� �Լ�(��޹��)
	{
		SaveTile(szName);
		//CPathMgr::GetInst()->GetRelativePath(szName);
	}
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	//Ŀ�ο�����Ʈ FILE, ���� ���� �����ϸ� pFile�� �ּҰ��� ä����
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strFilePath.c_str(),L"wb");//2����Ʈ ����
	assert(pFile);

	//������ ����
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
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0"; //���ó�� ���Ͱ� �� ALL�� ���� ������ .
	//Tile�� ���� ������ .tile
	ofn.nFilterIndex = 0; //ó�� ���� ����
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();//�ʱ���

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;//��ο� ������ ������ �����ؾ���

	if (GetOpenFileName(&ofn))//�츮�� ���� ������ ������ �̿��� â�� ���� �Լ�(��޹��)
	{
		//szName�� �����θ� �ٿ��� ��θ� �����ϱ⿡ �ٸ��������� ����ϴ� LoadTile��
		//����θ� ����ϰԲ� ���δ°� ����. �׷��⿡ szName���� ������ �κ��� �ڸ���
		//����θ� �ѱ�°� ����.
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

