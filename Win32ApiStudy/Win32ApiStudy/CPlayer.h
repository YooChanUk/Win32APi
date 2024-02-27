#pragma once
#include "CObject.h"

class CTexture;

class CPlayer:
	public CObject
{
private:
	//CTexture* m_pTex;

public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(CPlayer);
	//CPlayer* clone() { return new CPlayer(*this); };

public:
	void CreateMissile();

public:
	CPlayer();
	~CPlayer();

};

