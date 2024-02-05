#include "DxLib.h"
#include "MozueyeEnemy.h"
#include "Player.h"
#include "Game.h"

#include <cassert>

namespace
{
	// �G�l�~�[�̃T�C�Y
	constexpr float kWidth = 93.6f;
	constexpr int kHeight = 65;

	// �G�l�~�[�̉摜���T�C�Y
	constexpr int SrcWidth = 46;
	constexpr int SrcHeight = 32;

	// �ړ����x
	float kSpeed = 3.0f;
	// �v���C���[HP�����l
	constexpr int kHP = 2;
	// �v���C���[Atk�����l
	constexpr int kAtk = 10;

	// ��{�L�����A�j���[�V����		// ���[�V�����̃t���[�����Ƃɍ�蒼��
	constexpr int DefFrame[] = { 0,1,2,3,4 };
	// ��{�L�����A�j���[�V������1�R�}�̃t���[����
	constexpr int DefAnimFrameNum = 10;
	// ��{�L�����A�j���[�V����1�T�C�N���̃t���[����
	constexpr int DefFrameCycle = _countof(DefFrame) * DefAnimFrameNum;
}

MozueyeEnemy::MozueyeEnemy()
{
	EGraph= LoadGraph("data/Enemy/Mozueye.png");

	HP = kHP;		// HP
	Atk = kAtk;	// �U����
	Score = 50;	// �|�����ۂɓ�����X�R�A

	Gravity = 0.0f;				// �G�̏����d��
	isTurn = false;				// �E�������Ă����false��}��
	EnemyAnim = 0;				// �G�̃A�j���[�V�����̏�����
}

MozueyeEnemy::~MozueyeEnemy()
{
	DeleteGraph(EGraph);
}

void MozueyeEnemy::Update()
{
	// �_���[�W���o�̐i�s
	m_damageFrame--;
	if (m_damageFrame < 0)	m_damageFrame = 0;

	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2,
		kWidth, kHeight);

	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };
	// �x�N�g���̐��K��
	move.normalize();
	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;
	m_pos += move;

	//�G�ړ�
	if (isTurn == false)
	{
		if (kSpeed <= 40.0f)
		{
			kSpeed = 3.0f;
		}

		kSpeed += 5.0f;
		m_pos.x += kSpeed;
	}
	else if (isTurn == true)
	{
		m_pos.x -= kSpeed;
	}

	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	if (m_pos.x > kScreenWidth - kWidth)
	{
		m_pos.x = kScreenWidth - kWidth;
		isTurn = true;
	}
	else if (m_pos.x < 0)
	{
		m_pos.x = 0;
		isTurn = false;
	}

	// �A�j���[�V�����t���[��
	EnemyAnim++;
	if (EnemyAnim >= DefFrameCycle)
	{
		EnemyAnim = 0;
	}
}

void MozueyeEnemy::Draw()
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
			srcX + 2, 29,
			SrcWidth, SrcHeight,
			EGraph, true);
	}
	else if (isTurn == true)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX + 2, 0,
			SrcWidth, SrcHeight,
			EGraph, true);
	}
#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void MozueyeEnemy::Start(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;

	m_isExist = true;
}