#include "PumpkinEnemy.h"
#include "DxLib.h"
#include "Game.h"
#include "Player.h"

#include <cassert>

namespace
{
	// �G�l�~�[�̃T�C�Y
	constexpr int kWidth = 48;
	constexpr int kHeight = 66;

	// �G�l�~�[�̉摜���T�C�Y
	constexpr int SrcWidth = 16;
	constexpr int SrcHeight = 22;

	// �ړ����x
	constexpr float kSpeed = 1.0f;

	// �v���C���[HP�����l
	constexpr int kHP = 1;
	// �v���C���[Atk�����l
	constexpr int kAtk = 30;
	// �����X�R�A
	constexpr int kScore = 100;

	// ��{�L�����A�j���[�V����		// ���[�V�����̃t���[�����Ƃɍ�蒼��
	constexpr int DefFrame[] = { 0,1,2,3,4,5,6,7 };
	// ��{�L�����A�j���[�V������1�R�}�̃t���[����
	constexpr int DefAnimFrameNum = 8;
	// ��{�L�����A�j���[�V����1�T�C�N���̃t���[����
	constexpr int DefFrameCycle = _countof(DefFrame) * DefAnimFrameNum;
}

PumpkinEnemy::PumpkinEnemy()
{
	EGraph= LoadGraph("data/Enemy/Pumpkin.png");

	HP = kHP;			// HP
	Atk = kAtk;			// �U����
	Score = kScore;			// �|�����ۂɓ�����X�R�A

	Gravity = 0.0f;		// �G�̏����d��
	isTurn = false;		// �E�������Ă����false��}��
	EnemyAnim = 0;		// �G�̃A�j���[�V�����̏�����
}

PumpkinEnemy::~PumpkinEnemy()
{
	DeleteGraph(EGraph);
}

void PumpkinEnemy::Update()
{
	// �_���[�W���o�̐i�s
	m_damageFrame--;
	if (m_damageFrame < 0)	m_damageFrame = 0;

	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2,
		kWidth, kHeight);

	m_pos += m_vec;

	const Vec2 target = m_pPlayer->OutPos();

	// �G�̏����ʒu����^�[�Q�b�g�ʒu�Ɍ������x�N�g���𐶐�����
	// �n�_����I�_�Ɍ������x�N�g�������߂�ꍇ�A�I�_�̍��W-�n�_�̍��W�ŋ��߂�
	Vec2 toTarget = target - m_pos;

	// �x�N�g���̐��K���@������1�ɂ���
	toTarget.normalize();
	// kSpeed�ł�����
	m_vec = toTarget * kSpeed;

	if (m_pos.x<0 || m_pos.x > kScreenWidth + kWidth / 2)
	{
		m_isExist = false;
	}

	// �A�j���[�V�����t���[��
	EnemyAnim++;
	if (EnemyAnim >= DefFrameCycle)
	{
		EnemyAnim = 0;
	}
}

void PumpkinEnemy::Draw()
{
	int EnemyFrame = EnemyAnim / DefAnimFrameNum;
	int srcX = DefFrame[EnemyFrame] * SrcWidth;

	// ���݂��Ȃ��G�͕`�悵�Ȃ�
	if (!m_isExist) return;
	// �O���t�B�b�N���ݒ肳��Ă��Ȃ���Ύ~�܂�
	assert(EGraph != -1);

	if (m_damageFrame % 4 >= 2) return;

	if (isTurn == false)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX-1, 25,
			SrcWidth, SrcHeight,
			EGraph, true);
	}
	else if (isTurn == true)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX - 1, 0,
			SrcWidth, SrcHeight,
			EGraph, true);
	}
#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void PumpkinEnemy::Start(float x, float y)
{
	m_isExist = true;

	m_pos.x = x;
	m_pos.y = y;
}
