#include "DeathYourEnemy.h"
#include "DxLib.h"
#include "Game.h"

#include <cassert>

namespace
{
	// �G�l�~�[�̃T�C�Y
	constexpr int kWidth = 63;
	constexpr float kHeight = 103.5f;

	// �G�l�~�[�̉摜���T�C�Y
	constexpr int SrcWidth = 28;
	constexpr int SrcHeight = 46;

	// �ړ����x
	constexpr float kSpeed = 3.0f;
	// �v���C���[HP�����l
	constexpr int kHP = 1;
	// �v���C���[Atk�����l
	constexpr int kAtk = 10;

	// �����X�R�A
	constexpr int kScore = 100;

	// ��{�L�����A�j���[�V����		// ���[�V�����̃t���[�����Ƃɍ�蒼��
	constexpr int DefFrame[] = { 0,1,2,3,4,5,6 };
	// ��{�L�����A�j���[�V������1�R�}�̃t���[����
	constexpr int DefAnimFrameNum = 7;
	// ��{�L�����A�j���[�V����1�T�C�N���̃t���[����
	constexpr int DefFrameCycle = _countof(DefFrame) * DefAnimFrameNum;
}

DeathYourEnemy::DeathYourEnemy()
{
	m_graph = LoadGraph("data/Enemy/DeathYourEnemy.png");

	m_hp = kHP;			// HP
	m_atk = kAtk;			// �U����
	m_score = kScore;		// �|�����ۂɓ�����X�R�A

	m_gravity = 0.0f;		// �G�̏����d��
	m_isTurn = false;		// �E�������Ă����false��}��
	m_angle = 0;			// �G�̈ړ��p�x
	m_enemyAnim = 0;		// �G�̃A�j���[�V�����̏�����
	m_damageFrame = 0;
}

DeathYourEnemy::~DeathYourEnemy()
{
	DeleteGraph(m_graph);
}

void DeathYourEnemy::Init(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}

void DeathYourEnemy::Update()
{
	//m_basePos += m_vec;
	//m_pos += m_basePos;

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

	//�G�ړ�
	if (m_isTurn == false)
	{
		m_angle++;
		float angle2 = m_angle * (DX_PI / 180.0f);
		m_pos.y = sin(angle2) * 200.0f + 550.0f;
		m_pos.x += kSpeed;

	}
	else if (m_isTurn == true)
	{
		m_angle++;
		float angle2 = m_angle * (DX_PI / 180.0f);
		m_pos.y = sin(angle2) * 200.0f + 320.0f;
		m_pos.x -= kSpeed;
	}
	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	if (m_pos.x > kScreenWidth - kWidth)
	{
		m_pos.x = kScreenWidth - kWidth;
		m_isTurn = true;
	}
	else if (m_pos.x < 0)
	{
		m_pos.x = 0;
		m_isTurn = false;
	}

	// �A�j���[�V�����t���[��
	m_enemyAnim++;
	if (m_enemyAnim >= DefFrameCycle)
	{
		m_enemyAnim = 0;
	}
}

void DeathYourEnemy::Draw()
{
	int EnemyFrame = m_enemyAnim / DefAnimFrameNum;
	int srcX = DefFrame[EnemyFrame] * SrcWidth;

	// ���݂��Ȃ��G�͕`�悵�Ȃ�
	if (!m_isExist) return;
	// �O���t�B�b�N���ݒ肳��Ă��Ȃ���Ύ~�܂�
	assert(m_graph != -1);

	if (m_damageFrame % 4 >= 2) return;

	if (m_isTurn == false)
	{
			DrawRectExtendGraph(m_pos.x + kWidth, m_pos.y,
			m_pos.x, m_pos.y + kHeight,
			srcX, 0,
			SrcWidth, SrcHeight,
			m_graph, true);
	}
	else if (m_isTurn == true)
	{
		DrawRectExtendGraph(m_pos.x, m_pos.y,
			m_pos.x + kWidth, m_pos.y + kHeight,
			srcX , 0,
			SrcWidth, SrcHeight,
			m_graph, true);
	}
#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif // DEBUG
}

void DeathYourEnemy::Start(float x, float y)
{
	m_isExist = true;

	m_pos.x =  x;
	m_pos.y = y;
}
