#include "PumpkinEnemy.h"
#include "DxLib.h"
#include "Game.h"
#include "Player.h"

#include <cassert>

namespace
{
	// エネミーのサイズ
	constexpr int kWidth = 16;
	constexpr int kHeight = 22;

	// 移動速度
	constexpr float kSpeed = 1.0f;
	// 基本キャラアニメーション		// モーションのフレームごとに作り直す
	constexpr int DefFrame[] = { 0,1,2,3,4,5,6,7 };
	// 基本キャラアニメーションの1コマのフレーム数
	constexpr int DefAnimFrameNum = 8;
	// 基本キャラアニメーション1サイクルのフレーム数
	constexpr int DefFrameCycle = _countof(DefFrame) * DefAnimFrameNum;
}

PumpkinEnemy::PumpkinEnemy()
{

	EGraph= LoadGraph("data/Enemy/Pumpkin.png");

	HP = 1;		// HP
	Atk = 100;	// 攻撃力
	Score = 10;	// 倒した際に得られるスコア

	Gravity = 0.0f;				// 敵の初期重力
	isTurn = false;				// 右を向いているのfalseを挿入
	EnemyAnim = 0;				// 敵のアニメーションの初期化
}

PumpkinEnemy::~PumpkinEnemy()
{
	DeleteGraph(EGraph);
}

void PumpkinEnemy::Update()
{
	m_pos += m_vec;

	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, kWidth, kHeight);

	if (m_pos.x<0 || m_pos.x > kScreenWidth + kWidth / 2)
	{
		m_isExist = false;
	}

	const Vec2 target = m_pPlayer->OutPos();

	// 敵の初期位置からターゲット位置に向かうベクトルを生成する
	// 始点から終点に向かうベクトルを求める場合、終点の座標-始点の座標で求める
	Vec2 toTarget = target - m_pos;

	// ベクトルの長さをkSpeedにしてやる

	// ベクトルの正規化　長さを1にする
	toTarget.normalize();
	// kSpeedでかける
	m_vec = toTarget * kSpeed;

	// アニメーションフレーム
	EnemyAnim++;
	if (EnemyAnim >= DefFrameCycle)
	{
		EnemyAnim = 0;
	}
}

void PumpkinEnemy::Draw()
{
	int EnemyFrame = EnemyAnim / DefAnimFrameNum;
	int srcX = DefFrame[EnemyFrame] * kWidth;

	// 存在しない敵は描画しない
	if (!m_isExist) return;
	// グラフィックが設定されていなければ止まる
	assert(EGraph != -1);

	if (m_damageFrame % 4 >= 2) return;

	if (isTurn == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX-1, 25,
			kWidth, kHeight,
			EGraph, true);
	}
	else if (isTurn == true)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX - 1, 0,
			kWidth, kHeight,
			EGraph, true);
	}
#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void PumpkinEnemy::Start(float x, float y)
{
	m_isExist = true;

	m_pos.x = x;
	m_pos.y = y;
}
