#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// 使用するフォントを準備する

	// ********** フォントのロード **********
	LPCSTR font_path = "Font/mogihaPen.ttf"; // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	// ********** ここから読み込んだフォントを利用できる **********

	// タイトル表示用のフォント
	int titleFont = CreateFontToHandle("モギハ・ペン字Font", 64, -1);
	int explanationFontHandle = CreateFontToHandle("HGP創英角ﾎﾟｯﾌﾟ体", 32, -1);

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理

		/*SetFontSize(64);
		ChangeFont("HG丸ｺﾞｼｯｸM-PRO");
		DrawString(100, 100, "フォントのテスト", 0xffffff);
		SetFontSize(32);
		DrawString(160, 200, "ボタンを押してください", 0xffffff);*/

		DrawStringToHandle(100, 100, "ゲームのタイトル", 0xffffff, titleFont);
		DrawStringToHandle(160, 200, "ボタンを押してください", 0xffffff, explanationFontHandle);

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
	DeleteFontToHandle(titleFont);
	DeleteFontToHandle(explanationFontHandle);

	// ********** フォントのアンロード **********
	if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
		// アンロードに成功
	}
	else {
		// アンロードに失敗
		MessageBox(NULL, "remove failure", "", MB_OK);
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}