#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include <cassert>

#include "SceneManager.h"

namespace
{
}

/*
// �v���C���[�ƓG�̓����蔻��
// �������Ă���ꍇ�Atrue��Ԃ�		(return true;����)
// �������Ă��Ȃ��ꍇ�Afalse��Ԃ�	(return false;����)

// �v���C���[�ƓG�̓����蔻��
bool IsCollision(const Player& player, const Enemy& enemy)
{
	// �����蔻��
	// �v���C���[�������S�ɍ��ɂ���ꍇ�͓������Ă��Ȃ�
	// �v���C���[���[�������ɓG�̉E�[������ꍇ�͓������Ă��Ȃ�
	if (player.GetLeft() > enemy.GetRight())
	{
		// ���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ɗm��
		return false;	// �m���ɓ������Ă��Ȃ��̂�false��Ԃ�
	}
	// �v���C���[�������S�ɉ��ɂ���ꍇ�͓������Ă��Ȃ�
	// �v���C���[���[�������ɓG�̏�[������ꍇ�͓������Ă��Ȃ�
	if (player.GetBottom() < enemy.GetTop())
	{
		// ���S�ɍ��ɂ���̂œ������Ă��Ȃ����Ɗm��
		return false;	// �m���ɓ������Ă��Ȃ��̂�false��Ԃ�
	}
	// ���l�Ɋ��S�ɉE�ɂ���p�^�[������菜��
	if (player.GetRight() < enemy.GetLeft())
	{
		return false;	// �m���ɓ������Ă��Ȃ��̂�false��Ԃ�

	}
	// ���l�Ɋ��S�ɏ�ɂ���p�^�[������菜��
	if (player.GetTop() > enemy.GetBottom())
	{
		return false;	// �m���ɓ������Ă��Ȃ��̂�false��Ԃ�
	}

	return true;
}

#if false	// �R�����g���폜���Ă������肳����Ƃ���Ȋ���
bool IsCollision(const Player& player, const Enemy& enemy)
{
	if (player.GetLeft() > enemy.GetRight())	return false;
	if (player.GetBottom() < enemy.GetTop())	return false;
	if (player.GetRight() < enemy.GetLeft())	return false;
	if (player.GetTop() > enemy.GetBottom())	return false;

	return true;
}
#endif

*/

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	// ��ʂ̃T�C�Y�ύX
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// �V�[��
	SceneManager scene;
	scene.Init();

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���V�[���̍X�V
		scene.Update();
		// �Q�[���V�[���̕`��
		scene.Draw();

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

		// ���s���Ă����V�[���̏I������
	scene.End();

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}



#if false
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	// ��ʂ̃T�C�Y�ύX
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);



	SceneMain sceneMain;
	sceneMain.Init();


	// �Q�[���V�[��������
	int sceneNo = 0;	// ���݂̃V�[����ϐ��Ŏ���
						// 0:Title 1:Main
						// �{����enum���ł��ׂ�
	SceneTitle  sceneTitle;

	SceneMain sceneMain;
	sceneTitle.Init();

	/*
	int playerHandle = LoadGraph("data/player.png");
	assert(playerHandle != -1);	// �O���t�B�b�N�̃��[�h�Ɏ��s���Ă�����~�߂�
	int enemyHandle = LoadGraph("data/enemy.png");
	assert(enemyHandle != -1);	// �O���t�B�b�N�̃��[�h�Ɏ��s���Ă�����~�߂�

	Player player;
	player.Init();
	player.SetGraphHandle(playerHandle);

	Enemy enemy;
	enemy.Init();
	enemy.SetGrahpHandle(enemyHandle);
	enemy.SetStartPos();	// �O���t�B�b�N��ݒ肵���㏉���l�ɐݒ�
	*/

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���

		sceneMain.Update();
		sceneMain.Draw();


		switch (sceneNo)
		{
		case 0:
			sceneTitle.Update();
			sceneTitle.Draw();
			if (sceneTitle.isEnd())	// �^�C�g���I��
			{
				// �^�C�g�����I������
				sceneTitle.End();

				// ���̃V�[����p�ӂ���
				sceneNo = 1;	// SceneMain�ɕύX
				sceneMain.Init();
			}
			break;
		case 1:
			sceneMain.Update();
			sceneMain.Draw();
			break;
		default:
			assert(false);	// ���݂��Ȃ��V�[���̔ԍ����w�肳��Ă���
			break;
		}

		/*
		if (IsCollision(player, enemy))
		{
			// �������Ă��邩�ǂ������m�F����f�o�b�O�\��
			DrawString(8, 8, "�������Ă���", GetColor(255, 255, 255));
		}
		*/

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// �V�[���̏I��
		if (sceneMain.IsSceneEnd())
		{
			break;
		}

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

	// �V�[���̏I������
	sceneMain.End();

	switch (sceneNo)
	{
	case 0:
		sceneTitle.Init();
		break;
	case 1:
		sceneMain.Init();
		break;
	default:
		assert(false);	// ���݂��Ȃ��V�[���̔ԍ����w�肳��Ă���
		break;
	}

	/*
	// ����������O���t�B�b�N���폜����
	DeleteGraph(playerHandle);
	DeleteGraph(enemyHandle);
*/

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
#endif