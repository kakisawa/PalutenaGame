#include "DxLib.h"
#include "Player.h"
#include "Shot.h"
#include "Game.h"

#define PI    3.1415926535897932384626433832795f

namespace
{
	// 弾の移動速度
	constexpr int kSpeed =10;

	// 弾のサイズ
	constexpr int kWidth = 16;
	constexpr int kHeight = 8;
}

Shot::Shot()
{
}

Shot::~Shot()
{
}

void Shot::Init()
{
	// ショットのグラフィックをメモリにロード
	Graph = LoadGraph("data/Shot.png");

	// 弾が画面上に存在しているか保持する変数に『存在していない』を意味するfalseを代入しておく
	Flag = false;

	// 弾のグラフィックのサイズを得る
	GetGraphSize(Graph, &W, &H);

	// 弾の左方向フラグに否定のfalseを代入する
	LeftDir[SHOT] = false;
	// 弾の上方向フラグに否定のfalseを代入する
	TopDir[SHOT] = false;
}

void Shot::Update(Player& player)
{
	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, kWidth, kHeight);

	// 弾が存在している場合のみ次の処理に移る
	if (Flag == true)
	{
		// 画面外に出てしまった場合は存在状態を保持している変数にfalse(存在しない)を代入する
		if (X[SHOT] > kScreenWidth || X[SHOT] < 0)
		{
			Flag = false;
		}

		// 弾の移動処理
		if (player.LeftDir)
		{
			// 弾を左に移動させる
			X[SHOT] -= kSpeed;
		}
		else if (player.TopDir)
		{
			// 弾を上に移動させる
			Y[SHOT] -= kSpeed;
		}
		else
		{
			// 弾を右に移動させる
			X[SHOT] += kSpeed;
		}
	}
}

// エネミーとの当たり判定
//if (((shot.X > enemy.X && shot.X < enemy.X + enemy.W) ||
//	(enemy.X > shot.X && enemy.X < shot.X + shot.W)) &&
//	((shot.Y > enemy.Y && shot.Y < enemy.Y + enemy.H) ||
//		(enemy.Y > shot.Y && enemy.Y < shot.Y + shot.H)))
//{
//	// 接触している場合は当たった弾の存在を消す
	//shot.Flag = false;
//}


void Shot::Draw(Player& player)
{
	// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容がtrue(存在する)の場合のみ行う )
	if (Flag == true)
	{
		// 画面外に出てしまった場合は存在状態を保持している変数にfalse(存在しない)を代入する
		if (X[SHOT] > kScreenWidth || X < 0)
		{
			Flag = false;
		}

		if (player.isTurn)
		{
			// 画面に弾iを描画する
			DrawTurnGraph(X[SHOT], Y[SHOT], Graph, FALSE);

		}
		else if (player.isLookUp)
		{
			// 画面に弾iを描画する
			DrawRotaGraph(X[SHOT], Y[SHOT], 1.0f, PI * 1.5f, Graph, FALSE);
		}
		else
		{
			// 画面に弾iを描画する
			DrawGraph(X[SHOT], Y[SHOT], Graph, FALSE);
		}
	}
#ifdef _DEBUG
	// 弾の当たり判定デバッグ表示
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}