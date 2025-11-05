// 独自計算ライブラリ
#include "mymath.h"


// 当たり判定用。2つのboxが当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitBox(
	int x1, int y1, int w1, int h1,		// ひとつめのbox 左上(x,y), 大きさw,h
	int x2, int y2, int w2, int h2		// ふたつめのbox 左上(x,y), 大きさw,h
) {
	if (x1 < x2 + w2 && x2 < x1 + w1		// x方向の判定
		&& y1 < y2 + h2 && y2 < y1 + h1		// y方向の判定
		)
	{
		// 2つのboxは当たっている
		return 1;
	}

	// 2つのboxは当たっていない
	return 0;
}


// 当たり判定用。2つの円が当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitCircle(
	int x1, int y1, int r1,		// ひとつめのcircle 中心(x,y), 半径r
	int x2, int y2, int r2		// ふたつめのcircle 中心(x,y), 半径r
) {
	int w, h, r;
	w = x1 - x2;
	h = y1 - y2;
	r = r1 + r2;
	if (r * r > w * w + h * h) {
		return 1;
	}
	return 0;
}

// 当たり判定用。boxと円が当たったかを判定
int IsHitBoxCircle(
	int x1, int y1, int w1, int h1,		// box 左上(x,y), 大きさw,h
	float x2, float y2		// circle 中心(x,y), 半径r
){
	int  dx, dy;

		dx = x2 - (x1 +(w1 / 2));
		dy = y2 - (y1 +(h1 / 2));
		if (x1 < x2 && x2 < x1 + w1 && y1 < y2 && y2 < y1 + h1) {
		
		return 1;
	}

	return 0;
}

// 当たり判定用。boxと円が当たったかを判定
int IsHitBoxCircle(
	int x1, int y1, int w1, int h1,		// box 左上(x,y), 大きさw,h
	float x2, float y2, float r2		// circle 中心(x,y), 半径r
) {
	int  dx, dy;

	dx = x2 - (x1 + (w1 / 2));
	dy = y2 - (y1 + (h1 / 2));
	if (x1 - r2 < x2 && x2 < x1 + w1 + r2 && y1 - r2 < y2 && y2 < y1 + h1 + r2) {

		return 1;
	}

	return 0;
}

int CheckHitAll(VECTOR pos1, VECTOR r1, int type1, VECTOR pos2, VECTOR r2, int type2) {
	VECTOR tmp = VSub(pos2, pos1);
	tmp = VNorm(tmp);
	double tmpX1, tmpX2;
	if (tmp.x < 0) {
		tmpX1 = -pow(-tmp.x, 2 / type1);
		tmpX2 = pow(-tmp.x, 2 / type2);
	}
	else {
		tmpX1 = pow(tmp.x, 2 / type1);
		tmpX2 = -pow(tmp.x, 2 / type2);
	}
	double tmpY1, tmpY2;
	if (tmp.y < 0) {
		tmpY1 = -pow(-tmp.y, 2 / type1);
		tmpY2 = pow(-tmp.y, 2 / type2);
	}
	else {
		tmpY1 = pow(tmp.y, 2 / type1);
		tmpY2 = -pow(tmp.y, 2 / type2);
	}
	//double X1, X2;
	tmpX1 = tmpX1 * r1.x; tmpX2 = tmpX2 * r2.x;
	tmpX1 += pos1.x; tmpX2 += pos2.x;
	tmpX1 *= tmp.x; tmpX2 *= tmp.x;
	//double Y1, Y2;
	tmpY1 = tmpY1 * r1.y; tmpY2 = tmpY2 * r2.y;
	tmpY1 += pos1.y; tmpY2 += pos2.y;
	tmpY1 *= tmp.y; tmpY2 *= tmp.y;
	if (tmpX1 >= tmpX2 && tmpY1 >= tmpY2) {
		return 1;
	}
	return 0;
}