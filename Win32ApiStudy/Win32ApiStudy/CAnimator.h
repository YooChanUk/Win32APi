#pragma once


class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*> m_mapAnim; //��� �ִϸ��̼�
	CAnimation* m_pCurAnim;//���� ������� �ִϸ��̼�
	CObject* m_pOwner;//animator�� ������ ������Ʈ
	bool m_bRepeat;

public:
	void CreateAnimation(const wstring& _strName,CTexture* _pTex,Vec2 _vLT,Vec2 _vSliceSize,Vec2 _vStep ,float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName,bool _bRepeat);

	void update();
	void finalupdate();
	void render(HDC _dc);

	CObject* GetObj() { return m_pOwner; }

public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

