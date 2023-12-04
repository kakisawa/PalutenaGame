#include "DxLib.h"
#include "Player.h"
#include "Shot.h"
#include "Game.h"

#define PI    3.1415926535897932384626433832795f

namespace
{
	// �e�̈ړ����x
	constexpr int kSpeed = 16;

	// �e�̃T�C�Y
	constexpr int kWidth = 16;
	constexpr int kHeight = 8;
}

// �V���b�g�̏�����
void InitShot(Shot& shot)
{
	// �V���b�g�̃O���t�B�b�N���������Ƀ��[�h
	shot.Graph = LoadGraph("data/Shot.png");

	// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����false�������Ă���
	shot.Flag = false;

	// �e�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(shot.Graph, &shot.W, &shot.H);

	//// �e�̍������t���O�ɔے��false��������
	//shot.LeftDir = false;
	//// �e�̏�����t���O�ɔے��false��������
	//shot.TopDir = false;
}

// �V���b�g�̍X�V
void UpdateShot(Shot& shot, Player& player)
{
	// �����蔻��̍X�V
	shot.m_colRect.SetCenter(shot.m_pos.x + kWidth / 2, shot.m_pos.y + kHeight / 2, kWidth, kHeight);

		// �e�����݂��Ă���ꍇ�̂ݎ��̏����Ɉڂ�

	// �G�l�~�[�Ƃ̓����蔻��
	//if (((shot.X > enemy.X && shot.X < enemy.X + enemy.W) ||
	//	(enemy.X > shot.X && enemy.X < shot.X + shot.W)) &&
	//	((shot.Y > enemy.Y && shot.Y < enemy.Y + enemy.H) ||
	//		(enemy.Y > shot.Y && enemy.Y < shot.Y + shot.H)))
	//{
	//	// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
		//shot.Flag = false;
	//}


	// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��true(���݂���)�̏ꍇ�̂ݍs�� )
	if (shot.Flag == true)
	{
		// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���false(���݂��Ȃ�)��������
		if (shot.X > kScreenWidth || shot.X < 0)
		{
			shot.Flag = false;
		}

		if (player.LeftDir)
		{
			// �ei���P�U�h�b�g���Ɉړ�������
			shot.X -= kSpeed;
		}
		else if (player.TopDir)
		{
			// �ei���P�U�h�b�g��Ɉړ�������
			shot.Y -= kSpeed;
		}
		else
		{
			// �ei���P�U�h�b�g���Ɉړ�������
			shot.X += kSpeed;
		}
	}
}

void DrawShot(Shot& shot, Player& player)
{
	// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��true(���݂���)�̏ꍇ�̂ݍs�� )
	if (shot.Flag == true)
	{
		// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���false(���݂��Ȃ�)��������
		if (shot.X > kScreenWidth || shot.X < 0)
		{
			shot.Flag = false;
		}

		if (player.isTurn)
		{
			// ��ʂɒei��`�悷��
			DrawTurnGraph(shot.X, shot.Y, shot.Graph, FALSE);

		}
		else if (player.isLookUp)
		{
			// ��ʂɒei��`�悷��
			DrawRotaGraph(shot.X, shot.Y, 1.0f, PI * 1.5f, shot.Graph, FALSE);
		}
		else
		{
			// ��ʂɒei��`�悷��
			DrawGraph(shot.X, shot.Y, shot.Graph, FALSE);
		}
	}
#ifdef _DEBUG
	// �e�̓����蔻��f�o�b�O�\��
	shot.m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}