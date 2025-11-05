#pragma once
#include "DxLib.h"
#include "SceneBase.h"
#include "gamemain.h"
#include "titlescene.h"


class ResultScene : public SceneBase {
public:
	ResultScene();			// コンストラクタ
	virtual ~ResultScene();	// デストラクタ

	void    Init()override;
	void	Input()override;	// 入力
	void	Process()override;	// 計算
	void	Draw()override;	// 描画

protected:

};