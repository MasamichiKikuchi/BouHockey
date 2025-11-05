#include "DxLib.h"
#include "titlescene.h"
#include "gamemain.h"
#include "rulescene.h"

int cgTitle;
int PlayGameBGM;
TitleScene::TitleScene() {
	// 何もしない
}

TitleScene::~TitleScene() {
	// 何もしない
}
void TitleScene::Init() {
	PlayGameBGM = LoadSoundMem("res/GamePlay.BGM.wav");
	cgTitle = LoadGraph("res/start_gamen240702.png");
	PlaySoundMem(PlayGameBGM, DX_PLAYTYPE_LOOP);
}
void TitleScene::Input() {
	// キー入力、トリガ入力、リリース入力を得る

	GetJoypadXInputState(DX_INPUT_PAD1, &xinput_pad1);			// pad1の入力値を取得
	GetJoypadXInputState(DX_INPUT_PAD2, &xinput_pad2);			// pad2の入力値を取得
}
	

void TitleScene::Process() {
	if (xinput_pad1.Buttons[XINPUT_BUTTON_LEFT_SHOULDER] == 1) {
		SceneBase* scene = new GameMainScene();
		ChangeScene(scene);
	}
}

void TitleScene::Draw() {
	ClearDrawScreen();						// 画面を初期化する
	DrawGraph(0, 0, cgTitle, true);
	ScreenFlip();							// 裏画面の内容を表画面に反映させる
}