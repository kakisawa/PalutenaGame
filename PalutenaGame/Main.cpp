#include "DxLib.h"
#include "Vec2.h"
#include <cmath>

namespace
{
	// ��ʕ�(��)
	int kScreenWidth = 720;
	// ��ʕ�(�c)
	int kScreenHeight = 480;
	// �J���[�r�b�g��
	int kColorDepth = 32;

	// �v���C���[�̃T�C�Y
	int kWidth = 32;
	int kHeight = 32;

	// �v���C���[�̏����ʒu
	int PlayerX = kScreenWidth / 2;
	int PlayerY = 400;

	// �n��
	int Ground = 400;

	// �ړ����x
	float kSpeed = 3.0f;

	// �W�����v�ړ���
	float JumpPower = 0.0f;

	// �W�����v�{�^���t���O
	int push = 0;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ��ʃ��[�h�ύX(�𑜓x�E�r�b�g��)
	SetGraphMode(kScreenWidth, kScreenHeight, 32);


	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);


	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// �v���C���[�̃��[�h
	int handle = LoadGraph("data/Fairy.png");

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �Q�[���̏���

		// ���L�[�������Ă�����v���C���[���ړ�������
		// �W�����v
		if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			PlayerY -= 3;
		}
		// ���ނ��A���ړ��͂��Ȃ�
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			PlayerY += 3;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			PlayerX -= 3;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			PlayerX += 3;
		}

		// �v���C���[����ʂ���͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
		if (PlayerX < 0)
		{
			PlayerX = 0;
		}
		if (PlayerX > kScreenWidth - kWidth)
		{
			PlayerX = kScreenWidth - kWidth;
		}
		if (PlayerY < 0)
		{
			PlayerY = 0;
		}
		if (PlayerY > Ground)
		{
			PlayerY = Ground;
		}

		// ��������
		PlayerY -= JumpPower;

		// ���������x��������
		JumpPower -= 1;

		// �����n�ʂɂ��Ă�����~�܂�
		if (PlayerY > Ground)
		{
			PlayerY = Ground;
			JumpPower = 0;
		}

		// �W�����v�{�^���������Ă��āA�n�ʂɂ��Ă�����W�����v
		if (CheckHitKey(KEY_INPUT_A) && PlayerY == Ground)
		{
			JumpPower = 10;
			push = 1;
		}



		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();
		// �v���C���[�̕`��
		DrawGraph(PlayerX, PlayerY, handle, false);
		

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

	DeleteGraph(handle);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}