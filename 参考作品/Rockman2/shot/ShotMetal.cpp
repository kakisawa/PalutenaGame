#include "ShotMetal.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "Game.h"
#include "Pad.h"
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

ShotMetal::ShotMetal() :
	m_energy(28)
{
	// �e�̃O���t�B�b�N���[�h
	m_handle = LoadGraph("data/image/Shot/shotMetal.png");
}

ShotMetal::~ShotMetal()
{
}

void ShotMetal::Init()
{
}

void ShotMetal::Update()
{
	// �e�����݂��Ȃ���ΏI������
	if (!m_isExist) return;

	// �v���C���[�̃|�C���^���ݒ肳��Ă��Ȃ��Ƃ��~�܂�
	assert(m_pPlayer);

	// �e�G�l���M�[����1���炷
	m_energy--;

	// ���݈ʒu�̍X�V
	m_pos += m_vec;

	// �����蔻��̍X�V
	m_colRect.SetLT(m_pos.x, m_pos.y, kWidth, kHeight);

	// ��Q���ɓ��������������
	//if ()
	//{
	//	m_isExist = false;
	//	return;	// �I�����m�肵����ȍ~�̏����͍s��Ȃ�
	//}

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ���		true:��ʊO�Afalse:��ʓ�
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true;					// ��ʍ��[
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true;	// ��ʉE�[
	if (m_pos.y < 0.0f - kWidth) isOut = true;						// ��ʏ�
	if (m_pos.y > Game::kScreenHeight) isOut = true;				// ��ʉ�

	// �`�F�b�N���̍��W����ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// �����ɗ����Ƃ������Ƃ͉�ʊO�ɂ���
	m_isExist = false;
}

void ShotMetal::Draw()
{
	if (!m_isExist) return;

	DrawGraph(m_pos.x, m_pos.y, m_handle, true);

#ifdef _DEBUG
	// �e�̓����蔻��f�o�b�O�\��
	m_colRect.Draw(0xff0000, false);
#endif
}

void ShotMetal::Start(Vec2 pos)
{
	m_isExist = true;

	// �����ʒu�̐ݒ�
	m_pos = pos;

	// 1�t���[��������̈ړ��x�N�g�������肷��
	if (Pad::IsPress(PAD_INPUT_RIGHT)) // ��������
	{
		m_vec.x = kSpeed;
		m_vec.y = 0.0f;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT)) // ��������
	{
		m_vec.x = -kSpeed;
		m_vec.y = 0.0f;
	}
	if (Pad::IsPress(PAD_INPUT_UP))	// ��������
	{
		m_vec.x = 0.0f;
		m_vec.y = -kSpeed;
	}
	if (Pad::IsPress(PAD_INPUT_DOWN)) // ��������
	{
		m_vec.x = 0.0f;
		m_vec.y = kSpeed;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT) && Pad::IsPress(PAD_INPUT_UP)) // ��+������������
	{
		m_vec.x = kSpeed;
		m_vec.y = -kSpeed;
		m_vec.normalize();
		m_vec *= kSpeed;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT) && Pad::IsPress(PAD_INPUT_DOWN)) // ��+������������
	{
		m_vec.x = kSpeed;
		m_vec.y = kSpeed;
		m_vec.normalize();
		m_vec *= kSpeed;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT) && Pad::IsPress(PAD_INPUT_UP)) // ��+������������
	{
		m_vec.x = -kSpeed;
		m_vec.y = -kSpeed;
		m_vec.normalize();
		m_vec *= kSpeed;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT) && Pad::IsPress(PAD_INPUT_DOWN)) // ��+������������
	{
		m_vec.x = -kSpeed;
		m_vec.y = kSpeed;
		m_vec.normalize();
		m_vec *= kSpeed;
	}
	if (!Pad::IsPress(PAD_INPUT_RIGHT) && !Pad::IsPress(PAD_INPUT_LEFT) &&
		!Pad::IsPress(PAD_INPUT_UP) && !Pad::IsPress(PAD_INPUT_DOWN)) // ���L�[��������Ă��Ȃ�
	{
		if(m_pPlayer->GetDir()) // �v���C���[���E�������Ă���ꍇ
		{
			m_vec.x = kSpeed;
		}
		if (!m_pPlayer->GetDir()) // �v���C���[�����������Ă���ꍇ
		{
			m_vec.x = -kSpeed;
		}
	}
}
