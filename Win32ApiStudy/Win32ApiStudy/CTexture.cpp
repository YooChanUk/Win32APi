#include "pch.h"
#include "CTexture.h"

#include "CCore.h"


CTexture::CTexture()
	:m_hBit(0)
	,m_dc(0)
	, m_bitInfo{}
{

}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);

}

void CTexture::Load(const wstring& _strFilePath)
{
	//파일로 부터 로딩한 데이터를 비트맵으로 생성
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);


	//이 비트맵과 연결 지어줄 DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainHDC());

	//비트맵과 DC연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	//가로 세로 길이(비트맵 정보)
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);



}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC maindc = CCore::GetInst()->GetMainHDC();
	
	m_hBit = CreateCompatibleBitmap(maindc, _iWidth, _iHeight);
	m_dc = CreateCompatibleDC(maindc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBit);

	//가로 세로 길이(비트맵 정보)
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
