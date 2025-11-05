#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "gamemainscene.h"
// 他のcppでも使いたいグローバル変数は、ヘッダファイルでextern宣言する

// ゲーム情報
extern XINPUT_STATE xinput_pad1;	// pad1の入力値
extern XINPUT_STATE xinput_pad2;	// pad2の入力値


// 呼び出すシーンの設定
extern int gSceneType;		// 0:Scene, 1:SceneGameMain, 2:SceneGameOver


void GameMain();	// gamemain.cpp に実体を記述

void ChangeScene(SceneBase* scene);
