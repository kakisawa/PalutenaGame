#include "PumpkinEnemy.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	// �G�l�~�[�̃T�C�Y
	constexpr int kWidth = 16;
	constexpr int kHeight = 22;

	// �ړ����x
	constexpr float kSpeed = 3.0f;
}

PumpkinEnemy::PumpkinEnemy()
{
	HP = 1;		// HP
	Atk = 10;	// �U����
	Item;		// �h���b�v�A�C�e��
	
	Gravity = 0.0f;				// �G�̏����d��
	isTurn = false;				// �E�������Ă����false��}��

	m_pos.x = kScreenWidth * 0.5;
	m_pos.y = kScreenHeight * 0.5;
}

void PumpkinEnemy::Update()
{
	m_basePos += m_vec;

	m_pos += m_basePos;

	//�����蔻��̍X�V
	UpdateCollision();

	int width = 0;
	int height = 0;
	GetGraphSize(EGraph, &width, &height);

	if (m_pos.x<0 || m_pos.x > kScreenWidth + width / 2)
	{
		m_isExist = false;
	}

	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	// �x�N�g���̐��K��
	move.normalize();
	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;
	// ���W�ƃx�N�g���̑����Z
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

void PumpkinEnemy::Damage(int damage)
{
	// HP�����炷
	HP -= damage;
	// ����HP��0�ȉ��Ȃ玀�S����������
	if (HP <= 0)
	{
		Death();
	}
}
