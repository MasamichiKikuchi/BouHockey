// Game.cpp
#include "gamemainscene.h"

//
// 定数・構造体定義
//
#define PLAYER1_X		(510)
#define	PLAYER1_Y		(534)
#define PLAYER2_X		(1400)
#define	PLAYER2_Y		(534)
#define PLAYER_RADIUS	(64)

#define PLAYER_X_MIN		(180)
#define PLAYER_X_MAX		(1750)
#define PLAYER_Y_MIN		(170)
#define PLAYER_Y_MAX		(900)

#define PACK_X		(962)
#define PACK_Y		(500)

#define GOAL_MAX	(2)
#define GOAL_W	(64)
#define GOAL_H	(384)

#define FENCE_MAX	(72)

#define PACK_SPEED_ADJUSTMENT	(0.2)
#define PACK_SPEED_ACCELERATION	(1.5)

#define PACK_SMALL_SCORE	(1)
#define PACK_MIDUM_SCORE	(2)
#define PACK_BIG_SCORE		(4)

#define GAME_TIME 100 // 制限時間

#define EFFECT_TYPE_NORMAL 0
#define EFFECT_TYPE_FIRE   1
#define EFFECT_TYPE_CRASH 2 // 新しいエフェクトの種類を追加


CHARACTER	character[CHARACTER_MAX];
PACK pack;

int player1Score;
int player2Score;
int winPlayer;
int gTrg;
int gKey;

int lastTouchPlayer;

//時間
int remainingTime;

struct GOAL
{
	//座標（左上）
	int x, y;
	//幅と高さ
	int w, h;
};

GOAL goal[GOAL_MAX];

struct FENCE
{
	//フェンスが使用可能か　0:使用可能　1：使用不能
	int use;
	//フェンスの配置　1：横用　2：縦用
	int orientation;
	//座標（左上）
	int x, y;
	//幅と高さ
	int w, h;

};

FENCE fence[FENCE_MAX];

// エフェクト用の構造体と関数
struct EFFECT {
	int use;
	int type;
	int x, y;
	int animcnt;
	int animspeed;
	int animnum;
};

#define EFFECT_MAX (30)

EFFECT effect[EFFECT_MAX];


//
// グローバル変数宣言


// ゲーム情報
VECTOR moveVecter = VGet(0, 0, 0); //パッドの移動値

time_t startTime;           // ゲーム開始時の時間

// 画像		
int cgCharacter[CHARACTER_MAX];	// プレイヤーとパッド
int cgSmallPack;
int cgMediumPack;
int cgBiggPack;
int cgGoal;//ゴール
int cgBg;
int fence_red_side;
int fence_red_warp;
int fence_blue;
int cgEffect[4][6];
int cgFinish;	//FINISH画像
int cgPack[PACK_GRADE_NUM];


//	音
int soundGoal;
int soundFenceCrash;
int soundFenceBreak;


GameMainScene::GameMainScene() {

};			// コンストラクタ
GameMainScene::~GameMainScene() {};	// デストラクタ
// 配列にキャラを追加する
// 引数：
//	type = 追加するキャラタイプ
//	x, y = 座標
// 戻り値：
//	-1 : 追加できなかった
//	0～ : chara[]配列番号
int AddCharacter(int type, float x, float y, float radius, int speed) {
	// 未使用配列を探す
	for (int i = 0; i < CHARACTER_MAX; i++) {
		if (character[i].type == CHARACTER_TYPE_NONE) {
			// 未使用配列に情報を設定
			character[i].type = type;
			character[i].pos = VGet(x, y, 0);
			character[i].radius = radius;
			character[i].speed = speed;
			return i;	// 追加した配列番号を返す
		}
	}
	// 見つからなかった
	return -1;
}
void PackInit(int grade, float x, float y, float radius, int speed) {

	pack.grade = grade;
	pack.pos = VGet(x, y, 0);
	pack.radius = radius;
	pack.speed = speed;
}

void GoalInit(int i, int x, int y, int w, int h) {

	//情報を設定
	goal[i].x = x;
	goal[i].y = y;
	goal[i].w = w;
	goal[i].h = h;
}

void FenceInit(int i, int use, int orientation, int x, int y, int w, int h) {

	//情報を設定
	fence[i].orientation = orientation;
	fence[i].use = use;
	fence[i].x = x;
	fence[i].y = y;
	fence[i].w = w;
	fence[i].h = h;
}
void FenceReset() {

	for (int i = 0; i < FENCE_MAX; i++)
	{
		fence[i].use = 0;
	}
	
	
}

VECTOR InversionVecter(int a, VECTOR moveVecter) {

	if (a == 0) {
		moveVecter.x = moveVecter.x * -1;
	}
	if (a == 1) {
		moveVecter.y = moveVecter.y * -1;
	}
	return moveVecter;
}

VECTOR MovePuck() {

	// 当たり判定と押し出し処理
	for (int i = 0; i < CHARACTER_MAX; i++) {
		VECTOR tmp = VNorm(character[i].vCenterL);
		for (int t = 0; t < VECTORSCALE; t++) {
			VECTOR tmpos = VAdd(character[i].pos, VScale(tmp, (t + 1)));
			if (IsHitCircle(
				character[i].pos.x, character[i].pos.y, character[i].radius,
				pack.pos.x, pack.pos.y, pack.radius
			) != 0) {

				lastTouchPlayer = i;
				moveVecter.x = (pack.pos.x - character[i].pos.x) * PACK_SPEED_ADJUSTMENT + character[i].vCenterL.x;
				moveVecter.y = (pack.pos.y - character[i].pos.y) * PACK_SPEED_ADJUSTMENT + character[i].vCenterL.y;

				t = VECTORSCALE;
				break;
			}
		}
	}
	float acceleration;
	if (pack.grade == PACK_BIG || pack.grade == PACK_MIDUM)
	{
		acceleration = PACK_SPEED_ACCELERATION;
	}
	else
	{
		acceleration = 1;
	}

	pack.pos.x += moveVecter.x * acceleration;
	pack.pos.y += moveVecter.y * acceleration;

	return pack.pos;
}
VECTOR PlayerMoveLimit(VECTOR playerVector)
{
	if (playerVector.x < PLAYER_X_MIN)playerVector.x = PLAYER_X_MIN;
	if (playerVector.x > PLAYER_X_MAX)playerVector.x = PLAYER_X_MAX;
	if (playerVector.y < PLAYER_Y_MIN)playerVector.y = PLAYER_Y_MIN;
	if (playerVector.y > PLAYER_Y_MAX)playerVector.y = PLAYER_Y_MAX;

	return playerVector;
}


void AddEffect(int type, int x, int y) {
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].use == 0) {
			effect[i].use = 1;
			effect[i].type = type;
			effect[i].x = x;
			effect[i].y = y;
			effect[i].animcnt = 0;
			effect[i].animspeed = 4;
			effect[i].animnum = 6;
			break;
		}
	}
}

void DrawEffect() {
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].use != 0) {
			int animindex = effect[i].animcnt / effect[i].animspeed;
			if (animindex < effect[i].animnum) {
				DrawGraph(effect[i].x, effect[i].y, cgEffect[effect[i].type][animindex], TRUE);
				effect[i].animcnt++;
			}
			else {
				effect[i].use = 0;
			}
		}
	}
}

void InitEffect() {
	for (int i = 0; i < EFFECT_MAX; i++) {
		effect[i].use = 0;
	}
}
int AddScore(int score) {

	switch (pack.grade)
	{
	case PACK_SMALL:
		score += PACK_SMALL_SCORE;
		break;
	case PACK_MIDUM:
		score += PACK_MIDUM_SCORE;
		break;
	case PACK_BIG:
		score += PACK_BIG_SCORE;
		break;
	}


	return score;
}


int JudgeGoal() {

	for (int i = 0; i < GOAL_MAX; i++)
	{
		if (IsHitBoxCircle(
			goal[i].x, goal[i].y, goal[i].w, goal[i].h,
			pack.pos.x, pack.pos.y)
			!= 0) {
			// 当たっている
			int goalCenterX = goal[i].x + goal[i].w / 2;
			int goalCenterY = goal[i].y + goal[i].h / 2;

			if (i == 0) {
				player2Score = AddScore(player2Score);
				AddEffect(0, goalCenterX - 770, goalCenterY - 200);
			}
			else if (i == 1) {
				player1Score = AddScore(player1Score);
				AddEffect(0, goalCenterX - 770, goalCenterY - 200);
			}

			// 効果音を再生
			PlaySoundMem(soundGoal, DX_PLAYTYPE_BACK);

			return 1;
		}
	}
	return 0;
}

int JudgeOutOfRange(VECTOR pos)
{
	if (pos.x < 0 || pos.x > SCREEN_W || pos.y < 0 || pack.pos.y > SCREEN_H) {
		return  1;
		// パックが場外に出た時のエフェクト
		AddEffect(EFFECT_TYPE_NORMAL, pos.x, pos.y);

	}
	return 0;
}

void FenceHit()
{
	for (int i = 0; i < FENCE_MAX; i++)
	{
		if (fence[i].use == 0)
		{
			if (IsHitBoxCircle(
				fence[i].x, fence[i].y, fence[i].w, fence[i].h,
				pack.pos.x, pack.pos.y, pack.r)
				!= 0) {
				// 当たっている
				if (pack.grade == PACK_BIG) {
					fence[i].use = 1;

					// 柵破壊のエフェクトを追加
					AddEffect(EFFECT_TYPE_CRASH, fence[i].x + (fence[i].w / 2) - 192, fence[i].y + (fence[i].h / 2) - 160);
					// 柵破壊音の追加
					PlaySoundMem(soundFenceBreak, DX_PLAYTYPE_BACK);

					continue;
				}
				if (fence[i].orientation == 0)moveVecter = InversionVecter(1, moveVecter);
				if (fence[i].orientation == 1)moveVecter = InversionVecter(0, moveVecter);
				pack.boundCount = pack.AddBoundCount(pack.boundCount);

				PlaySoundMem(soundFenceCrash, DX_PLAYTYPE_BACK);	//SE

				// 火花エフェクトの追加と位置を調整
				int effectX = fence[i].x + (fence[i].w / 2) - 192; // 火花位置調整用
				int effectY = fence[i].y + (fence[i].h / 2) - 224; // 火花位置調整用
				AddEffect(1, effectX, effectY);
			}
		}
	}
}

void PositionReset()
{
	pack.pos.x = PACK_X;
	pack.pos.y = PACK_Y;
	moveVecter = VGet(0, 0, 0);
	character[0].pos.x = PLAYER1_X;
	character[0].pos.y = PLAYER1_Y;
	character[1].pos.x = PLAYER2_X;
	character[1].pos.y = PLAYER2_Y;
}

void JudgeWinner() {

	if (player1Score == player2Score)winPlayer = 0;

	else if (player1Score > player2Score)winPlayer = 1;
	
	else if (player1Score < player2Score)winPlayer = 2;


}


// アプリの初期化
// 起動時に1回だけ実行される
void GameMainScene :: Init() {
	
	player1Score = 0;
	player2Score = 0;
	// 画像のロード
	cgGoal = LoadGraph("res/ball.png");
	cgPack[0] = LoadGraph("res/blonzepack64.png");
	cgPack[1] = LoadGraph("res/silberpack128.png");
	cgPack[2] = LoadGraph("res/goldpack256.png");

	cgCharacter[0] = LoadGraph("res/padlered big.png");
	cgCharacter[1] = LoadGraph("res/padleblue big.png");
	cgBg = LoadGraph("res/haikei.png");
	fence_red_side = LoadGraph("res/redfence.front.png");
	fence_red_warp = LoadGraph("res/redfence.righet.png");
	fence_blue = LoadGraph("res/柵(青)光沢3.png");
	cgFinish = LoadGraph("res/font_finish.png");		//フィニッシュ文字のロード

	cgEffect[0][0] = LoadGraph("res/kin effect1.png");
	cgEffect[0][1] = LoadGraph("res/kin effect2.png");
	cgEffect[0][2] = LoadGraph("res/kin effect3.png");
	cgEffect[0][3] = LoadGraph("res/kin effect4.png");
	cgEffect[0][4] = LoadGraph("res/kin effect5.png");
	cgEffect[0][5] = LoadGraph("res/kin effect6.png");

	cgEffect[1][0] = LoadGraph("res/hibana effect1.png");
	cgEffect[1][1] = LoadGraph("res/hibana effect2.png");
	cgEffect[1][2] = LoadGraph("res/hibana effect3.png");
	cgEffect[1][3] = LoadGraph("res/hibana effect4.png");
	cgEffect[1][4] = LoadGraph("res/hibana effect5.png");

	cgEffect[2][0] = LoadGraph("res/distortionredfence.front.png");
	cgEffect[2][1] = LoadGraph("res/breakeffect1.png");
	cgEffect[2][2] = LoadGraph("res/breakeffect2.png");
	cgEffect[2][3] = LoadGraph("res/breakeffect3.png");
	cgEffect[2][4] = LoadGraph("res/breakeffect4.png");
	cgEffect[2][5] = LoadGraph("res/breakeffect5.png");

	//効果音の挿入
	soundGoal = LoadSoundMem("res/Goal.wav");
	soundFenceCrash = LoadSoundMem("res/HitPandP.wav");
	soundFenceBreak = LoadSoundMem("res/FenceBreak.wav");


	
	DeleteSoundMem;
	InitEffect();

	//パックの設定
	PackInit(PACK_SMALL, PACK_X, SCREEN_H / 2, PACK_SMALL_RADIUS, 1);

	int i = 0;
	//プレイヤー１の設定
	i = AddCharacter(CHARACTER_TYPE_PLAYER1, PLAYER1_X, PLAYER1_Y, PLAYER_RADIUS, 2);
	//プレイヤー２の設定
	i = AddCharacter(CHARACTER_TYPE_PLAYER2, PLAYER2_X, PLAYER2_Y, PLAYER_RADIUS, 2);

	//ゴールの配置
	GoalInit(0, 64, 340, GOAL_W, GOAL_H);
	GoalInit(1, 1792, 340, GOAL_W, GOAL_H);

	for (int t = 0; t < FENCE_MAX; t++)
	{
		FenceInit(t, 0, 0, (t + 1) * 64, 50, 64, 64);
		if (t >= 28)
		{
			FenceInit(t, 0, 0, (t - (28 - 1)) * 64, 945, 64, 64);
		}
		if (t >= 56)
		{
			FenceInit(t, 0, 1, 64, ((t - 56) * 64) + 100, 64, 64);
		}
		if (t >= 60)
		{
			FenceInit(t, 0, 1, 64, ((t - 56) * 64) + (70 + 384), 64, 64);
		}
		if (t >= 64)
		{
			FenceInit(t, 0, 1, 64 * 28, ((t - 64) * 64) + 100, 64, 64);
		}
		if (t >= 68)
		{
			FenceInit(t, 0, 1, 64 * 28, ((t - 64) * 64) + (70 + 384), 64, 64);
		}

	}
	startTime = time(NULL); // ゲーム開始時の時間を記録

	winPlayer = -1;
}

void GameMainScene::Input() {
	
	// キー入力、トリガ入力、リリース入力を得る
	int keyold = gKey;
	gKey = GetJoypadXInputState(DX_INPUT_PAD1, &xinput_pad1);			// pad1の入力値を取得
	gTrg = (gKey ^ keyold) & gKey;
	
	
	GetJoypadXInputState(DX_INPUT_PAD2, &xinput_pad2);			// pad2の入力値を取得

}

void GameMainScene::Process() {
	time_t currentTime = time(NULL); // 現在の時間を取得
	int elapsedTime = (int)difftime(currentTime, startTime); // 経過時間を計算
	remainingTime = GAME_TIME - elapsedTime;
	if(remainingTime >0)
	{ 
	// 最新の状態
	// キャラクター（パック）の移動
	pack.pos = MovePuck();
	// キャラクター（プレイヤー）の移動
	character[0].pos = VAdd(character[0].pos, character[0].NormInput(xinput_pad1));
	character[1].pos = VAdd(character[1].pos, character[1].NormInput(xinput_pad2));
	// キャラクター（プレイヤー）の移動制限
	character[0].pos = PlayerMoveLimit(character[0].pos);
	character[1].pos = PlayerMoveLimit(character[1].pos);

	if (JudgeOutOfRange(pack.pos) == 1)
	{
		switch (lastTouchPlayer)
		{
		case 0:
			player1Score = AddScore(player1Score);
			break;
		case 1:
			player2Score = AddScore(player2Score);
			break;
		}

	}
	
	//パックとフェンスの再配置
	if (JudgeGoal() == 1 || JudgeOutOfRange(pack.pos) == 1)
	{
		PositionReset();
		pack.boundCount = pack.ResetBoundCount(pack.boundCount);		
		FenceReset();
	}

	FenceHit();
	pack.grade = pack.PackGradeUp(pack.boundCount, pack.grade);
	pack.radius = pack.SetPackStatus(pack.grade, pack.radius);

	}

	if (remainingTime == 0) {

		JudgeWinner();
	}

	if (remainingTime == -5 ) {
	
		SceneBase* scene = new ResultScene();
		ChangeScene(scene);	
	}	
}

void GameMainScene::Draw() {
	int i;

	ClearDrawScreen();						// 画面を初期化する

	DrawGraph(0, 0, cgBg, TRUE);

	for (int i = 0; i < FENCE_MAX; i++)
	{
		if (fence[i].use == 0)DrawGraph(fence[i].x, fence[i].y, fence_red_side, TRUE);
	}

	// キャラクター表示
	for (i = 0; i < CHARACTER_MAX; i++) {
		if (character[i].type == CHARACTER_TYPE_NONE) { continue; }		// noneは処理しない
		// キャラタイプ別に画像を選択
		int cg = -1;
		switch (character[i].type) {

		case CHARACTER_TYPE_PLAYER1:
			cg = cgCharacter[i];
			DrawGraph(character[i].pos.x - 64, character[i].pos.y - 64, cg, true);
			break;
		case CHARACTER_TYPE_PLAYER2:
			cg = cgCharacter[i];
			DrawGraph(character[i].pos.x - 64, character[i].pos.y - 64, cg, true);
			break;
		}

	}
	if (pack.grade == PACK_SMALL)
	{
		DrawGraph(pack.pos.x - PACK_SMALL_RADIUS, pack.pos.y - PACK_SMALL_RADIUS, cgPack[pack.grade - 1], true);
	}
	if (pack.grade == PACK_MIDUM)
	{
		DrawGraph(pack.pos.x - PACK_MIDUM_RADIUS, pack.pos.y - PACK_MIDUM_RADIUS, cgPack[pack.grade - 1], true);
	}
	if (pack.grade == PACK_BIG)
	{
		DrawGraph(pack.pos.x - PACK_BIG_RADIUS, pack.pos.y - PACK_BIG_RADIUS, cgPack[pack.grade - 1], true);
	}

	//開発用
	/*
	SetFontSize(20);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "プレイヤー１座標 X:%f Y%f:", character[1].pos.x, character[1].pos.y);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "パッド座標 X:%f Y%f:", moveVecter.x, moveVecter.y);
	
	DrawFormatString(0, 80, GetColor(255, 255, 255), "パックグレード:%d:", pack.grade);
	DrawCircle(pack.pos.x, pack.pos.y, 3, (255, 0, 0), 1);
	DrawCircle(character[0].pos.x, character[0].pos.y, 3, (255, 0, 0), 1);
	DrawCircle(character[1].pos.x, character[1].pos.y, 3, (255, 0, 0), 0);
	for (int i = 0; i < CHARACTER_MAX; i++)
	{
		DrawCircle(character[i].pos.x, character[i].pos.y, character[i].radius, (255, 0, 0), 0);
	}
	//DrawCircle(pack.pos.x, pack.pos.y, pack.radius, (255, 0, 0), 1);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "最後に触ったプレイヤー :%d", lastTouchPlayer + 1);
	*/
	SetFontSize(64);
	DrawFormatString(700, 10, GetColor(255, 255, 255), "バウンド回数:%d", pack.boundCount);
	//エフェクト描画
	DrawEffect();

	//得点描画
	SetFontSize(64);
	DrawFormatString(260, 10, GetColor(255, 0, 0), "Player 1: %d", player1Score);
	DrawFormatString(SCREEN_W - 650, 10, GetColor(0, 0, 255), "Player 2: %d", player2Score);

	time_t currentTime = time(NULL); // 現在の時間を取得
	int elapsedTime = (int)difftime(currentTime, startTime); // 経過時間を計算
	int remainingTime = GAME_TIME - elapsedTime;


	if (remainingTime <= 0) {															//
		DrawGraph(SCREEN_W / 2 - 550, SCREEN_H / 2 - 170, cgFinish, TRUE);				//FINISHの位置
	}

	SetFontSize(64);	//制限時間のフォントの大きさ
	if (remainingTime >= 0) {
		DrawFormatString(800, 120, GetColor(255, 10, 255), "Time: %d", remainingTime);		//制限時間の位置
	}

	ScreenFlip();							// 裏画面の内容を表画面に反映させる
}


