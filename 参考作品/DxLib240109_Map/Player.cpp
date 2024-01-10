#include "Player.h"
#include "Map.h"
#include "DxLib.h"

// �v���b�g�t�H�[�}�[�^�C�v�̃Q�[���̓v���C���[�̉����S�c������pos�ɂ����������₷��

namespace
{
	constexpr int kWidth = 24;
	constexpr int kHeight = 24;

	// �d��
	constexpr float kGravity = 0.5f;
	// �W�����v��
	constexpr float kJumpAcc = -8.0f;
}

Player::Player() :
	m_isJump(false),
	m_x(320.0f),
	m_y(240.0f),
	m_moveX(0.0f),
	m_moveY(0.0f)
{
}

Player::~Player()
{
}

void Player::Update()
{
	// �㉺���E�L�[�Ńv���C���[�ړ�
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (m_isJump)
	{
		// �󒆂ɂ���ꍇ�̏���

		// ���t���[���������ɉ�������(�d�͂̉e�����󂯂�)
		m_moveY += kGravity;

		// �n�ʂɒ��n���鏈��
		if (m_pMap->IsColPlayer())
		{
			m_y -= m_moveY;
			m_moveY = 0.0f;
			m_isJump = false;
		}
	}
	else
	{
		// �n�ʂɗ����Ă���ꍇ�̏���
		m_moveX = 0.0f;
		if (pad & PAD_INPUT_RIGHT)
		{
			m_moveX = 4.0f;
		}
		if (pad & PAD_INPUT_LEFT)
		{
			m_moveX = -4.0f;
		}
		// �W�����v
		if (pad & PAD_INPUT_1)
		{
			m_moveY = kJumpAcc;
			m_isJump = true;
		}
		// �ڒn���Ă��Ȃ�
		if (!m_pMap->IsColPlayer())
		{
			m_isJump = true;
		}
	}

	m_x += m_moveX;
	m_y += m_moveY;
}

void Player::Draw()
{
	unsigned int color = 0xff0000;
	if (m_pMap->IsColPlayer())	color = 0xffff00;

	// �������W��������W�ɕϊ�
	int x = static_cast<int>(m_x - kWidth / 2);
	int y = static_cast<int>(m_y - kHeight);

	// �X�N���[���ʂ𔽉f
	x -= m_pMap->GetScrollX();
	y -= m_pMap->GetScrollY();
	DrawBox(x, y, x + kWidth, y + kHeight, color, true);


}

float Player::GetLeft()
{
	return m_x - kWidth / 2;
}
float Player::GetRight()
{
	return m_x + kWidth / 2;
}
float Player::GetTop()
{
	return m_y - kHeight;
}
float Player::GetBottom()
{
	return m_y + kHeight;
}