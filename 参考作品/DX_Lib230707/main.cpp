#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include <cassert>

#include "SceneManager.h"

namespace
{
}

/*
// プレイヤーと敵の当たり判定
// 当たっている場合、trueを返す		(return true;する)
// 当たっていない場合、falseを返す	(return false;する)

// プレイヤーと敵の当たり判定
bool IsCollision(const Player& player, const Enemy& enemy)
{
	// 当たり判定
	// プレイヤーよりも完全に左にいる場合は当たっていない
	// プレイヤー左端よりも左に敵の右端がある場合は当たっていない
	if (player.GetLeft() > enemy.GetRight())
	{
		// 完全に左にいるので当たっていないこと確定
		return false;	// 確実に当たっていないのでfalseを返す
	}
	// プレイヤーよりも完全に下にいる場合は当たっていない
	// プレイヤー下端よりも下に敵の上端がある場合は当たっていない
	if (player.GetBottom() < enemy.GetTop())
	{
		// 完全に左にいるので当たっていないこと確定
		return false;	// 確実に当たっていないのでfalseを返す
	}
	// 同様に完全に右にいるパターンを取り除く
	if (player.GetRight() < enemy.GetLeft())
	{
		return false;	// 確実に当たっていないのでfalseを返す

	}
	// 同様に完全に上にいるパターンを取り除く
	if (player.GetTop() > enemy.GetBottom())
	{
		return false;	// 確実に当たっていないのでfalseを返す
	}

	return true;
}

#if false	// コメントを削除してすっきりさせるとこんな感じ
bool IsCollision(const Player& player, const Enemy& enemy)
{
	if (player.GetLeft() > enemy.GetRight())	return false;
	if (player.GetBottom() < enemy.GetTop())	return false;
	if (player.GetRight() < enemy.GetLeft())	return false;
	if (player.GetTop() > enemy.GetBottom())	return false;

	return true;
}
#endif

*/

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	// 画面のサイズ変更
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// シーン
	SceneManager scene;
	scene.Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームシーンの更新
		scene.Update();
		// ゲームシーンの描画
		scene.Draw();

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

		// 実行していたシーンの終了処理
	scene.End();

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}



#if false
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	// 画面のサイズ変更
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);



	SceneMain sceneMain;
	sceneMain.Init();


	// ゲームシーンを準備
	int sceneNo = 0;	// 現在のシーンを変数で持つ
						// 0:Title 1:Main
						// 本来はenum等でやるべき
	SceneTitle  sceneTitle;

	SceneMain sceneMain;
	sceneTitle.Init();

	/*
	int playerHandle = LoadGraph("data/player.png");
	assert(playerHandle != -1);	// グラフィックのロードに失敗していたら止める
	int enemyHandle = LoadGraph("data/enemy.png");
	assert(enemyHandle != -1);	// グラフィックのロードに失敗していたら止める

	Player player;
	player.Init();
	player.SetGraphHandle(playerHandle);

	Enemy enemy;
	enemy.Init();
	enemy.SetGrahpHandle(enemyHandle);
	enemy.SetStartPos();	// グラフィックを設定した後初期値に設定
	*/

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理

		sceneMain.Update();
		sceneMain.Draw();


		switch (sceneNo)
		{
		case 0:
			sceneTitle.Update();
			sceneTitle.Draw();
			if (sceneTitle.isEnd())	// タイトル終了
			{
				// タイトルを終了処理
				sceneTitle.End();

				// 次のシーンを用意する
				sceneNo = 1;	// SceneMainに変更
				sceneMain.Init();
			}
			break;
		case 1:
			sceneMain.Update();
			sceneMain.Draw();
			break;
		default:
			assert(false);	// 存在しないシーンの番号が指定されている
			break;
		}

		/*
		if (IsCollision(player, enemy))
		{
			// 当たっているかどうかを確認するデバッグ表示
			DrawString(8, 8, "当たっている", GetColor(255, 255, 255));
		}
		*/

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// シーンの終了
		if (sceneMain.IsSceneEnd())
		{
			break;
		}

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

	// シーンの終了処理
	sceneMain.End();

	switch (sceneNo)
	{
	case 0:
		sceneTitle.Init();
		break;
	case 1:
		sceneMain.Init();
		break;
	default:
		assert(false);	// 存在しないシーンの番号が指定されている
		break;
	}

	/*
	// メモリからグラフィックを削除する
	DeleteGraph(playerHandle);
	DeleteGraph(enemyHandle);
*/

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
#endif