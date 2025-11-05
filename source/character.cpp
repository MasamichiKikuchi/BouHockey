#include	"DxLib.h"
#include	"character.h"
#include	"mymath.h"



CHARACTER::CHARACTER() {
}

CHARACTER::~CHARACTER() {
}

VECTOR CHARACTER::NormInput(XINPUT_STATE xinput)
{
	if (abs(xinput.ThumbLX) > 10000 || abs(xinput.ThumbLY) > 10000)
	{
		vInputL = VGet(xinput.ThumbLX, -xinput.ThumbLY, 0);
		vUnitL = VNorm(vInputL);
		vCenterL = VScale(vUnitL, VECTORSCALE);
	}
	else
	{
		vCenterL = VGet(0, 0, 0);
	}
	pos.x += vCenterL.x;
	pos.y += vCenterL.y;
	//return pos;
	return vCenterL;
}

float DistanceSqrf(const float t_x1, const float t_y1, const float t_x2, const float t_y2)
{
	float dx = t_x2 - t_x1;
	float dy = t_y2 - t_y1;

	return (dx * dx) + (dy * dy);
}


