#include "DeathYourEnemy.h"
#include "DxLib.h"
#include "Game.h"

#include <cassert>

namespace
{
	// �G�l�~�[�̃T�C�Y
	constexpr int kWidth = 42;
	constexpr int kHeight = 69;

	// �G�l�~�[�̉摜���T�C�Y
	constexpr int SrcWidth = 28;
	constexpr int SrcHeight = 46;

	// �ړ����x
	constexpr float kSpeed = 3.0f;

	// ��{�L�����A�j���[�V����		// ���[�V�����̃t���[�����Ƃɍ�蒼��
	constexpr int DefFrame[] = { 0,1,2,3,4,5,6 };
	// ��{�L�����A�j���[�V������1�R�}�̃t���[����
	constexpr int DefAnimFrameNum = 7;
	// ��{�L�����A�j���[�V����1�T�C�N���̃t���[����
	constexpr int DefFrameCycle = _countof(DefFrame) * DefAnimFrameNum;
}

DeathYourEnemy::DeathYourEnemy()
{
	EGraph = LoadGraph("data/Enemy/DeathYourEnemy.png");

	HP = 10;		// HP
	Atk = 10;	// �U����
	Score = 100;	// �|�����ۂɓ�����X�R�A

	Gravity = 0.0f;				// �G�̏����d��
	isTurn = false;				// �E�������Ă����false��}��
	angle = 0;					// �G�̈ړ��p�x
	EnemyAnim = 0;				// �G�̃A�j���[�V�����̏�����
}

DeathYourEnemy::~DeathYourEnemy()
{
	DeleteGraph(EGraph);
}

void DeathYourEnemy::Init()
{
	HP = 10;		// HP
	Atk = 10;	// �U����

	Gravity = 0.0f;				// �G�̏����d��
	isTurn = false;				// �E�������Ă����false��}��
	angle = 0;					// �G�̈ړ��p�x
	EnemyAnim = 0;				// �G�̃A�j���[�V����������
}

void DeathYourEnemy::Update()
{
	//m_basePos += m_vec;
	//m_pos += m_basePos;

	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, kWidth, kHeight);

	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	// �x�N�g���̐��K��
	move.normalize();
	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;


	//�G�ړ�
	if (isTurn == false)
	{
		angle++;
		float angle2 = angle * (DX_PI / 180);
		m_pos.y = sin(angle2) * 200 + 320;
		m_pos.x += kSpeed;

	}
	else if (isTurn == true)
	{
		angle++;
		float angle2 = angle * (DX_PI / 180);
		m_pos.y = sin(angle2) * 200 + 320;
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

void DeathYourEnemy::Draw()
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
			DrawRectExtendGraph(m_pos.x + kWidth, m_pos.y,
			m_pos.x, m_pos.y + kHeight,
			srcX+2, 0,
			SrcWidth, SrcHeight,
			EGraph, true);
	}
	else if (isTurn == true)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX+2, 0,
			SrcWidth, SrcHeight,
			EGraph, true);
	}
#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void DeathYourEnemy::Start(float x, float y)
{
	m_isExist = true;

	m_pos.x = x;
	m_pos.y = y;

}
