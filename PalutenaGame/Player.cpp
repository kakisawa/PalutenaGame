#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include "KeyProcess.h"
#include "Shot.h"

// �v���C���[�̏�����
void InitPlayer(Player& player)
{
	// �v���C���[�̉摜�ǂݍ���&���W�̏�����
	player.Graph = LoadGraph("data/Fairy.png");
	player.X = kScreenWidth / 2;
	player.Y = 400;
	// �v���C���[�̏c����
	GetGraphSize(player.Graph, &player.W, &player.H);

	// �ړ����x
	player.kSpeed = 3.0f;
	// �������x
	player.FallPowor = 0.0f;
	// �W�����v�ړ���
	player.JumpPowor = 20.0f;

	// �W�����v�����ǂ����̃t���O�t���O(������Ă��Ȃ���false��}��)
	player.PushFlag = false;
	// �ړ������ǂ����̃t���O(�ړ����Ă��Ȃ���false��}��)
	player.isMove = false;
	// �V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ���false(������Ă��Ȃ�)����
	player.PrevshotFlag = false;
}

// �v���C���[�̍X�V
void UpdatePlayer(Player& player, Shot shotArray[], int shotArraySize)
{
	// �p�b�h�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	
	// ���L�[�������Ă�����v���C���[���ړ�������
	// �W�����v
	if (pad && CheckHitKey(KEY_INPUT_UP))
	{
		//pad && CheckHitKey
		player.Y -= player.JumpPowor;
		player.PushFlag = true;
		player.isMove = true;
	}
	// ���ނ��A���ړ��͂��Ȃ�
	if (pad && CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		player.isMove = true;
	}
	// ���ړ�
	if (pad && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		player.X -= player.kSpeed;
		player.isMove = true;
	}
	// �E�ړ�
	if (pad && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		player.X += player.kSpeed;
		player.isMove = true;
	}

	// ���������x��������
	player.FallPowor += 0.5f;

	// ��������
	player.Y += player.FallPowor;

	// �����n�ʂɂ��Ă�����~�܂�
	if (player.Y > Ground)
	{
		player.Y = Ground;

		if (player.Y = Ground)
		{
			player.FallPowor = 0;

			player.PushFlag = false;
		}
	}

	// �e�̔��ˏ���
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// �O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���false��������e�𔭎�
		if (player.PrevshotFlag == false)
		{
			// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
			for (int i = 0; i < shotArraySize; i++)
			{
				// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
				if (shotArray[i].Flag == false)
				{
					// �ei�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
					shotArray[i].X = (player.W - shotArray[i].W) / 2 + player.X;
					shotArray[i].Y = (player.H - shotArray[i].H) / 2 + player.Y;

					// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���true��������
					shotArray[i].Flag = true;

					// ��e���o�����̂Œe���o�����[�v���甲���܂�
					break;
				}
			}
		}
		// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ���true(������Ă���)����
		player.PrevshotFlag = true;
	}
	else
	{
		// �V���b�g�{�^����������Ă��Ȃ������ꍇ��
		// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ���false(������Ă��Ȃ�)����
		player.PrevshotFlag = false;
	}

	// x���W...�v���C���[�����E��ʊO�ɏo��ƁA���Α�����v���C���[���o�Ă���
	// y���W...�v���C���[����ʊO�ɏo�悤�Ƃ���Ǝ~�܂�
	if (player.X < 0 -player.W)
	{
		player.X = kScreenWidth - player.W;
	}
	if (player.X > kScreenWidth)
	{
		player.X = 0;
	}
	if (player.Y < 0)
	{
		player.Y = 0;
	}
	if (player.Y > Ground)
	{
		player.Y = Ground;
	}
}

// �v���C���[�̕`��
void DrawPlayer(Player& player)
{
	DrawGraph(player.X, player.Y, player.Graph, false);
}
