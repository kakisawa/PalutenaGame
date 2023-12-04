#include "DxLib.h"
#include "Player.h"
#include "Shot.h"
#include "Game.h"
#include "KeyProcess.h"

#include <cmath>

namespace 
{
	// �L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	// �ړ����x
	constexpr float kSpeed = 3.0f;
	// �W�����v�ړ���
	constexpr float JumpPowor = 20.0f;
}

// �v���C���[�̏�����
void InitPlayer(Player& player)
{
	// �v���C���[�̉摜�ǂݍ���&���W�̏�����
	player.Graph = LoadGraph("data/Fairy.png");
	
	player.m_pos.x = kScreenWidth / 2;
	player.m_pos.y = 400;

	// �v���C���[�̏c����
	GetGraphSize(player.Graph, &player.W, &player.H);
	
	// �������x
	player.FallPowor = 0.0f;

	// �O���t�B�b�N���]�t���O(���]���Ă��Ȃ���false��}��)
	player.isTurn = false;
	// �v���C���[����������Ă��邩�̃t���O(�����Ă��Ȃ�false��}��)
	player.isLookUp = false;
	// �W�����v�����ǂ����̃t���O�t���O(������Ă��Ȃ���false��}��)
	player.isPushFlag = false;
	// �ړ������ǂ����̃t���O(�ړ����Ă��Ȃ���false��}��)
	player.isMove = false;
	// �V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ���false(������Ă��Ȃ�)����
	player.isPrevshotFlag = false;

	// �e�̍������t���O(���������Ă��Ȃ���false��}��)
	player.LeftDir = false;
	// �e�̏�����t���O(��������Ă��Ȃ���false��}��)
	player.TopDir = false;
}



// �v���C���[�̍X�V
void UpdatePlayer(Player& player, Shot shotArray[], int shotArraySize)
{
	// �p�b�h�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// �ړ������ǂ���
	bool isMove = false;
	// �ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	// ���L�[�������Ă�����v���C���[���ړ�������
	// �����
	if (pad && CheckHitKey(KEY_INPUT_UP) == 1)
	{
		//pad && CheckHitKey
		player.isLookUp = true;
		player.isMove = true;
		player.isTurn = false;
	}
	// ����
	if (pad && CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		player.isMove = true;
		player.isTurn = false;
	}
	// ���ړ�
	if (pad && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		player.m_pos.x -= kSpeed;
		player.isMove = true;
		player.isLookUp = false;
		player.isTurn = true;
	}
	// �E�ړ�
	if (pad && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		player.m_pos.x += kSpeed;
		player.isMove = true;
		player.isLookUp = false;
		player.isTurn = false;
	}

	// �W�����v
	if (pad && CheckHitKey(KEY_INPUT_A) == 1) {
		player.m_pos.y -= JumpPowor;
		player.isPushFlag = true;
		player.isMove = true;
	}

	// ���������x��������
	player.FallPowor += 0.5f;
	// ��������
	player.m_pos.y += player.FallPowor;

	// �����n�ʂɂ��Ă�����~�܂�
	if (player.m_pos.y > Ground)
	{
		player.m_pos.y = Ground;

		if (player.m_pos.y = Ground)
		{
			player.FallPowor = 0;

			player.isPushFlag = false;
		}
	}

	// �x�N�g���̐��K��
	move.normalize();
	// �x�N�g���̒�����kSpeed�ɂ���
	move *= kSpeed;
	// ���W�ƃx�N�g���̑����Z
	player.m_pos += move;
	
	// �����蔻��̍X�V
	player.m_colRect.SetCenter(player.m_pos.x+kWidth/2, player.m_pos.y+kHeight/2, kWidth, kHeight);


	// �e�̔��ˏ���
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		// �O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���false��������e�𔭎�
		if (player.isPrevshotFlag == false)
		{
			// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
			for (int i = 0; i < shotArraySize; i++)
			{
				// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
				if (shotArray[i].Flag == false)
				{
					// �ei�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
					if (player.isTurn)
					{
						shotArray[i].X = player.m_pos.x;
						player.LeftDir = true;
						player.TopDir = false;
					}
					else if (player.isLookUp)
					{
						shotArray[i].X = player.m_pos.x + kWidth / 2;
						player.LeftDir = false;
						player.TopDir = true;

					}
					else
					{
						shotArray[i].X = (kWidth - shotArray[i].W) / 2 + player.m_pos.x;
						player.LeftDir = false;
						player.TopDir = false;

					}

					shotArray[i].Y = (kHeight - shotArray[i].H) / 2 + player.m_pos.y;

					// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���true��������
					shotArray[i].Flag = true;

					// ��e���o�����̂Œe���o�����[�v���甲���܂�
					break;
				}
			}
		}
		// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ���true(������Ă���)����
		player.isPrevshotFlag = true;
	}
	else
	{
		// �V���b�g�{�^����������Ă��Ȃ������ꍇ��
		// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ���false(������Ă��Ȃ�)����
		player.isPrevshotFlag = false;
	}

	// x���W...�v���C���[�����E��ʊO�ɏo��ƁA���Α�����v���C���[���o�Ă���
	// y���W...�v���C���[����ʊO�ɏo�悤�Ƃ���Ǝ~�܂�
	if (player.m_pos.x < 0 - player.W)
	{
		player.m_pos.x = kScreenWidth - player.W;
	}
	if (player.m_pos.x > kScreenWidth)
	{
		player.m_pos.x = 0;
	}
	if (player.m_pos.y < 0)
	{
		player.m_pos.y = 0;
	}
	if (player.m_pos.y > Ground)
	{
		player.m_pos.y = Ground;
	}
}



// �v���C���[�̕`��
void DrawPlayer(Player& player)
{
	if (player.isTurn)
	{
		// �v���C���[���]�`��(������)
		DrawTurnGraph(player.m_pos.x, player.m_pos.y, player.Graph, false);
	}
	else
	{
		// �v���C���[�`��(�E����)
		DrawGraph(player.m_pos.x, player.m_pos.y, player.Graph, false);
	}

#ifdef _DEBUG
	// �����蔻��̕\��
	player.m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}
