#include "Enemy.h"
#include "Map.h"
#include "DxLib.h"

// �v���b�g�t�H�[�}�[�^�C�v�̃Q�[���̓v���C���[�̉����S�c������pos�ɂ����������₷��

namespace
{
	constexpr int kWidth = 24;
	constexpr int kHeight = 24;
}

Enemy::Enemy() :
	m_x(400.0f),
	m_y(300.0f)
{
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	// �������W��������W�ɕϊ�
	int x = static_cast<int>(m_x - kWidth / 2);
	int y = static_cast<int>(m_y - kHeight);

	// �X�N���[���ʂ𔽉f
	x -= m_pMap->GetScrollX();
	y -= m_pMap->GetScrollY();
	DrawBox(x, y, x + kWidth, y + kHeight, 0x0000ff, true);
}
