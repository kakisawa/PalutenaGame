#include "SceneMain.h"
#include "DxLib.h"
#include "Player.h"
#include "Bg.h"
#include "Pad.h"
#include "Rect.h"

// �o�ꂷ��G
// #include "EnemyBase.h"
#include "EnemyLeft.h"
#include "EnemyRight.h"
#include "EnemyToPlayer.h"

// �o�ꂷ��V���b�g
#include "ShotMagicWand.h"
#include <cassert>

namespace
{
	// ��x�ɓo��ł���G�̍ő吔
	constexpr int kEnemyMax = 32;
	// ���t���[�������ɓG���o�ꂷ�邩
	constexpr int kEnemyInterval = 60;

	// ��ʓ��Ɉ�x�ɏo�Ă���e�̍ő吔
	constexpr int kShotMax = 260;

	// ��ʂ����C�v����̂ɂ�����t���[����
	constexpr int kWipeFrame = 30;
}

SceneMain::SceneMain():
	m_enemyInterval(0),
	m_shakeFrame(0),
	m_wipeFrame(0)
{
	// �Q�[����ʕ`���̐���
	// ��ʃT�C�Y�Ɠ����傫���̃O���t�B�b�N�f�[�^���쐬����
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	// �O���t�B�b�N�̃��[�h
	m_playerHandle = LoadGraph("data/image/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/image/Enemy.bmp");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/image/bg.png");
	assert(m_bgHandle != -1);

	// �v���C���[�̃������m��
	m_pPlayer = new Player{this};
	m_pPlayer->SetHandle(m_playerHandle);	// Player�ɃO���t�B�b�N�̃n���h����n��

	// �w�i�̃������m��
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);
	
	// �G�̏���
	// m_pEnemy(vector)�������Ȃ���΃T�C�Y��0

	// resize�֐���kEnemyMax�����f�[�^��ۑ��ł���悤�ɂ���
	m_pEnemy.resize(kEnemyMax);

	// �����̓R���X�g���N�^�Ń��������m�ۂ���
	// �f�X�g���N�^�ŉ�����Ă�������
	// �����_����EnemyLeft,EnemyRight,EnemyToPlayer���m�ۂ�����
	// �ǂꂩ�킩��Ȃ��̂ł��炩���ߊm�ۂ��邱�Ƃ��o���Ȃ�
	// ->���I�Ƀ��������m�ۂ��� Update()���ɕK�v�ɉ�����

	// ������Ԃł̓��������m�ۂ��Ă��Ȃ����Ƃ�������悤�ɂ��Ă���
	// ���g�p��Ԃɂ��� nullptr�����Ă���
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = nullptr;

			// m_pEnemy�̒��ɂ͉������邩�킩��Ȃ�
			// ���̂����ꂩ������
			// �����_�ł͂ǂꂪ����̂�����ł��Ȃ�
		// new EnemyLeft;
		// new EnemyRighr;
		// new EnemyToPlayer;
	}

	// �V���b�g�̏���
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr;	// ���g�p
	}

	//m_pShot = new ShotMagicWand;
	//// SceneMain�̊֐����g�������̂Ń|�C���^��n���Ă���
	//// this�Ŏ��g�̃|�C���^���擾�\
	//m_pShot->SetMain(this);
}

SceneMain::~SceneMain()
{
	// MakeScreen�ō쐬������O���t�B�b�N���폜����
	DeleteGraph(m_gameScreenHandle);
	
	// ����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_bgHandle);

	// �������̉��
	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pBg;
	m_pBg = nullptr;
	
	// ���������m�ۂ���Ă���G��T���ĊJ�����Ă���
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// nullpte�ȊO�̕��������Ă���Ƃ������Ƃ́A�����ɂ̓|�C���^�������Ă���Ƃ�������
		if (m_pEnemy[i] != nullptr)	
		{
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;	// ���g�p��Ԃƕ�����悤�ɂ��Ă���
		}
	}

	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			// nullptr�ł͂Ȃ��ꍇ
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}
}

void SceneMain::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr	�̏ꍇ�~�܂�

	m_pPlayer->Init();
	m_pBg->Init();
}

void SceneMain::End()
{
	// ����������O���t�B�b�N���폜
}

void SceneMain::Update()
{
	m_pPlayer->Update();
	m_pBg->Update();

	Rect playerRect = m_pPlayer->GetColRect();
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	// nullptr�ł͂Ȃ��`�F�b�N
		{
			m_pEnemy[i]->Update();
		
			// �g�p�ς݂̓G�L�����N�^���폜����K�v������
			if (!m_pEnemy[i]->IsExist())
			{
				// ���������������
				delete m_pEnemy[i];
				m_pEnemy[i] = nullptr;	// �g���Ă��Ȃ��Ƃ킩��悤�ɂ���
			}
			else
			{
				// ���݂��Ă���G�ƃv���C���[�̓����蔻��
				Rect enemyRect = m_pEnemy[i]->GetColRect();
				if (playerRect.IsCollsion(enemyRect))
				{
				//	// test
					printfDx("�������Ă���\n");
					m_pPlayer->OnDamage();
					// �v���C���[���_���[�W���󂯂��u�ԁA��ʂ��h��n�܂�
					m_shakeFrame = 8;
				}
			}
		}
	}
	
	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[i])	continue;

		m_pShot[i]->Update();
		// ��ʊO�ɏo���烁�������
		if (!m_pShot[i]->IsExist())
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}

	// ���C�v����
	m_wipeFrame++;
	if (m_wipeFrame > kWipeFrame)	m_wipeFrame = kWipeFrame;


	// �G�L�����N�^�[��o�ꂳ����
	// kEnemyInterval�t���[���o�߂��邲�ƂɃ����_���ɓG��o�ꂳ����
	m_enemyInterval++;
	if (m_enemyInterval >= kEnemyInterval)
	{
		m_enemyInterval = 0;

		// �����_���ɓG��I��
		switch (GetRand(2))
		{
		case 0:	// Left
			CreateEnemyLeft();
			break;

		case 1:		// Right
			CreateEnemyRight();
			break;

		default:	assert(false);	// break�Ȃ�

		case 2:		// ToPlayer
			CreateEnemyToPlayer();
			break;
		}
	}
	// ��ʗh��t���[���̃J�E���g�_�E��
	m_shakeFrame--;
	if (m_shakeFrame < 0)	m_shakeFrame = 0;
}

void SceneMain::Draw()
{
	// �o�b�N�o�b�t�@�ɒ��ڏ������ނ̂ł͂Ȃ��A
	// �����Ő��������O���t�B�b�N�f�[�^�ɑ΂��ď������݂��s��
	SetDrawScreen(m_gameScreenHandle);

	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	m_pBg->Draw();
	m_pPlayer->Draw();

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	// nullptr�ł͂Ȃ��`�F�b�N
		{
			m_pEnemy[i]->Draw();
		}
	}

	for (int i = 0; i < m_pShot.size(); i++)
	{
		// nullptr���ǂ������`�F�b�N����
		if (!m_pShot[i])	continue;// nullptr�Ȃ�ȍ~�̏����͍s��Ȃ�
		m_pShot[i]->Draw();
	}

	// �f�o�b�O�\��
	DrawString(8, 8, "SceneMain", GetColor(255, 255, 255));

	// �L�����N�^�[���f�o�b�O�\������
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"�v���C���[�̍��W(%.2f,%.2f)", playerPos.x, playerPos.y);

	// �e���������邩�\��
	int shotNum = 0;
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])	 shotNum++;
	}
	DrawFormatString(8, 40, GetColor(255, 255, 255), "ShotNum:%d", shotNum);

	// �o�b�N�o�b�t�@�ɏ������ސݒ�ɖ߂��Ă���
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[����ʂ��o�b�N�o�b�t�@�ɕ`�悷��
	int screenX = 0;
	int screenY = 0;

		if (m_shakeFrame > 0)
		{
			// ��ʗh��
			screenX = GetRand(8) - 4;
			screenY = GetRand(8) - 4;
		}

		// m_wipeFrame����`�悷��͈͂��v�Z����
		// m_wipeFrame�̓Q�[���J�n����0�A
		// ���t���[�����Z�����kWipeFrame(30)�܂ŕω�����
		// wipeRate ��m_wipeFrame�̕ω��ɍ��킹��0.0->1.0�ɕω�����

		float wipeRate = static_cast<float>(m_wipeFrame) / static_cast<float>(kWipeFrame);
		int wipeHeight = Game::kScreenHeight * wipeRate;

		// ��ʗh��
		//DrawRectGraph(screenX, screenY,
		//	0, 0, Game::kScreenWidth, wipeHeight,
		//	m_gameScreenHandle, true, false);

		// offset�̒l��wipe�̐i�s�ɍ��킹��320->0�ɕω���������
		// 0->320�ɕω�������̂͂킩��₷��	320*wipeRate

		int offset = 320 * (1.0 - wipeRate);

		// ��ʂ̏ォ��1���C�����`����s���Ă���

		// ���ɂႮ�ɂ�
		for (int y = 0; y < Game::kScreenHeight; y++)
		{
			int x = sinf(y*0.05f) * offset;
			DrawRectGraph(x, y,
				0, y, Game::kScreenWidth, 1,
				m_gameScreenHandle, true, false);
		}

	//	printfDx("rate:%f\n", wipeRate);

	// DrawGraph(0, 0, m_gameScreenHandle, true);
}

Vec2 SceneMain::GetNearEnemyPos(Vec2 pos) const
{
	// �G�����Ȃ��ꍇ�͓K���ȍ��W��Ԃ�
	Vec2 result{ 0,0 };
	// �ŏ��̓G�`�F�b�N�ς݃t���O
	bool isFirst = true;

	// ��ԋ߂��G�L�����N�^�[�̍��W��result�ɓ����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		// �g���Ă��Ȃ��G�̓`�F�b�N���Ȃ�
		if (!m_pEnemy[i])	continue;

		// �����ɂ��Ă��鎞�_��m_pEnemy[i]��nullptr�łȂ����Ƃ͊m��

		// ���łɏ����邱�Ƃ��m�肵�Ă���G�̓`�F�b�N���Ȃ�
		if (!m_pEnemy[i]->IsExist()) continue;

		// pos��m_pEnemy�̋������`�F�b�N����

		if (isFirst)
		{
			// ��̖ڂ̓G
			// �����������痣��Ă��悤�ƌ����_�ł͈�ԋ߂��G
			result = m_pEnemy[i]->GetPos();
			isFirst = false;
		}
		else
		{
			// 2�̖ڈȍ~�̓G
			// result�̒��ɂ͈�ԋ߂��G�̍��W�������Ă���

			// ���܂Ń`�F�b�N�������ň�ԋ߂��G�Ƃ̋���
			Vec2 toNear = result - pos;	// pos����b���ʂ̍��W�Ɍ������x�N�g��
			
			// �`�F�b�N����G�Ƃ̋���
			Vec2 toEnemy = m_pEnemy[i]->GetPos() - pos;	// pos����`�F�b�N���̓G�Ɍ������x�N�g��

			// �������y�����邽�ߋ����̔�r���s���ꍇ�͋����̓��Ŕ�r���s��
			if (toNear.sqLength() > toEnemy.sqLength())
			{
				// ���`�F�b�N���Ă���G�ւ̋������b���ʂ����Z���ꍇ
				// ���`�F�b�N���Ă���G���b���ʂ�
				result = m_pEnemy[i]->GetPos();
			}
			// �b���ʂ̕������`�F�b�N���Ă���G���߂��ꍇ�͉������Ȃ�
		}
	}

	// �S�Ă̓G�̃`�F�b�N���s�����̂ł�������ʂŊm��
	return result;
}

bool SceneMain::AddShot(ShotBase* pShot)
{
	// nullptr��n���ꂽ��~�܂�
	assert(pShot);

	for (int i = 0; i < m_pShot.size(); i++)
	{
		// �g�p���Ȃ玟�̃`�F�b�N��
		if (m_pShot[i])	continue;

		// �����ɗ����Ƃ������Ƃ�m_pShot[i] == nullptr
		m_pShot[i] = pShot;
		// �o�^������I��
		return true;
	}

	// �����ɗ����A�Ƃ�������m_pShot�Ƀ|�C���^��o�^�ł��Ȃ�����
	delete pShot;
	return false;
}

void SceneMain::CreateEnemyLeft()
{
	// �g���Ă��Ȃ�����T���Ă����ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i]) // nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			m_pEnemy[i] = new EnemyLeft;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	// ���������m�ۂł����ȍ~�̓`�F�b�N���Ȃ�
		}
	}
}

void SceneMain::CreateEnemyRight()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i]) // nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			m_pEnemy[i] = new EnemyRight;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	// ���������m�ۂł����ȍ~�̓`�F�b�N���Ȃ�
		}
	}
}

void SceneMain::CreateEnemyToPlayer()
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i]) // nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			// Base�������Ȃ��Ǝ��̊֐����Ăт���
			EnemyToPlayer* pEnemy = new EnemyToPlayer;
			
			pEnemy->Init();
			pEnemy->SetHandle(m_enemyHandle);
			pEnemy->SetPlayer(m_pPlayer);	// pPlayer��EnemyToPlayer�Ȃ̂ŌĂׂ�
			pEnemy->Start();

			// pEnemy�͂���������̂�m_pEnemy�Ɋm�ۂ����A�h���X���R�s�[���Ă���
			m_pEnemy[i] = pEnemy;

			/*
			m_pEnemy[i] = new EnemyToPlayer;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			// Player��ݒ肷��K�v������
			m_pEnemy[i]->setPlayer(m_pPlayer);
			m_pEnemy[i]->Start();
			*/
			return;	// ���������m�ۂł����ȍ~�̓`�F�b�N���Ȃ�
		}
	}
}
