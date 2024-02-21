#include "EnemyBase.h"
#include "Player.h"

#include "DxLib.h"
#include <cassert>

namespace
{
	// �_���[�W���o�t���[����
	constexpr int kDamageFrame = 60;
}

EnemyBase::EnemyBase():
	EGraph(-1),
	m_w(0),
	m_h(0),
	m_hp(0),
	m_atk(0), 
	EnemyAnim(0),
	m_gravity(0),
	m_isTurn(false),	// �G�l�~�[�̌����t���O,�E�������Ă����false��}��
	m_isDeath(false),	// ���S�t���O,����ł��Ȃ���false��}��
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
	// �_���[�W���o�̐i�s
	m_damageFrame--;
	if (m_damageFrame < 0)	m_damageFrame = 0;

	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;
}

void EnemyBase::OnDamage()
{	
	// �_���[�W���o���͍ēx�H���Ȃ�
	if (m_damageFrame > 0)	return;

	m_hp -= m_pPlayer->GetAtk();
	
	if (m_hp <= 0)
	{
		Death();
	}
	// ���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;
}

void EnemyBase::Death()
{  
	m_pPlayer->AddScore(Score);

	m_isDeath = true;		// ���S�t���O���I���ɂ���
	m_isExist = false;
}

void EnemyBase::Start(float x, float y)
{
	m_isExist = true;
}