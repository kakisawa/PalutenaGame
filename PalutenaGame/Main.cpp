#include "DxLib.h"
#include "Vec2.h"

#include "Player.h"
#include "Shot.h"
#include "Game.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ��ʃ��[�h�ύX(�𑜓x�E�r�b�g��)
	SetGraphMode(kScreenWidth, kScreenHeight, kColorDepth);

	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);


	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[���̏���
	Player player;
	Shot shot[SHOT];


	// �v���C���[�̏�����
	player.Init();

	// �V���b�g�̏�����
	for (int i = 0; i < SHOT; i++)
	{
		shot[i].Init();
	}

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �v���C���[�̍X�V
		player.Update(shot, SHOT);

		// �v���C���[�̕`��
		player.Draw();

		// �V���b�g�̕`��E�X�V
		for (int i = 0; i < SHOT; i++)
		{
			shot[i].Update(player);
			shot[i].Draw(player);
		}

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// �}�C�i�X�̒l�i�G���[�l�j���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0)
		{
			break;
		}
		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}