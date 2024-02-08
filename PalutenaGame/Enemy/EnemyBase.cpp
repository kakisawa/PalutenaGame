#include "EnemyBase.h"
#include "Player.h"

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
	m_isExist(false), 
	m_damageFrame(0)
{
}

void EnemyBase::Init(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}

void EnemyBase::Update()
{
	// ダメージ演出の進行
	m_damageFrame--;
	if (m_damageFrame < 0)	m_damageFrame = 0;

	// 存在しない敵の処理はしない
	if (!m_isExist) return;
}

void EnemyBase::OnDamage()
{	
	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0)	return;

	HP -= m_pPlayer->GetAtk();
	
	if (HP <= 0)
	{
		Death();
	}
	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;
}

void EnemyBase::Death()
{  
	m_pPlayer->AddScore(Score);

	isDeath = true;		// 死亡フラグをオンにする
	m_isExist = false;
}

void EnemyBase::Start(float x, float y)
{
	m_isExist = true;
}