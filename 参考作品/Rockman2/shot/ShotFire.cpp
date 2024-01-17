#include "ShotFire.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "Game.h"
#include <cassert>

// �萔�̒�`
namespace
{
	// �e�̈ړ����x
	constexpr float kSpeed = 10.0f;
	// �V���b�g�̑傫��
	constexpr float kWidth = 32.0f;
	constexpr float kHeight = 32.0f;
}

ShotFire::ShotFire()
{
	// �e�̃O���t�B�b�N���[�h
	m_handle = LoadGraph("data/image/Shot/shotFire.png");
	m_mediumHandle = LoadGraph("data/image/Shot/shotFire2.png");
	m_fullHandle = LoadGraph("data/image/Shot/shotFire3.png");
}

ShotFire::~ShotFire()
{
}

void ShotFire::Init()
{
}

void ShotFire::Update()
{
	// �e�����݂��Ȃ���ΏI������
	if (!m_isExist) return;

	// �v���C���[�̃|�C���^���ݒ肳��Ă��Ȃ��Ƃ��~�܂�
	assert(m_pPlayer);

	// ���݈ʒu�̍X�V
	m_pos += m_vec;

	// �����蔻��̍X�V
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

	// TODO:��Q���ɓ��������������
	//if ()
	//{
	//	m_isExist = false;
	//	return;	// �I�����m�肵����ȍ~�̏����͍s��Ȃ�
	//}

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ����t���O
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // ��ʍ��[
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // ��ʉE�[

	// �`�F�b�N���̍��W����ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// �����ɗ����Ƃ������Ƃ͉�ʊO�ɂ���
	m_isExist = false;
}

void ShotFire::Draw()
{
	if (!m_isExist) return;

	if (m_pPlayer->GetPressTime() < 2000) // ���������Ԃ�2�b�ȉ�
	{
		DrawGraph(m_pos.x, m_pos.y, m_handle, true); // �ʏ�T�C�Y�̒e��`��
	}
	else if (m_pPlayer->GetPressTime() < 5000) // ���������Ԃ�5�b�ȉ�
	{
		if (m_pPlayer->GetFireEnergy() - 6 < 0) // �e�G�l���M�[������Ȃ��ꍇ
		{
			DrawGraph(m_pos.x, m_pos.y, m_handle, true); // �ʏ�T�C�Y�̒e��`��
		}
		else
		{
			DrawGraph(m_pos.x, m_pos.y, m_mediumHandle, true); // ���T�C�Y�̒e��`��
		}
	}
	else // ���������Ԃ�5�b�ȏ�
	{
		if (m_pPlayer->GetFireEnergy() - 10 < 0) // �e�G�l���M�[������Ȃ��ꍇ
		{
			DrawGraph(m_pos.x, m_pos.y, m_handle, true); // �ʏ�T�C�Y�̒e��`��
		}
		else
		{
			DrawGraph(m_pos.x, m_pos.y, m_fullHandle, true); //��T�C�Y�̒e��`��
		}
	}

#ifdef _DEBUG
	// �e�̓����蔻��f�o�b�O�\��
	m_colRect.Draw(0xff0000, false);
#endif
}

void ShotFire::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	m_pos = pos;

	// 1�t���[��������̈ړ��x�N�g�������肷��
	if (m_pPlayer->GetDir()) // �v���C���[���E�������Ă���ꍇ
	{
		m_vec.x = kSpeed;
	}
	else // �v���C���[�����������Ă���ꍇ
	{
		m_vec.x = -kSpeed;
	}
}
