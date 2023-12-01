#include "DxLib.h"
#include "Shot.h"
#include "Game.h"

// �V���b�g�̏�����
void InitShot(Shot& shot)
{
	// �V���b�g�̃O���t�B�b�N���������Ƀ��[�h
	shot.Graph = LoadGraph("data/Shot.png");

	// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����false�������Ă���
	shot.Flag = false;

	// �e�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(shot.Graph, &shot.W, &shot.H);
}

// �V���b�g�̍X�V
void UpdateShot(Shot& shot)
{
	// �e�̓����蔻��
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

}

void DrawShot(Shot& shot)
{
	// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e��true(���݂���)�̏ꍇ�̂ݍs�� )
	if (shot.Flag == true)
	{
		// �ei���P�U�h�b�g���Ɉړ�������
		shot.X += 16;

		// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���false(���݂��Ȃ�)��������
		if (shot.X > kScreenWidth || shot.X < 0)
		{
			shot.Flag = false;
		}
		// ��ʂɒei��`�悷��
		DrawGraph(shot.X, shot.Y, shot.Graph, FALSE);
	}
}