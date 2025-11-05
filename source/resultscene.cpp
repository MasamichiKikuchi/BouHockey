#include "resultscene.h"
#include "gamemainscene.h"

int cgPlayer1Win;
int cgPlayer2Win;
int cgDrow;
//int* win;
//int a;

ResultScene::ResultScene() {
	// 何もしない
}

ResultScene::~ResultScene() {
	// 何もしない
}
void ResultScene::Init() {
	cgPlayer1Win = LoadGraph("res/winresult5.png");
	cgPlayer2Win = LoadGraph("res/winresult6.png");
	cgDrow = LoadGraph("res/Untitled-4.png");
}
void ResultScene::Input() {
	// キー入力、トリガ入力、リリース入力を得る
	GetJoypadXInputState(DX_INPUT_PAD1, &xinput_pad1);			// pad1の入力値を取得
	GetJoypadXInputState(DX_INPUT_PAD2, &xinput_pad2);			// pad2の入力値を取得
	/*win = &winPlayer;
	a = *win;*/
}

void ResultScene::Process() {
	if (xinput_pad1.Buttons[XINPUT_BUTTON_X] == 1) {
		SceneBase* scene = new TitleScene();
		ChangeScene(scene);
	}
	
}

void ResultScene::Draw() {
	ClearDrawScreen();						// 画面を初期化する
	DrawFormatString(0, 20, GetColor(255, 255, 255), "リザルトシーン");
	if (winPlayer == 0) {
		DrawGraph(0, 0, cgDrow, 0);
	}
	else if(winPlayer == 1){
		DrawGraph(0,0, cgPlayer1Win,0);
	}
	else if (winPlayer == 2) {
		DrawGraph(0, 0, cgPlayer2Win, 0);
	}
	ScreenFlip();							// 裏画面の内容を表画面に反映させる
}
