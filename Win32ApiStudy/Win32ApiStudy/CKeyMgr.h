#pragma once
#include "pch.h"

//1. 프레임동기화
//동일 프레임 내 같은 키에 대해 동일한 이벤트를 가져간다.

//2. 키 입력 이벤트 구체적 정의
// tap, hold ,away

enum class KEY_STATE
{
	NONE, //지금도 예전에도 눌리지 않은 상태
	TAP, //막 누른 시점
	HOLD, // 누르고 있음
	AWAY, //막 뗀 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST,
};

struct tKeyInfo//벡터로 쓸 구조체이다. 이 벡터의 배열값은 어떤 키를 눌렀는지 KEY와 관련있다.
{
	KEY_STATE eState; //키의 상태값
	bool bPrevPush;// 이전 프레임에 눌렸는지 안눌렸는지 확인
};

class CKeyMgr
{
public:
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;
	Vec2 m_vCurMousePos;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
	Vec2 GetMousePos() { return m_vCurMousePos; }

};

