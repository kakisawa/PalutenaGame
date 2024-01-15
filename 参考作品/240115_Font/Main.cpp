#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// �g�p����t�H���g����������

	// ********** �t�H���g�̃��[�h **********
	LPCSTR font_path = "Font/mogihaPen.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	// ********** ��������ǂݍ��񂾃t�H���g�𗘗p�ł��� **********

	// �^�C�g���\���p�̃t�H���g
	int titleFont = CreateFontToHandle("���M�n�E�y����Font", 64, -1);
	int explanationFontHandle = CreateFontToHandle("HGP�n�p�p�߯�ߑ�", 32, -1);

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���

		/*SetFontSize(64);
		ChangeFont("HG�ۺ޼��M-PRO");
		DrawString(100, 100, "�t�H���g�̃e�X�g", 0xffffff);
		SetFontSize(32);
		DrawString(160, 200, "�{�^���������Ă�������", 0xffffff);*/

		DrawStringToHandle(100, 100, "�Q�[���̃^�C�g��", 0xffffff, titleFont);
		DrawStringToHandle(160, 200, "�{�^���������Ă�������", 0xffffff, explanationFontHandle);

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
	DeleteFontToHandle(titleFont);
	DeleteFontToHandle(explanationFontHandle);

	// ********** �t�H���g�̃A�����[�h **********
	if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
		// �A�����[�h�ɐ���
	}
	else {
		// �A�����[�h�Ɏ��s
		MessageBox(NULL, "remove failure", "", MB_OK);
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}