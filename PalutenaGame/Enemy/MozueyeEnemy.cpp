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
	constexpr float kSpeed = 3.0f;
}

MozueyeEnemy::MozueyeEnemy()
{
	EGraph= LoadGraph("data/Fairy.png");

	HP = 2;		// HP
	Atk = 10;	// �U����
	Item;		// �h���b�v�A�C�e��

	Gravity = 0.0f;				// �G�̏����d��
	isTurn = false;				// �E�������Ă����false��}��

	m_pos.x = 300;
	m_pos.y = 300;
}

MozueyeEnemy::~MozueyeEnemy()
{
	DeleteGraph(EGraph);
}

void MozueyeEnemy::Update()
{
	EnemyBase::Update();

	m_basePos += m_vec;

	m_pos += m_basePos;


	//�����蔻��̍X�V
	UpdateCollision();

	int width = 0;
	int height = 0;
	GetGraphSize(EGraph, &width, &height);

	if (m_pos.x > kScreenWidth + width / 2)
	{
		m_isExist = false;
	}

	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	// �x�N�g���̐��K��
	move.normalize();
	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;

	//// ���W�ƃx�N�g���̑����Z
	//enemy += move;

	// �G�ړ�
	//for (int i = 0; i < ENEMY_NUM; i++)
	//{
	//	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
	//	if (isTurn == false)
	//	{
	//		enemy[i].x += kSpeed;
	//	}
	//	else if (isTurn == true)
	//	{
	//		enemy[i].x -= kSpeed;
	//	}
	//	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	//	if (enemy[i].x > kScreenWidth - kWidth)
	//	{
	//		enemy[i].x = kScreenWidth - kWidth;
	//		isTurn = true;
	//	}
	//	else if (enemy[i].x < 0)
	//	{
	//		enemy[i].x = 0;
	//		isTurn = false;
	//	}
	//}
}
