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
	//// ジャンプ移動量
	//constexpr float JumpPower = 20.0f;
}


Player::Player():
	FallPowor(0.0f),			// 落下速度
	JumpPower(0.0f),			// ジャンプ移動量
	m_handle(-1),
	m_pos(kScreenWidth / 2, 400),
	Graph(0),
	W(0),
	H(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
	// プレイヤーの画像読み込み&座標の初期化
	Graph = LoadGraph("data/Fairy.png");

	// プレイヤーの縦横幅
	GetGraphSize(Graph, &W, &H);

	// グラフィック反転フラグ(反転していないのfalseを挿入)
	isTurn = false;
	// プレイヤーが上を向いているかのフラグ(向いていないのfalseを挿入)
	isLookUp = false;
	// プレイヤーがしゃがんでいるかのフラグ(しゃがんでいないのfalseを挿入)
	isSquat = false;
	// ジャンプ中かどうかのフラグフラグ(ジャンプしていないのfalseを挿入)
	isPushFlag = false;
	// 移動中かどうかのフラグ(移動していないのfalseを挿入)
	isMove = false;
	// ショットボタンが前のフレームで押されたかどうかを保存する変数にfalse(押されていない)を代入
	isPrevshotFlag = false;

	// 弾の左方向フラグ(左を向いていないのfalseを挿入)
	LeftDir = false;
	// 弾の上方向フラグ(上を向いていないのfalseを挿入)
	TopDir = false;
}

void Player::Update(Shot shotArray[], int shotArraySize)
{
	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	// 矢印キーを押していたらプレイヤーを移動させる
	// 上向き
	if (Key && CheckHitKey(KEY_INPUT_UP) == 1)
	{
		isMove = true;
		isLookUp = true;
		isTurn = false;
		isSquat = false;
	}
	// 屈む
	if (Key && CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		isMove = true;
		isTurn = false;
		isLookUp = false;
		isSquat = true;
	}
	// 左移動
	if (Key && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		m_pos.x -= kSpeed;
		isMove = true;
		isLookUp = false;
		isTurn = true;
		isSquat = false;
	}
	// 右移動
	if (Key && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		m_pos.x += kSpeed;
		isMove = true;
		isLookUp = false;
		isTurn = false;
		isSquat = false;
	}

	// ジャンプボタンを押していて、地面についていたらジャンプ
	if ((Key & PAD_INPUT_A) && m_pos.y == 400)
	{
		JumpPower = 8.0f;

		isPushFlag = true;
		isMove = true;
	}

	// 落下処理
	m_pos.y -= JumpPower;

	// 落下加速度を加える
	JumpPower -= 0.5f;

	//// ジャンプ
	//if (Key && CheckHitKey(KEY_INPUT_A) == 1) {
	//	m_pos.y -= player.JumpPower;
	//	player.isPushFlag = true;
	//	isMove = true;
	//}
	//// 落下加速度を加える
	//player.FallPowor += 0.5f;
	//// 落下処理
	//m_pos.y += player.FallPowor;

	// もし地面についていたら止まる
	if (m_pos.y > Ground)
	{
		m_pos.y = Ground;

		if (m_pos.y = Ground)
		{
			FallPowor = 0;

			isPushFlag = false;
		}
	}

	// ベクトルの正規化
	move.normalize();
	// ベクトルの長さをkSpeedにする
	move *= kSpeed;
	// 座標とベクトルの足し算
	m_pos += move;

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, kWidth, kHeight);


	// 弾の発射処理
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// 前フレームでショットボタンを押したかが保存されている変数がfalseだったら弾を発射
		if (isPrevshotFlag == false)
		{
			// 画面上にでていない弾があるか、弾の数だけ繰り返して調べる
			for (int i = 0; i < shotArraySize; i++)
			{
				// 弾iが画面上にでていない場合はその弾を画面に出す
				if (shotArray[i].Flag == false)
				{
					// 弾iの位置をセット、位置はプレイヤーの中心にする
					if (isTurn)
					{
						shotArray[i].X = m_pos.x;
						LeftDir = true;
						TopDir = false;

						/*shotArray[i].LeftDir = true;
						shotArray[i].TopDir = false;*/
					}
					else if (isLookUp)
					{
						shotArray[i].X = m_pos.x + kWidth / 2;
						LeftDir = false;
						TopDir = true;

						/*shotArray[i].LeftDir = false;
						shotArray[i].TopDir = true;*/
					}
					else
					{
						shotArray[i].X = (kWidth - shotArray[i].W) / 2 + m_pos.x;
						LeftDir = false;
						TopDir = false;

						/*shotArray[i].LeftDir = false;
						shotArray[i].TopDir = false;*/
					}

					shotArray[i].Y = (kHeight - shotArray[i].H) / 2 + m_pos.y;

					// 弾iは現時点を持って存在するので、存在状態を保持する変数にtrueを代入する
					shotArray[i].Flag = true;

					// 一つ弾を出したので弾を出すループから抜けます
					break;
				}
			}
		}
		// 前フレームでショットボタンを押されていたかを保存する変数にtrue(おされていた)を代入
		isPrevshotFlag = true;
	}
	else
	{
		// ショットボタンが押されていなかった場合は
		// 前フレームでショットボタンが押されていたかを保存する変数にfalse(おされていない)を代入
		isPrevshotFlag = false;
	}

	// x座標...プレイヤーが左右画面外に出ると、反対側からプレイヤーが出てくる
	// y座標...プレイヤーが画面外に出ようとすると止まる
	if (m_pos.x < 0 - W)
	{
		m_pos.x = kScreenWidth - W;
	}
	if (m_pos.x > kScreenWidth)
	{
		m_pos.x = 0;
	}
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
	}
	if (m_pos.y > Ground)
	{
		m_pos.y = Ground;
	}
}

void Player::Draw()
{
	if (isTurn)
	{
		// プレイヤー反転描画(左向き)
		DrawTurnGraph(m_pos.x, m_pos.y, Graph, false);
	}
	else
	{
		// プレイヤー描画(右向き)
		DrawGraph(m_pos.x, m_pos.y, Graph, false);
	}

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}
