#include "DxLib.h"
#include "Player.h"

#include "Game.h"

namespace
{
	// キャラクターのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// 移動速度
	constexpr float kSpeed = 3.0f;
}


Player::Player():
	m_pos(kScreenWidth / 2, 100),
	m_dir(kDirRight),
	JumpPower(8.0f),
	Gravity(8.0f)
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
}

void Player::Update()
{
	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };

	// 重力処理
	m_pos.y += JumpPower;

	// もし地面についていたら止まる
	if (m_pos.y > Ground)
	{
		m_pos.y = Ground;

		if (m_pos.y == Ground)
		{
			FallPowor = 0;

			isPushFlag = false;
		}
	}


	// 矢印キーを押していたらプレイヤーを移動させる
	// 上向き
	if (Key && CheckHitKey(KEY_INPUT_UP) == 1)
	{
		isMove = true;
		isTurn = false;
		m_dir = kDirUp;
	}
	// 屈む
	if (Key && CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		isMove = true;
		isTurn = false;
		m_dir = kDirDown;
	}
	// 左移動
	if (Key && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		m_pos.x -= kSpeed;
		isMove = true;
		isTurn = true;
		m_dir = kDirLeft;
	}
	// 右移動
	if (Key && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		m_pos.x += kSpeed;
		isMove = true;
		isTurn = false;
		m_dir = kDirRight;
	}

	// ジャンプボタンを押していて、地面についていたらジャンプ
	if ((Key & PAD_INPUT_A) && m_pos.y == 400)
	{
		m_pos.y -= JumpPower;
		isPushFlag = true;
		isMove = true;
	}

	// ベクトルの正規化
	move.normalize();

	// ベクトルの長さをkSpeedにする
	move *= kSpeed;

	// 座標とベクトルの足し算
	m_pos += move;
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
}



// 地面処理まで終わってるはず
// 1,プレイヤーのアニメーション(左右ジャンプ)
// 2,重力加速度
// 3,ジャンプ量を大きく
// 4,単押しでジャンプ(優先度低)
// 5,当たり判定
// HP管理・表示

// 背景表示
// シーン遷移(タイトル、ゲーム画面)
// スクロール

// ショット

