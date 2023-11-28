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
	player.JumpPowor = 40.0f;

	// �W�����v�����ǂ����̃t���O�t���O(������Ă��Ȃ���false��}��)
	player.PushFlag = false;
	// �V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ���false(������Ă��Ȃ�)����
	player.PrevshotFlag = false;
}

void UpdatePlayer(Player& player, Shot shotArray[], int shotArraySize)
{
	// �p�b�h�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	bool isMove = false;	// �ړ������ǂ���


	// ���L�[�������Ă�����v���C���[���ړ�������
	// �W�����v
	if (pad && CheckHitKey(KEY_INPUT_UP) == 1)
	{
		//player.Y -= player.JumpPowor;

		player.Y -= 20.0f;
		player.PushFlag = true;
		isMove = true;
	}
	// ���ނ��A���ړ��͂��Ȃ�
	if (pad && CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		player.Y += player.kSpeed;
		isMove = true;
	}
	// ���ړ�
	if (pad && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		player.X -= player.kSpeed;
		isMove = true;
	}
	// �E�ړ�
	if (pad && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		player.X += player.kSpeed;
		isMove = true;
	}

	//// �W�����v�{�^���������Ă��āA�n�ʂɂ��Ă�����W�����v
	//if (player.Y == Ground) {
	//	if (Pad::IsTrigger(CheckHitKey(KEY_INPUT_RIGHT) == 1))
	//	{
	//		player.Y -= player.JumpPowor;

	//		player.PushFlag = true;
	//		isMove = true;
	//	}
	//}

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


	// �v���C���[����ʂ���͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
	if (player.X < 0)
	{
		player.X = 0;
	}
	if (player.X > kScreenWidth - player.W)
	{
		player.X = kScreenWidth - player.W;
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


void DrawPlayer(Player& player)
{
	// �v���C���[�̕`��
	DrawGraph(player.X, player.Y, player.Graph, false);
}
