#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include "KeyProcess.h"
#include "Shot.h"

// プレイヤーの初期化
void InitPlayer(Player& player)
{
	// プレイヤーの画像読み込み&座標の初期化
	player.Graph = LoadGraph("data/Fairy.png");
	player.X = kScreenWidth / 2;
	player.Y = 400;

	// プレイヤーの縦横幅
	GetGraphSize(player.Graph, &player.W, &player.H);

	// 移動速度
	player.kSpeed = 3.0f;
	// 落下速度
	player.FallPowor = 0.0f;
	// ジャンプ移動量
	player.JumpPowor = 40.0f;

	// ジャンプ中かどうかのフラグフラグ(押されていないのfalseを挿入)
	player.PushFlag = false;
	// ショットボタンが前のフレームで押されたかどうかを保存する変数にfalse(押されていない)を代入
	player.PrevshotFlag = false;
}

void UpdatePlayer(Player& player, Shot shotArray[], int shotArraySize)
{
	// パッドの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	bool isMove = false;	// 移動中かどうか


	// 矢印キーを押していたらプレイヤーを移動させる
	// ジャンプ
	if (pad && CheckHitKey(KEY_INPUT_UP) == 1)
	{
		//player.Y -= player.JumpPowor;

		player.Y -= 20.0f;
		player.PushFlag = true;
		isMove = true;
	}
	// 屈むが、下移動はしない
	if (pad && CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		player.Y += player.kSpeed;
		isMove = true;
	}
	// 左移動
	if (pad && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		player.X -= player.kSpeed;
		isMove = true;
	}
	// 右移動
	if (pad && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		player.X += player.kSpeed;
		isMove = true;
	}

	//// ジャンプボタンを押していて、地面についていたらジャンプ
	//if (player.Y == Ground) {
	//	if (Pad::IsTrigger(CheckHitKey(KEY_INPUT_RIGHT) == 1))
	//	{
	//		player.Y -= player.JumpPowor;

	//		player.PushFlag = true;
	//		isMove = true;
	//	}
	//}

	// 落下加速度を加える
	player.FallPowor += 0.5f;

	// 落下処理
	player.Y += player.FallPowor;

	// もし地面についていたら止まる
	if (player.Y > Ground)
	{
		player.Y = Ground;

		if (player.Y = Ground)
		{
			player.FallPowor = 0;

			player.PushFlag = false;
		}
	}

	// 弾の発射処理
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// 前フレームでショットボタンを押したかが保存されている変数がfalseだったら弾を発射
		if (player.PrevshotFlag == false)
		{
			// 画面上にでていない弾があるか、弾の数だけ繰り返して調べる
			for (int i = 0; i < shotArraySize; i++)
			{
				// 弾iが画面上にでていない場合はその弾を画面に出す
				if (shotArray[i].Flag == false)
				{
					// 弾iの位置をセット、位置はプレイヤーの中心にする
					shotArray[i].X = (player.W - shotArray[i].W) / 2 + player.X;
					shotArray[i].Y = (player.H - shotArray[i].H) / 2 + player.Y;

					// 弾iは現時点を持って存在するので、存在状態を保持する変数にtrueを代入する
					shotArray[i].Flag = true;

					// 一つ弾を出したので弾を出すループから抜けます
					break;
				}
			}
		}

		// 前フレームでショットボタンを押されていたかを保存する変数にtrue(おされていた)を代入
		player.PrevshotFlag = true;
	}
	else
	{
		// ショットボタンが押されていなかった場合は
		// 前フレームでショットボタンが押されていたかを保存する変数にfalse(おされていない)を代入
		player.PrevshotFlag = false;
	}


	// プレイヤーが画面からはみ出そうになっていたら画面内の座標に戻してあげる
	if (player.X < 0)
	{
		player.X = 0;
	}
	if (player.X > kScreenWidth - player.W)
	{
		player.X = kScreenWidth - player.W;
	}
	if (player.Y < 0)
	{
		player.Y = 0;
	}
	if (player.Y > Ground)
	{
		player.Y = Ground;
	}

}


void DrawPlayer(Player& player)
{
	// プレイヤーの描画
	DrawGraph(player.X, player.Y, player.Graph, false);
}
