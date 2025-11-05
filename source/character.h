#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "DxLib.h"

#define	CHARACTER_MAX	(2)	// キャラクター数（パッド、プレイヤー）
#define	CHARACTER_TYPE_NONE		(0)	// タイプ無し（配列未使用
#define	CHARACTER_TYPE_PLAYER1	(1)	// プレイヤー1
#define	CHARACTER_TYPE_PLAYER2	(2)	// プレイヤー2
#define VECTORSCALE	(15)

class CHARACTER
{
public:
	CHARACTER();
	virtual ~CHARACTER();

	int		type;		// プレイヤータイプ
	VECTOR	pos;		// 座標（DXライブラリのベクトル使用）
	int		r;		// 半径サイズ
	float	direction;	// 向き(度数)
	int		w, h;		// 画像のサイズ
	float	speed;		// 移動力
	int cX, cY;
	int radius; //半径
	VECTOR vCenterL;

	VECTOR NormInput(XINPUT_STATE xinput);
	
	
private:
	//コントローラー入力関係
	VECTOR vInputL;
	VECTOR vUnitL;
	float radL;
	float degL;

};





