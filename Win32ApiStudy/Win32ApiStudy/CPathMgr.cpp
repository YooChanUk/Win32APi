#include "pch.h"
#include "CCore.h"
#include "CPathMgr.h"


CPathMgr::CPathMgr()
	:m_szContentPath{}
{

}

CPathMgr::~CPathMgr()
{


}

void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);//�����ΰ� �̰��� ä������

	int iLen = (int)wcslen(m_szContentPath); //���ڰ� �󸶳� �ִ���Ȯ�� �迭üũ

	//����������
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\"); //���� �ڿ� �ٿ��ֱ�

	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filePath)
{
	wstring strFilePath = _filePath;

	//int iPos = strFilePath.find_last_of(m_szContentPath);//Ư�����ڿ��� ã�Ƴ��� �ְ�����
	//strFilePath.substr();//Ư���������� ���ڸ� �߶󳾼��ְ�����

	size_t iAbsLen = wcslen(m_szContentPath); //�����α���
	size_t iFullLen = strFilePath.length();//��ü����


	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);


	return strRelativePath;
}
