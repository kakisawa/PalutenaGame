#include "DxLib.h"
#include "Player.h"
#include "Shot.h"
#include "Game.h"

#define PI    3.1415926535897932384626433832795f

namespace
{
	// 弾の移動速度
	constexpr int kSpeed = 16;

	// 弾のサイズ
	constexpr int kWidth = 16;
	constexpr int kHeight = 8;
}

// ショットの初期化
void InitShot(Shot& shot)
{
	// ショットのグラフィックをメモリにロード
	shot.Graph = LoadGraph("data/Shot.png");

	// 弾が画面上に存在しているか保持する変数に『存在していない』を意味するfalseを代入しておく
	shot.Flag = false;

	// 弾のグラフィックのサイズを得る
	GetGraphSize(shot.Graph, &shot.W, &shot.H);

	//// 弾の左方向フラグに否定のfalseを代入する
	//shot.LeftDir = false;
	//// 弾の上方向フラグに否定のfalseを代入する
	//shot.TopDir = false;
}

// ショットの更新
void UpdateShot(Shot& shot, Player& player)
{
	// 当たり判定の更新
	shot.m_colRect.SetCenter(shot.m_pos.x + kWidth / 2, shot.m_pos.y + kHeight / 2, kWidth, kHeight);

		// 弾が存在している場合のみ次の処理に移る

	// エネミーとの当たり判定
	//if (((shot.X > enemy.X && shot.X < enemy.X + enemy.W) ||
	//	(enemy.X > shot.X && enemy.X < shot.X + shot.W)) &&
	//	((shot.Y > enemy.Y && shot.Y < enemy.Y + enemy.H) ||
	//		(enemy.Y > shot.Y && enemy.Y < shot.Y + shot.H)))
	//{
	//	// 接触している場合は当たった弾の存在を消す
		//shot.Flag = false;
	//}


	// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容がtrue(存在する)の場合のみ行う )
	if (shot.Flag == true)
	{
		// 画面外に出てしまった場合は存在状態を保持している変数にfalse(存在しない)を代入する
		if (shot.X > kScreenWidth || shot.X < 0)
		{
			shot.Flag = false;
		}

		if (player.LeftDir)
		{
			// 弾iを１６ドット横に移動させる
			shot.X -= kSpeed;
		}
		else if (player.TopDir)
		{
			// 弾iを１６ドット上に移動させる
			shot.Y -= kSpeed;
		}
		else
		{
			// 弾iを１６ドット横に移動させる
			shot.X += kSpeed;
		}
	}
}

void DrawShot(Shot& shot, Player& player)
{
	// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容がtrue(存在する)の場合のみ行う )
	if (shot.Flag == true)
	{
		// 画面外に出てしまった場合は存在状態を保持している変数にfalse(存在しない)を代入する
		if (shot.X > kScreenWidth || shot.X < 0)
		{
			shot.Flag = false;
		}

		if (player.isTurn)
		{
			// 画面に弾iを描画する
			DrawTurnGraph(shot.X, shot.Y, shot.Graph, FALSE);

		}
		else if (player.isLookUp)
		{
			// 画面に弾iを描画する
			DrawRotaGraph(shot.X, shot.Y, 1.0f, PI * 1.5f, shot.Graph, FALSE);
		}
		else
		{
			// 画面に弾iを描画する
			DrawGraph(shot.X, shot.Y, shot.Graph, FALSE);
		}
	}
#ifdef _DEBUG
	// 弾の当たり判定デバッグ表示
	shot.m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}