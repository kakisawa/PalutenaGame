#include "PumpkinEnemy.h"
#include "DxLib.h"
#include "Game.h"
#include "Player.h"

namespace
{
	// エネミーのサイズ
	constexpr int kWidth = 16;
	constexpr int kHeight = 22;

	// 移動速度
	constexpr float kSpeed = 3.0f;
}

PumpkinEnemy::PumpkinEnemy()
{

	EGraph= LoadGraph("data/Fairy3.png");

	HP = 1;		// HP
	Atk = 10;	// 攻撃力
	Item;		// ドロップアイテム
	
	Gravity = 0.0f;				// 敵の初期重力
	isTurn = false;				// 右を向いているのfalseを挿入

	m_pos.x = kScreenWidth * 0.5;
	m_pos.y = Ground-kHeight*0.5;
}

PumpkinEnemy::~PumpkinEnemy()
{
	DeleteGraph(EGraph);
}

void PumpkinEnemy::Update()
{
	// EnemyBaseの継承がうまくできてない？
	// 一時的に力技で呼び出し中
	EnemyBase::Update();

	m_pos += m_vec;

	//当たり判定の更新
	UpdateCollision();

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
}