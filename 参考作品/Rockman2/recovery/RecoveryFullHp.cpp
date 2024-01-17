#include "RecoveryFullHp.h"
#include "EnemyBase.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �A�C�e���̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
}

RecoveryFullHp::RecoveryFullHp()
{
	m_handle = LoadGraph("data/image/Recovery/fullHp.png");
}

RecoveryFullHp::~RecoveryFullHp()
{
}

void RecoveryFullHp::Init()
{
}

void RecoveryFullHp::Update()
{
	// ���݂��Ȃ��A�C�e���̏����͂��Ȃ�
	if (!m_isExist) return;

	// �����蔻��
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
}

void RecoveryFullHp::Draw()
{
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 1.0, 0.0, m_handle, true, false);

#ifdef _DEBUG
	// �A�C�e���̓����蔻��f�o�b�O�\��
	m_colRect.Draw(0x00ff00, false);
#endif
}

void RecoveryFullHp::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	m_pos = pos;
}
