#include "EnemyBase.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	// ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;
}

EnemyBase::EnemyBase():
	EGraph(-1),
	W(0),
	H(0),
	HP(0),
	Atk(0), 
	EnemyAnim(0),
	Gravity(0),
	isTurn(false),	// エネミーの向きフラグ,右を向いているのfalseを挿入
	isDeath(false),	// 死亡フラグ,死んでいないのfalseを挿入
	m_isExist(true)
{
}

void EnemyBase::Update()
{
	// 存在しない敵の処理はしない
	if (!m_isExist) return;
}

void EnemyBase::Draw()
{
	// 存在しない敵は描画しない
	if (!m_isExist) return;

	// グラフィックが設定されていなければ止まる
	assert(EGraph != -1);

	if (isTurn == false)
	{
		DrawGraph(m_pos.x, m_pos.y, EGraph, true);
	}
	else if (isTurn == true)
	{
		DrawTurnGraph(m_pos.x, m_pos.y, EGraph, true);
	}
#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void EnemyBase::OnDamage()
{
	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0)
	{
		return;
	}
	// HP -= m_pPlayer->GetPlayerAtk();

	HP -= 1;
	

	if (HP <= 0)
	{
		Death();
	}

	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;
}

void EnemyBase::Death()
{
	isDeath = true;		// 死亡フラグをオンにする
	m_isExist = false;
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(EGraph, &width, &height);
	// 中心座標を指定して当たり判定のRectを生成する
	m_colRect.SetLT(m_pos.x, m_pos.y, width, height);
}
