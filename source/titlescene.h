#pragma once
#include "SceneBase.h"

//int cgBg;

class TitleScene : public SceneBase {
public:

	TitleScene();			// コンストラクタ
	virtual ~TitleScene();	// デストラクタ

	void    Init()override;
	void	Input()override;	// 入力
	void	Process()override;	// 計算
	void	Draw()override;	// 描画

protected:

};