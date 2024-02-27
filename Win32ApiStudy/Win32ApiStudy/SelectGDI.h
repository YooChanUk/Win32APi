#pragma once
class SelectGDI
{
private:
	HDC m_hDC;
	HPEN m_hDefaultPen;
	HBRUSH m_hDefaultBrush;

public:
	SelectGDI(HDC _dc, PEN_TYPE _eType);
	SelectGDI(HDC _dc, BRUSH_TYPE _eType);
	~SelectGDI();
};

