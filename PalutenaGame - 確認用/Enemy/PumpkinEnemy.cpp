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
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].x = kScreenWidth / 5;		// �G���W
		enemy[i].y = 400 - i * kHeight;
	}


	Gravity = 0.0f;				// �G�̏����d��
	isTurn = false;				// �E�������Ă����false��}��
}

void PumpkinEnemy::Init()
{
}

void PumpkinEnemy::Update()
{// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	// �x�N�g���̐��K��
	move.normalize();
	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;
	// ���W�ƃx�N�g���̑����Z
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[ENEMY_NUM] += move;
	}

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

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// �����蔻��̍X�V
		m_colRect[i].SetCenter(enemy[i].x + kWidth / 2, enemy[i].y + kHeight / 2, kWidth, kHeight);
	}
}

void PumpkinEnemy::Draw()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (isTurn == false)
		{
			DrawGraph(enemy[i].x, enemy[i].y, EGraph, true);
		}
		else if (isTurn == true)
		{
			DrawTurnGraph(enemy[i].x, enemy[i].y, EGraph, true);
		}
	}

#ifdef _DEBUG
	// �����蔻��̕\��
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		m_colRect[i].Draw(GetColor(0, 0, 255), false);
	}
#endif
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
