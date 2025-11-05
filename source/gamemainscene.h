#pragma once
#include "SceneBase.h"
#include "character.h"
#include "pack.h"
#include "time.h"
#include "mymath.h"
#include "winmain.h"
#include "gamemain.h"
#include "resultscene.h"
#include "time.h"

//勝利したプレイヤー　０：引き分け、１：プレイヤー１、２：プレイヤー


class GameMainScene : public SceneBase {
public:
	GameMainScene();			// コンストラクタ
	virtual ~GameMainScene();	// デストラクタ
	void    Init()override;
	void	Input()override;	// 入力
	void	Process()override;	// 計算
	void	Draw()override;	// 描画

protected:
	


};
extern int winPlayer;