#include "DxLib.h"
#include "Vec2.h"
#include <cmath>

namespace
{
	// 画面幅(横)
	int kScreenWidth = 720;
	// 画面幅(縦)
	int kScreenHeight = 480;
	// カラービット数
	int kColorDepth = 32;

	// プレイヤーのサイズ
	int kWidth = 32;
	int kHeight = 32;

	// プレイヤーの初期位置
	int PlayerX = kScreenWidth / 2;
	int PlayerY = 400;

	// 地面
	int Ground = 400;

	// 移動速度
	float kSpeed = 3.0f;

	// ジャンプ移動量
	float JumpPower = 0.0f;

	// ジャンプボタンフラグ
	int push = 0;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モード変更(解像度・ビット数)
	SetGraphMode(kScreenWidth, kScreenHeight, 32);


	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// プレイヤーのロード
	int handle = LoadGraph("data/Fairy.png");

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// ゲームの処理

		// 矢印キーを押していたらプレイヤーを移動させる
		// ジャンプ
		if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			PlayerY -= 3;
		}
		// 屈むが、下移動はしない
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			PlayerY += 3;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			PlayerX -= 3;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			PlayerX += 3;
		}

		// プレイヤーが画面からはみ出そうになっていたら画面内の座標に戻してあげる
		if (PlayerX < 0)
		{
			PlayerX = 0;
		}
		if (PlayerX > kScreenWidth - kWidth)
		{
			PlayerX = kScreenWidth - kWidth;
		}
		if (PlayerY < 0)
		{
			PlayerY = 0;
		}
		if (PlayerY > Ground)
		{
			PlayerY = Ground;
		}

		// 落下処理
		PlayerY -= JumpPower;

		// 落下加速度を加える
		JumpPower -= 1;

		// もし地面についていたら止まる
		if (PlayerY > Ground)
		{
			PlayerY = Ground;
			JumpPower = 0;
		}

		// ジャンプボタンを押していて、地面についていたらジャンプ
		if (CheckHitKey(KEY_INPUT_A) && PlayerY == Ground)
		{
			JumpPower = 10;
			push = 1;
		}



		// 描画を行う前に画面をクリアする
		ClearDrawScreen();
		// プレイヤーの描画
		DrawGraph(PlayerX, PlayerY, handle, false);
		

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

	DeleteGraph(handle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}