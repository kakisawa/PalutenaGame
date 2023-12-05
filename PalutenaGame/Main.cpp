#include "DxLib.h"
#include "Vec2.h"

#include "Player.h"
#include "Shot.h"
#include "Game.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モード変更(解像度・ビット数)
	SetGraphMode(kScreenWidth, kScreenHeight, kColorDepth);

	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);


	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームの処理
	Player player;
	Shot shot[SHOT];


	// プレイヤーの初期化
	player.Init();

	// ショットの初期化
	for (int i = 0; i < SHOT; i++)
	{
		shot[i].Init();
	}

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// プレイヤーの更新
		player.Update(shot, SHOT);

		// プレイヤーの描画
		player.Draw();

		// ショットの描画・更新
		for (int i = 0; i < SHOT; i++)
		{
			shot[i].Update(player);
			shot[i].Draw(player);
		}

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// マイナスの値（エラー値）が返ってきたらループを抜ける
		if (ProcessMessage() < 0)
		{
			break;
		}
		// もしＥＳＣキーが押されていたらループから抜ける
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}