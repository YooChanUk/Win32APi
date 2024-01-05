#pragma once
#include "pch.h"

#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							\
							return &mgr;\
						}\
						private:\
							type();\
							~type();


#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()