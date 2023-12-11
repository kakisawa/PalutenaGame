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
	// ジャンプ距離
	constexpr float kJump = 13.0f;
}

Player::Player():
	HP(100),						// プレイヤーの初期HP
	m_pos(kScreenWidth / 2, 100),	// プレイヤーの初期位置
	m_dir(kDirRight),				// プレイヤーの初期方向
	JumpPower(0.0f),				// プレイヤーの初期ジャンプ
	Gravity(0.0f)					// プレイヤーの初期重力
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
	m_pos.y += Gravity;
	// 落下加速度を加える
	Gravity += 0.3f;

	// もし地面についていたら止まる
	if (m_pos.y > Ground)
	{
		m_pos.y = Ground;

		if (m_pos.y == Ground)
		{
			Gravity = 0;
			JumpPower = 0;

			isJumpFlag = false;
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
	if ((Key & PAD_INPUT_A) && m_pos.y == Ground)
	{
		// ジャンプ加速度
		for (int i = 0; i < kJump; i++) {
			JumpPower += 0.5f;
		}
		isJumpFlag = true;
		isMove = true;
	}

	// ジャンプ処理
	m_pos.y -= JumpPower;


	// ベクトルの正規化
	move.normalize();

	// ベクトルの長さをkSpeedにする
	move *= kSpeed;

	// 座標とベクトルの足し算
	m_pos += move;

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, kWidth, kHeight);

	// x座標...プレイヤーが左右画面外に出ると、反対側からプレイヤーが出てくる
	if (m_pos.x > kScreenWidth - kWidth)
	{
		m_pos.x = 0;
	}
	if (m_pos.x < 0)
	{
		m_pos.x = kScreenWidth - kWidth;
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

	// プレイヤーの現在座標表示
	DrawFormatString(0,0,GetColor( 255 , 255 , 255 ),
		"現在座標:(%.2f,%.2f)",m_pos.x, m_pos.y);
	// プレイヤーの現在体力表示
	DrawFormatString(0, 19, GetColor(255, 255, 255),
		"HP:(%d)", HP);

#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}

// 地面処理まで終わってるはず
// 1,プレイヤーのアニメーション
// 4,単押しでジャンプ(優先度低)
// 〇5,当たり判定
// HP管理・表示

// 背景表示
// シーン遷移(タイトル、ゲーム画面)
// スクロール

// ショット

