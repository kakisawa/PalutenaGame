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
	m_graph(-1),
	m_expGraph(-1),
	m_w(0),
	m_h(0),
	m_hp(0),
	m_atk(0), 
	m_score(0),
	m_enemyAnim(0),
	m_gravity(0),
	m_enemyDeathAnim(0),
	m_isScore(false),
	m_isTurn(false),		// エネミーの向きフラグ,右を向いているのfalseを挿入
	m_isDeath(false),		// 死亡フラグ,死んでいないのfalseを挿入
	m_isExist(false),
	m_isDeathAnim(false),
	m_pPlayer(nullptr),
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
	if (m_damageFrame < 0) 
	{
		m_damageFrame = 0;
	}

	// 存在しない敵の処理はしない
	if (!m_isExist) return;
}

void EnemyBase::OnDamage()
{	
	// ダメージ演出中は再度食らわない
	if (m_damageFrame > 0)	return;

	m_hp -= m_pPlayer->GetAtk();
	
	if (m_hp <= 0)
	{
		Death();
	}
	// 演出フレーム数を設定する
	m_damageFrame = kDamageFrame;
}

void EnemyBase::Death()
{  
	m_pPlayer->AddScore(m_score);


	m_isDeath = true;		// 死亡フラグをオンにする
	m_isDeathAnim = true;
	m_isExist = false;
}