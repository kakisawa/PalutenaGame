#include "ShotMagicWand.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include <cassert>

namespace
{
	// �萔�̒�`

	constexpr float kSpeed = 8.0f;	// �e�̈ړ����x

	// �V���b�g�̑傫��
	constexpr float kWidth = 8.0f;
	constexpr float kHeight = 8.0f;

	// �o���Ă����ߋ��̈ʒu���̐�
	constexpr int kPosLogNum = 8;
}

ShotMagicWand::ShotMagicWand()
{
	m_posLog.resize(kPosLogNum);
}

ShotMagicWand::~ShotMagicWand()
{
}

void ShotMagicWand::Init()
{
}

void ShotMagicWand::Update()
{
	if (!m_isExist) return;

	// �ʒu�̃��O�����炷
//	for (int i = 1; i < m_posLog.size(); i++)
	for (int i = m_posLog.size() - 1; i >= 1; i--)
	{
		m_posLog[i] = m_posLog[i - 1];
	}
	// 1�t���[���O�̈ʒu��������
	m_posLog[0] = m_pos;

	m_pos += m_vec;
	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);

	// ��ʊO�ɏo������
	// �ߋ��̕\���ʒu���܂߂Ă��ׂĉ�ʊO�ɏo����I��
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ����t���O

	if (m_pos.x < 0.0f - kWidth / 2)	isOut = true;
	if (m_pos.x > Game::kScreenWidth + kWidth / 2)	isOut = true;
	if (m_pos.y < 0.0f - kHeight / 2)	isOut = true;
	if (m_pos.y > Game::kScreenHeight + kHeight / 2)	isOut = true;
	// �`�F�b�N���̍��W����ʓ��Ȃ炱���ŏI��
	if (isOut) return;

	// �ߋ����O����ʓ��ɂ��邩���`�F�b�N����
	for (int i = 0; i < m_posLog.size(); i++)
	{
		isOut = false;
		if (m_posLog[i].x < 0.0f - kWidth / 2)	isOut = true;
		if (m_posLog[i].x > Game::kScreenWidth + kWidth / 2)	isOut = true;
		if (m_posLog[i].y < 0.0f - kHeight / 2)	isOut = true;
		if (m_posLog[i].y > Game::kScreenHeight + kHeight / 2)		isOut = true;
		// �`�F�b�N���̍��W����ʓ��Ȃ炱���ŏI��
		if (isOut) return;
	}

	// �����ɗ����Ƃ������͉�ʊO�ɂ���
	m_isExist = false;
	//if ((m_vec.x < 0.0f) &&
	//	(m_pos.x < 0.0f - kWidth / 2))
	//{
	//	m_isExist = false;
	//}
	//if ((m_vec.x > 0.0f) &&
	//	(m_pos.x > Game::kScreenWidth / 2))
	//{
	//	m_isExist = false;
	//}
	//if ((m_vec.y < 0.0f) &&
	//	(m_pos.y < 0.0f - kHeight / 2))
	//{
	//	m_isExist = false;
	//}
	//if ((m_vec.y > 0.0f) &&
	//	(m_pos.y > Game::kScreenHeight / 2))
	//{
	//	m_isExist = false;
	//}
}

void ShotMagicWand::Draw()
{
	if (!m_isExist) return;

#if false
	// �c���̕\��
	// 0���ŐV�A7���Â�
	// 0���Z���\���A7�������\��
	for (int i = 0; i < m_posLog.size(); i++)
	{
		int alpha = 255 - (20 * (i + 1));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(m_posLog[i].x - kWidth / 2, m_posLog[i].y - kHeight / 2,
			m_posLog[i].x + kWidth / 2, m_posLog[i].y + kHeight / 2, GetColor(255, 255, 0), true);
	}
	// �\�����[�h����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	// �e�̎���
	DrawBox(m_pos.x - kWidth / 2, m_pos.y - kHeight / 2, 
		m_pos.x + kWidth / 2, m_pos.y + kHeight / 2 , GetColor(255, 255, 0), true);
#else
	
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 1; i < m_posLog.size(); i++)
	{
		for (int listNum = 0; listNum < 8; listNum++)
		{
			int startX = m_pos.x;
			int startY = m_pos.y;
			int endX = m_posLog[i].x;
			int endY = m_posLog[i].y;

			// �����͂���ĂȂ����e
			// �������悭���邽�߂Ɏg��
			float angle = GetRand(359) / 360.0f* DX_TWO_PI_F ;
			float len = GetRand(3) - 1;
			startX += cosf(angle) * len;
			startY += sinf(angle) * len;
			/*angle = GetRand(359) / 360.0f * DX_TWO_PI_F;
			len = GetRand(4) - 2;*/
			endX += cosf(angle) * len;
			endY += sinf(angle) * len;

			DrawLine(startX, startY, endX, endY,
				GetColor(16, 4, 1), kWidth);
		}
	}
	// �\�����[�h����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#endif
#ifdef _DEBUG
	// �e�̓����蔻��f�o�b�O�\��
	m_colRect.Draw(GetColor(0, 0, 0), false);
#endif
}

void ShotMagicWand::Start(Vec2 pos)
{
	// SceneMain�̐ݒ�Y��`�F�b�N
	assert(m_pMain);	// m_pMain == nullptr�Ȃ�~�܂�

	m_isExist = true;
	// �����ʒu�̐ݒ�
	m_pos = pos;

	// �ߋ��̈ʒu�������������_�ł͏������ʒu�Ɠ����ɂ��Ă��܂�
	// �c�����ςȈʒu�ɕ\������Ȃ��悤�ɂ����
	for (int i = 0; i < m_posLog.size(); i++)
	{
		m_posLog[i] = m_pos;
	}

	// ��ԋ߂��G�̕����Ɉړ�����

	// �^�[�Q�b�g�ʒu
	// �e�̔��ˈʒu�����ԋ߂��ɂ���G�̍��W���擾����
	// SceneMain�Ɏ��������֐��𗘗p����
	const Vec2 target = m_pMain->GetNearEnemyPos(m_pos);

	// ���ˈʒu����^�[�Q�b�g�Ɍ������x�N�g��
	Vec2 toTarget = target - m_pos;
	// ���K��
	toTarget.normalize();
	// �e�̑��x��kSpeed��
	m_vec = toTarget * kSpeed;

	//// �������@�E�����Ɉړ�������
	//m_vec.x = kSpeed;
	//m_vec.y = 0.0f;
}