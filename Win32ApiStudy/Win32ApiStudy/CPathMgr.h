#pragma once
#include "pch.h"

class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t m_szContentPath[256];
	wchar_t m_szRelativePath[256];

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; } //포인터로 주기때문에 가져간뒤에 수정 못하게 const로준다

	wstring GetRelativePath(const wchar_t* _filePath);

};

