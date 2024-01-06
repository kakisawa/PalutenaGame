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

	enemy.x = kScreenWidth / 3;		// �G���W
	enemy.y = 400;
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
	enemy += move;
	

	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
	if (isTurn == false)
	{
		enemy.x += kSpeed;
	}
	else if (isTurn == true)
	{
		enemy.x -= kSpeed;
	}
	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	if (enemy.x > kScreenWidth - kWidth)
	{
		enemy.x = kScreenWidth - kWidth;
		isTurn = true;
	}
	else if (enemy.x < 0)
	{
		enemy.x = 0;
		isTurn = false;
	}


	// �����蔻��̍X�V
	m_colRect.SetCenter(enemy.x + kWidth / 2, enemy.y + kHeight / 2, kWidth, kHeight);
}

void MozueyeEnemy::Draw()
{
	if (isTurn == false)
	{
		DrawGraph(enemy.x, enemy.y, EGraph, true);
	}
	else if (isTurn == true)
	{
		DrawTurnGraph(enemy.x, enemy.y, EGraph, true);
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
