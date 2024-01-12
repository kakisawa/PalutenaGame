#include "DxLib.h"
#include "Player.h"
#include "Map.h"

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

		m_x += m_moveX;
		// �����瓖�����������`�F�b�N����
		Rect chipRect;	// ���������}�b�v�`�b�v�̋�`
		if (m_pMap->IsCol(getRect(), chipRect))
		{
			// ������Ԃ������ꍇ�̏���
			m_x -= m_moveX;

			// ���E�ǂ��炩�炠�����������f�o�b�O�\��
			if (m_moveX > 0.0f)	// �v���C���[���E�����Ɉړ����Ă���
			{
				//printfDx("�v���C���[�̉E�����}�b�v�ɂԂ�����\n");
				m_x = chipRect.left - kWidth / 2 - 1;	// �}�b�v�`�b�v�̍������x�ɂԂ���Ȃ��ʒu�ɕ␳
			}
			else if (m_moveX < 0.0f)
			{
				//printfDx("�v���C���[�̍������}�b�v�ɂԂ�����\n");
				m_x = chipRect.right + kWidth / 2 + 1;	// �}�b�v�`�b�v�̉E�����x�ɂԂ���Ȃ��ʒu�ɕ␳
			}
		}
		m_y += m_moveY;
		// �����炠�����������`�F�b�N����
		if (m_pMap->IsCol(getRect(),chipRect))
		{
			if (m_moveY > 0.0f)	// �v���C���[���������Ɉړ����Ă���
			{
				// ���n
				m_y = chipRect.top - 1;
				m_moveY = 0.0f;
				m_isJump = false;
			}
			else if (m_moveY < 0.0f)	// �v���C���[��������Ɉړ����Ă���
			{
				m_y = chipRect.bottom+kHeight+1;	// �߂荞�܂Ȃ��ʒu�ɖ߂�
				m_moveY *= -1.0f;	// ������ւ̉����������ɕϊ�
			}
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

		m_x += m_moveX;
		// �����瓖�����������`�F�b�N����
		Rect chipRect;	// ���������}�b�v�`�b�v�̋�`
		if (m_pMap->IsCol(getRect(), chipRect))
		{
			// ������Ԃ������ꍇ�̏���
			m_x -= m_moveX;

			// ���E�ǂ��炩�炠�����������f�o�b�O�\��
			if (m_moveX > 0.0f)	// �v���C���[���E�����Ɉړ����Ă���
			{
				//printfDx("�v���C���[�̉E�����}�b�v�ɂԂ�����\n");
				m_x = chipRect.left - kWidth / 2-1;	// �}�b�v�`�b�v�̍������x�ɂԂ���Ȃ��ʒu�ɕ␳
			}
			else if (m_moveX < 0.0f)
			{
				//printfDx("�v���C���[�̍������}�b�v�ɂԂ�����\n");
				m_x = chipRect.right + kWidth / 2 + 1;	// �}�b�v�`�b�v�̉E�����x�ɂԂ���Ȃ��ʒu�ɕ␳
			}
		}

		m_y += m_moveY;
		// �c���瓖�����������`�F�b�N����
		if (m_pMap->IsCol(getRect(),chipRect))
		{
			if (m_moveY > 0.0f)	// �v���C���[���������Ɉړ����Ă���
			{
				// �n�ʂɗ����Ă��鉽�����Ȃ�
				m_y = chipRect.top - 1;
			}
			else if (m_moveY < 0.0f)	// �v���C���[��������Ɉړ����Ă���
			{
				m_y = chipRect.bottom + kHeight + 1;	// �߂荞�܂Ȃ��ʒu�ɖ߂�
				m_moveY *= -1.0f;	// ������ւ̉����������ɕϊ�

				//printfDx("�v���C���[�̏㑤���}�b�v�ɂԂ�����\n");
			}
		}
		else
		{
			// �n�ʂɂ���Ԃ����Ă��Ȃ�
			m_isJump = true;
		}

		// �ڒn���Ă��Ȃ�
		if (!m_pMap->IsCol(getRect(),chipRect))
		{
			m_isJump = true;
		}
	}
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
	return m_y;
}

Rect Player::getRect()
{
	Rect rect;
	rect.top = GetTop();
	rect.bottom = GetBottom();
	rect.left = GetLeft();
	rect.right = GetRight();

	return rect;
}
