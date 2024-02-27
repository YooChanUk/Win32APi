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
	GetCurrentDirectory(255, m_szContentPath);//현재경로가 이곳에 채워진다

	int iLen = (int)wcslen(m_szContentPath); //문자가 얼마나 있는지확인 배열체크

	//상위폴더로
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\"); //문자 뒤에 붙여주기

	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}

wstring CPathMgr::GetRelativePath(const wchar_t* _filePath)
{
	wstring strFilePath = _filePath;

	//int iPos = strFilePath.find_last_of(m_szContentPath);//특정문자열을 찾아낼수 있게해줌
	//strFilePath.substr();//특정지점에서 문자를 잘라낼수있게해줌

	size_t iAbsLen = wcslen(m_szContentPath); //절대경로길이
	size_t iFullLen = strFilePath.length();//전체길이


	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);


	return strRelativePath;
}
