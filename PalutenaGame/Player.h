#pragma once

// �v���g�^�C�v�錾
struct Shot;

struct Player 
{
	// �v���C���[�̏����ʒu
	int X;
	int Y;

	// �v���C���[�̉摜
	int Graph;
	// �v���C���[�̉摜�T�C�Y
	int W;
	int H;

	// �ړ����x
	float kSpeed;
	// �����ړ���
	float FallPowor;
	// �W�����v�ړ���
	float JumpPowor;

	// �W�����v�����ǂ����̃t���O
	int PushFlag;
	// �V���b�g�{�^�����O�t���[���ŉ����ꂽ���ǂ����̃t���O
	bool PrevshotFlag;
};

// �v���g�^�C�v�錾
void InitPlayer(Player& player);
void UpdatePlayer(Player& player, Shot shot[], int shotArraySize);
void DrawPlayer(Player& player);