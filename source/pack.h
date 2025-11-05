#pragma once
#include"character.h"

#define PACK_GRADE_NUM (3)
#define PACK_SMALL	(1)
#define PACK_MIDUM	(2)
#define PACK_BIG	(3)

#define PACK_SMALL_RADIUS	(32)
#define PACK_MIDUM_RADIUS	(64)
#define PACK_BIG_RADIUS	(128)


class PACK :public CHARACTER {
public:
	int grade;
	int boundCount;
	int AddBoundCount(int boundCount);
	int ResetBoundCount(int boundCount);
	int PackGradeUp(int boundCount,int grade);
	int SetPackStatus(int grade, float radius);

protected:
	
};


