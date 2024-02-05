#include "DxLib.h"
#include "MozueyeEnemy.h"
#include "Player.h"
#include "Game.h"

#include <cassert>

namespace
{
	// エネミーのサイズ
	constexpr float kWidth = 93.6f;
	constexpr int kHeight = 65;

	// エネミーの画像元サイズ
	constexpr int SrcWidth = 46;
	constexpr int SrcHeight = 32;

	// 移動速度
	float kSpeed = 3.0f;
	// プレイヤーHP初期値
	constexpr int kHP = 2;
	// プレイヤーAtk初期値
	constexpr int kAtk = 10;

	// 基本キャラアニメーション		// モーションのフレームごとに作り直す
	constexpr int DefFrame[] = { 0,1,2,3,4 };
	// 基本キャラアニメーションの1コマのフレーム数
	constexpr int DefAnimFrameNum = 10;
	// 基本キャラアニメーション1サイクルのフレーム数
	constexpr int DefFrameCycle = _countof(DefFrame) * DefAnimFrameNum;
}

MozueyeEnemy::MozueyeEnemy()
{
	EGraph= LoadGraph("data/Enemy/Mozueye.png");

	HP = kHP;		// HP
	Atk = kAtk;	// 攻撃力
	Score = 50;	// 倒した際に得られるスコア

	Gravity = 0.0f;				// 敵の初期重力
	isTurn = false;				// 右を向いているのfalseを挿入
	EnemyAnim = 0;				// 敵のアニメーションの初期化
}

MozueyeEnemy::~MozueyeEnemy()
{
	DeleteGraph(EGraph);
}

void MozueyeEnemy::Update()
{
	// ダメージ演出の進行
	m_damageFrame--;
	if (m_damageFrame < 0)	m_damageFrame = 0;

	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2,
		kWidth, kHeight);

	// 移動量を持つようにする
	Vec2 move{ 0.0f,0.0f };
	// ベクトルの正規化
	move.normalize();
	// ベクトルの長さをkSpeedにする
	move *= kSpeed;
	m_pos += move;

	//敵移動
	if (isTurn == false)
	{
		if (kSpeed <= 40.0f)
		{
			kSpeed = 3.0f;
		}

		kSpeed += 5.0f;
		m_pos.x += kSpeed;
	}
	else if (isTurn == true)
	{
		m_pos.x -= kSpeed;
	}

	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	if (m_pos.x > kScreenWidth - kWidth)
	{
		m_pos.x = kScreenWidth - kWidth;
		isTurn = true;
	}
	else if (m_pos.x < 0)
	{
		m_pos.x = 0;
		isTurn = false;
	}

	// アニメーションフレーム
	EnemyAnim++;
	if (EnemyAnim >= DefFrameCycle)
	{
		EnemyAnim = 0;
	}
}

void MozueyeEnemy::Draw()
{
	int EnemyFrame = EnemyAnim / DefAnimFrameNum;
	int srcX = DefFrame[EnemyFrame] * SrcWidth;

	// 存在しない敵は描画しない
	if (!m_isExist) return;
	// グラフィックが設定されていなければ止まる
	assert(EGraph != -1);

	if (m_damageFrame % 4 >= 2) return;

	if (isTurn == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 29,
			SrcWidth, SrcHeight,
			EGraph, true);
	}
	else if (isTurn == true)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 0,
			SrcWidth, SrcHeight,
			EGraph, true);
	}
#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void MozueyeEnemy::Start(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;

	m_isExist = true;
}