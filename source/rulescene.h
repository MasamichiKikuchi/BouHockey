#pragma once
#include "DxLib.h"
#include "SceneBase.h"
#include "gamemainscene.h"

class RuleScene : public SceneBase {
public:
	RuleScene();			// コンストラクタ
	virtual ~RuleScene();	// デストラクタ

	void    Init()override;
	void	Input()override;	// 入力
	void	Process()override;	// 計算
	void	Draw()override;	// 描画

protected:

};