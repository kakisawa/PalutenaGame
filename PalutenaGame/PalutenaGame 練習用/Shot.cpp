#include "DxLib.h"
#include "Player.h"
#include "Shot.h"
#include "Game.h"

#define PI    3.1415926535897932384626433832795f

namespace
{
	// �e�̈ړ����x
	constexpr int kSpeed =10;

	// �e�̃T�C�Y
	constexpr int kWidth = 16;
	constexpr int kHeight = 8;
}

Shot::Shot()
{
}

Shot::~Shot()
{
}

void Shot::Init()
{
	// �V���b�g�̃O���t�B�b�N���������Ƀ��[�h
	Graph = LoadGraph("data/Shot.png");

	// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����false�������Ă���
	Flag = false;

	// �e�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(Graph, &W, &H);

	// �e�̍������t���O�ɔے��false��������
	LeftDir[SHOT] = false;
	// �e�̏�����t���O�ɔے��false��������
	TopDir[SHOT] = false;
}

void Shot::Update(Player& player)
{
	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, kWidth, kHeight);

	// �e�����݂��Ă���ꍇ�̂ݎ��̏����Ɉڂ�
	if (Flag == true)
	{
		// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���false(���݂��Ȃ�)��������
		if (X[SHOT] > kScreenWidth || X[SHOT] < 0)
		{
			Flag = false;
		}

		// �e�̈ړ�����
		if (player.LeftDir)
		{
			// �e�����Ɉړ�������
			X[SHOT] -= kSpeed;
		}
		else if (player.TopDir)
		{
			// �e����Ɉړ�������
			Y[SHOT] -= kSpeed;
		}
		else
		{
			// �e���E�Ɉړ�������
			X[SHOT] += kSpeed;
		}
	}
}

// �G�l�~�[�Ƃ̓����蔻��
//if (((shot.X > enemy.X && shot.X < enemy.X + enemy.W) ||
//	(enemy.X > shot.X && enemy.X < shot.X + shot.W)) &&
//	((shot.Y > enemy.Y && shot.Y < enemy.Y + enemy.H) ||
//		(enemy.Y > shot.Y && enemy.Y < shot.Y + shot.H)))
//{
//	// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
	//shot.Flag = false;
//}


void Shot::Draw(Player& player)
{
	// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��true(���݂���)�̏ꍇ�̂ݍs�� )
	if (Flag == true)
	{
		// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���false(���݂��Ȃ�)��������
		if (X[SHOT] > kScreenWidth || X < 0)
		{
			Flag = false;
		}

		if (player.isTurn)
		{
			// ��ʂɒei��`�悷��
			DrawTurnGraph(X[SHOT], Y[SHOT], Graph, FALSE);

		}
		else if (player.isLookUp)
		{
			// ��ʂɒei��`�悷��
			DrawRotaGraph(X[SHOT], Y[SHOT], 1.0f, PI * 1.5f, Graph, FALSE);
		}
		else
		{
			// ��ʂɒei��`�悷��
			DrawGraph(X[SHOT], Y[SHOT], Graph, FALSE);
		}
	}
#ifdef _DEBUG
	// �e�̓����蔻��f�o�b�O�\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}