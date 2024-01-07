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
	HP = 1;		// HP
	Atk = 10;	// �U����
	Item;		// �h���b�v�A�C�e��

	enemy[ENEMY_NUM].x = kScreenWidth / 3;		// �G���W
	enemy[ENEMY_NUM].y = 400;
	/*
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].y = 400 - i * kHeight;
	}
	*/

	Gravity = 0.0f;				// �G�̏����d��
	isTurn = false;				// �E�������Ă����false��}��
}

void MozueyeEnemy::Init()
{
	EGraph = LoadGraph("data/Fairy.png");
}

void MozueyeEnemy::Update()
{
	// �ړ��ʂ����悤�ɂ���
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


	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
		if (isTurn == false)
		{
			enemy[i].x += kSpeed;
		}
		else if (isTurn == true)
		{
			enemy[i].x -= kSpeed;
		}
		// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
		if (enemy[i].x > kScreenWidth - kWidth)
		{
			enemy[i].x = kScreenWidth - kWidth;
			isTurn = true;
		}
		else if (enemy[i].x < 0)
		{
			enemy[i].x = 0;
			isTurn = false;
		}
	}

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// �����蔻��̍X�V
		m_colRect.SetCenter(enemy[i].x + kWidth / 2, enemy[i].y + kHeight / 2, kWidth, kHeight);
	}
}

void MozueyeEnemy::Draw()
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
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}

void MozueyeEnemy::Damage(int damage)
{
	// HP�����炷
	HP -= damage;
	// ����HP��0�ȉ��Ȃ玀�S����������
	if (HP <= 0)
	{
		Death();
	}
}
