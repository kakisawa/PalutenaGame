#include "PumpkinEnemy.h"
#include "DxLib.h"
#include "Game.h"
#include "Player.h"

namespace
{
	// �G�l�~�[�̃T�C�Y
	constexpr int kWidth = 16;
	constexpr int kHeight = 22;

	// �ړ����x
	constexpr float kSpeed = 1.0f;
}

PumpkinEnemy::PumpkinEnemy()
{

	EGraph= LoadGraph("data/Fairy3.png");

	HP = 1;		// HP
	Atk = 10;	// �U����

	Gravity = 0.0f;				// �G�̏����d��
	isTurn = false;				// �E�������Ă����false��}��

	m_pos.x = kScreenWidth * 0.5;
	m_pos.y = Ground-kHeight*0.5;
}

PumpkinEnemy::~PumpkinEnemy()
{
	DeleteGraph(EGraph);
}

void PumpkinEnemy::Update()
{
	// EnemyBase�̌p�������܂��ł��ĂȂ��H
	// �ꎞ�I�ɗ͋Z�ŌĂяo����
	EnemyBase::Update();

	m_pos += m_vec;

	//�����蔻��̍X�V
	UpdateCollision();

	if (m_pos.x<0 || m_pos.x > kScreenWidth + kWidth / 2)
	{
		m_isExist = false;
	}

	const Vec2 target = m_pPlayer->OutPos();

	// �G�̏����ʒu����^�[�Q�b�g�ʒu�Ɍ������x�N�g���𐶐�����
	// �n�_����I�_�Ɍ������x�N�g�������߂�ꍇ�A�I�_�̍��W-�n�_�̍��W�ŋ��߂�
	Vec2 toTarget = target - m_pos;

	// �x�N�g���̒�����kSpeed�ɂ��Ă��

	// �x�N�g���̐��K���@������1�ɂ���
	toTarget.normalize();
	// kSpeed�ł�����
	m_vec = toTarget * kSpeed;
}

void PumpkinEnemy::Start()
{
	m_isExist = true;
}
