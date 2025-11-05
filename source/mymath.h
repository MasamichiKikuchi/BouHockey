#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include <math.h>
#include "DxLib.h"
// 円周率
#define	PI				(3.141592653589793)


// 当たり判定用。2つのboxが当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitBox(
	int x1, int y1, int w1, int h1,		// ひとつめのbox 左上(x,y), 大きさw,h
	int x2, int y2, int w2, int h2		// ふたつめのbox 左上(x,y), 大きさw,h
);


// 当たり判定用。2つの円が当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitCircle(
	int x1, int y1, int r1,		// ひとつめのcircle 中心(x,y), 半径r
	int x2, int y2, int r2		// ふたつめのcircle 中心(x,y), 半径r
);

int IsHitBoxCircle(
	int x1, int y1, int w1, int h1,		// box 左上(x,y), 大きさw,h
	float x2, float y2 		// circle 中心(x,y), 半径r
);

int IsHitBoxCircle(
	int x1, int y1, int w1, int h1,		// box 左上(x,y), 大きさw,h
	float x2, float y2, float r2		// circle 中心(x,y), 半径r
);

int CheckHitAll(
	VECTOR pos1, VECTOR r1, int type1, 
	VECTOR pos2, VECTOR r2, int type2);

	
	