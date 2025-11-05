#include "rulescene.h"
#include "gamemain.h"



RuleScene::RuleScene() {
	// 何もしない
}

RuleScene::~RuleScene() {
	// 何もしない
}
void RuleScene::Init() {
	winPlayer;
}
void RuleScene::Input() {
	// キー入力、トリガ入力、リリース入力を得る
	GetJoypadXInputState(DX_INPUT_PAD1, &xinput_pad1);			// pad1の入力値を取得
	GetJoypadXInputState(DX_INPUT_PAD2, &xinput_pad2);			// pad2の入力値を取得

}

void RuleScene::Process() {
	if (xinput_pad1.Buttons[XINPUT_BUTTON_A] == 1) {
		SceneBase* scene = new GameMainScene();
		ChangeScene(scene);
	}
}
	


void RuleScene::Draw() {
	ClearDrawScreen();						// 画面を初期化する
	DrawFormatString(0, 20, GetColor(255, 255, 255), "ルールシーン");
	ScreenFlip();							// 裏画面の内容を表画面に反映させる
}
