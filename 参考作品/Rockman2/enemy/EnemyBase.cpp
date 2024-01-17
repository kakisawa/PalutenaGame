#include "EnemyBase.h"
#include "RecoveryBase.h"
#include "RecoverySmallHp.h"
#include "ShotBase.h"
#include "SceneMain.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

EnemyBase::EnemyBase():
	m_pMain(nullptr),
	m_pRecovery(nullptr),
	m_handle(-1),
	m_isExist(false),
	m_hp(0),
	m_pos(0, 0)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
	m_hp = 0;
}

void EnemyBase::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// �O���t�B�b�N���ݒ肳��Ă��Ȃ���Ύ~�܂�
	assert(m_handle != -1);
}

void EnemyBase::Draw()
{
}

void EnemyBase::Start()
{
	m_isExist = false;
}

void EnemyBase::OnDamage()
{
	// ���݂�HP�����炷
	m_hp--;

	// HP��0�ȉ��ɂȂ����瑶�݂�����
	if (m_hp <= 0)
	{
		m_isExist = false;
	}
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	// �����蔻��𐶐�
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(width), static_cast<float>(height));
}
