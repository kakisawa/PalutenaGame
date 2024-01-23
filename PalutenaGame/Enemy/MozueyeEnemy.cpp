#include "DxLib.h"
#include "MozueyeEnemy.h"
#include "Player.h"
#include "Game.h"

namespace
{
	// �G�l�~�[�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// �ړ����x
	float kSpeed = 3.0f;
}

MozueyeEnemy::MozueyeEnemy()
{
	EGraph= LoadGraph("data/Fairy.png");

	HP = 2;		// HP
	Atk = 10;	// �U����

	Gravity = 0.0f;				// �G�̏����d��
	isTurn = false;				// �E�������Ă����false��}��

	m_pos.x = kScreenWidth * 0.3;
	m_pos.y = Ground - kHeight*0.5;
}

MozueyeEnemy::~MozueyeEnemy()
{
	DeleteGraph(EGraph);
}

void MozueyeEnemy::Update()
{
	EnemyBase::Update();

	//�����蔻��̍X�V
	UpdateCollision();

	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

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

	// �x�N�g���̐��K��
	move.normalize();
	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;

	m_pos += move;

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
}

void MozueyeEnemy::Start()
{
	m_isExist = true;
}
