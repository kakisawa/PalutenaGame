#include "DxLib.h"
#include "Vec2.h"
#include "Game.h"

#include "SceneMain.h"
#include "Player.h"
#include "SceneTitle.h"
#include "SceneManager.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モード変更(解像度・ビット数)
	SetGraphMode(kScreenWidth, kScreenHeight, kColorDepth);

	// 一部の関数はDxLib_Init()の前に実行する必要がある
	//ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* pSceneManager=new SceneManager;
	pSceneManager->Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		pSceneManager->Update();

		// シーンの描画
		pSceneManager->Draw();

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

	pSceneManager->End();


	delete pSceneManager;
	pSceneManager = nullptr;

	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}