#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include <memory>

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �v���C���[�̃������m��
	std::shared_ptr<Player> pPlayer;
	pPlayer = std::make_shared <Player>();
	// �v���C���[�̃������m��
	std::shared_ptr<Enemy> pEnemy;
	pEnemy = std::make_shared <Enemy>();
	// �}�b�v�̃������m��
	// Map* pMap;
	std::shared_ptr<Map> pMap;
	pMap = std::make_shared<Map>();		// �X�}�[�g�|�C���^,�����ŉ�����Ă����̂�delete�������K�v�͂Ȃ�
	

	// �}�b�v�̏����Q�Ƃł���悤�Ƀ|�C���^��n��
	pPlayer->SetMap(pMap);
	pEnemy->SetMap(pMap);
	// �v���C���[�̏����Q�Ƃł���悤�Ƀ|�C���^��n��
	pMap->setPlayer(pPlayer);


	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
		pMap->Update();
		pEnemy->Update();
		pPlayer->Update();

		pMap->Draw();
		pEnemy->Draw();
		pPlayer->Draw();

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

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}