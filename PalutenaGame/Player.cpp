#include "DxLib.h"
#include "Player.h"
#include "Shot.h"
#include "Game.h"
#include "KeyProcess.h"

#include <cmath>

namespace 
{
	// キャラクターのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// 移動速度
	constexpr float kSpeed = 3.0f;
	// ジャンプ移動量
	constexpr float JumpPowor = 20.0f;
}

// プレイヤーの初期化
void InitPlayer(Player& player)
{
	// プレイヤーの画像読み込み&座標の初期化
	player.Graph = LoadGraph("data/Fairy.png");
	
	player.m_pos.x = kScreenWidth / 2;
	player.m_pos.y = 400;

	// プレイヤーの縦横幅
	GetGraphSize(player.Graph, &player.W, &player.H);
	
	// 落下速度
	player.FallPowor = 0.0f;

	// グラフィック反転フラグ(反転していないのfalseを挿入)
	player.isTurn = false;
	// プレイヤーが上を向いているかのフラグ(向いていないfalseを挿入)
	player.isLookUp = false;
	// ジャンプ中かどうかのフラグフラグ(押されていないのfalseを挿入)
	player.isPushFlag = false;
	// 移動中かどうかのフラグ(移動していないのfalseを挿入)
	player.isMove = false;
	// ショットボタンが前のフレームで押されたかどうかを保存する変数にfalse(押されていない)を代入
	player.isPrevshotFlag = false;

	// 弾の左方向フラグ(左を向いていないのfalseを挿入)
	player.LeftDir = false;
	// 弾の上方向フラグ(上を向いていないのfalseを挿入)
	player.TopDir = false;
}



// プレイヤーの更新
void UpdatePlayer(Player& player, Shot shotArray[], int shotArraySize)
{
	// パッドの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// 移動中かどうか
	bool isMove = false;
	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	// 矢印キーを押していたらプレイヤーを移動させる
	// 上向き
	if (pad && CheckHitKey(KEY_INPUT_UP) == 1)
	{
		//pad && CheckHitKey
		player.isLookUp = true;
		player.isMove = true;
		player.isTurn = false;
	}
	// 屈む
	if (pad && CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		player.isMove = true;
		player.isTurn = false;
	}
	// 左移動
	if (pad && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		player.m_pos.x -= kSpeed;
		player.isMove = true;
		player.isLookUp = false;
		player.isTurn = true;
	}
	// 右移動
	if (pad && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		player.m_pos.x += kSpeed;
		player.isMove = true;
		player.isLookUp = false;
		player.isTurn = false;
	}

	// ジャンプ
	if (pad && CheckHitKey(KEY_INPUT_A) == 1) {
		player.m_pos.y -= JumpPowor;
		player.isPushFlag = true;
		player.isMove = true;
	}

	// 落下加速度を加える
	player.FallPowor += 0.5f;
	// 落下処理
	player.m_pos.y += player.FallPowor;

	// もし地面についていたら止まる
	if (player.m_pos.y > Ground)
	{
		player.m_pos.y = Ground;

		if (player.m_pos.y = Ground)
		{
			player.FallPowor = 0;

			player.isPushFlag = false;
		}
	}

	// ベクトルの正規化
	move.normalize();
	// ベクトルの長さをkSpeedにする
	move *= kSpeed;
	// 座標とベクトルの足し算
	player.m_pos += move;
	
	// 当たり判定の更新
	player.m_colRect.SetCenter(player.m_pos.x+kWidth/2, player.m_pos.y+kHeight/2, kWidth, kHeight);


	// 弾の発射処理
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// 前フレームでショットボタンを押したかが保存されている変数がfalseだったら弾を発射
		if (player.isPrevshotFlag == false)
		{
			// 画面上にでていない弾があるか、弾の数だけ繰り返して調べる
			for (int i = 0; i < shotArraySize; i++)
			{
				// 弾iが画面上にでていない場合はその弾を画面に出す
				if (shotArray[i].Flag == false)
				{
					// 弾iの位置をセット、位置はプレイヤーの中心にする
					if (player.isTurn)
					{
						shotArray[i].X = player.m_pos.x;
						player.LeftDir = true;
						player.TopDir = false;
					}
					else if (player.isLookUp)
					{
						shotArray[i].X = player.m_pos.x + kWidth / 2;
						player.LeftDir = false;
						player.TopDir = true;

					}
					else
					{
						shotArray[i].X = (kWidth - shotArray[i].W) / 2 + player.m_pos.x;
						player.LeftDir = false;
						player.TopDir = false;

					}

					shotArray[i].Y = (kHeight - shotArray[i].H) / 2 + player.m_pos.y;

					// 弾iは現時点を持って存在するので、存在状態を保持する変数にtrueを代入する
					shotArray[i].Flag = true;

					// 一つ弾を出したので弾を出すループから抜けます
					break;
				}
			}
		}
		// 前フレームでショットボタンを押されていたかを保存する変数にtrue(おされていた)を代入
		player.isPrevshotFlag = true;
	}
	else
	{
		// ショットボタンが押されていなかった場合は
		// 前フレームでショットボタンが押されていたかを保存する変数にfalse(おされていない)を代入
		player.isPrevshotFlag = false;
	}

	// x座標...プレイヤーが左右画面外に出ると、反対側からプレイヤーが出てくる
	// y座標...プレイヤーが画面外に出ようとすると止まる
	if (player.m_pos.x < 0 - player.W)
	{
		player.m_pos.x = kScreenWidth - player.W;
	}
	if (player.m_pos.x > kScreenWidth)
	{
		player.m_pos.x = 0;
	}
	if (player.m_pos.y < 0)
	{
		player.m_pos.y = 0;
	}
	if (player.m_pos.y > Ground)
	{
		player.m_pos.y = Ground;
	}
}



// プレイヤーの描画
void DrawPlayer(Player& player)
{
	if (player.isTurn)
	{
		// プレイヤー反転描画(左向き)
		DrawTurnGraph(player.m_pos.x, player.m_pos.y, player.Graph, false);
	}
	else
	{
		// プレイヤー描画(右向き)
		DrawGraph(player.m_pos.x, player.m_pos.y, player.Graph, false);
	}

#ifdef _DEBUG
	// 当たり判定の表示
	player.m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}
