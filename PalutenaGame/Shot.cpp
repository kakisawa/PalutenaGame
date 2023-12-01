#include "DxLib.h"
#include "Shot.h"
#include "Game.h"

// ショットの初期化
void InitShot(Shot& shot)
{
	// ショットのグラフィックをメモリにロード
	shot.Graph = LoadGraph("data/Shot.png");

	// 弾が画面上に存在しているか保持する変数に『存在していない』を意味するfalseを代入しておく
	shot.Flag = false;

	// 弾のグラフィックのサイズを得る
	GetGraphSize(shot.Graph, &shot.W, &shot.H);
}

// ショットの更新
void UpdateShot(Shot& shot)
{
	// 弾の当たり判定
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

}

void DrawShot(Shot& shot)
{
	// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容がtrue(存在する)の場合のみ行う )
	if (shot.Flag == true)
	{
		// 弾iを１６ドット横に移動させる
		shot.X += 16;

		// 画面外に出てしまった場合は存在状態を保持している変数にfalse(存在しない)を代入する
		if (shot.X > kScreenWidth || shot.X < 0)
		{
			shot.Flag = false;
		}
		// 画面に弾iを描画する
		DrawGraph(shot.X, shot.Y, shot.Graph, FALSE);
	}
}