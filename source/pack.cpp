#include "pack.h"


int PACK::AddBoundCount(int boundCount)
{
	boundCount++;
	return boundCount;
}
int PACK::ResetBoundCount(int boundCount)
{
	boundCount = 0;
	return boundCount;
}

int PACK::PackGradeUp(int boundCount, int grade)
{
	if (boundCount <= 5)grade = PACK_SMALL;
	
	if (6<= boundCount && boundCount <= 10)grade = PACK_MIDUM;
	
	if (11 <= boundCount  )grade = PACK_BIG;
	
	return grade;
}

int PACK::SetPackStatus(int grade,float radius)
{
	switch (grade)
	{
		case PACK_SMALL: 
			radius = PACK_SMALL_RADIUS;
		break;
		case PACK_MIDUM:
			radius = PACK_MIDUM_RADIUS;
		
		break;
		case PACK_BIG:
			radius = PACK_BIG_RADIUS;
			break;

	default:
		break;
	}

	return radius;
	
}


