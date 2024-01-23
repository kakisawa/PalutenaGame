#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "MozueyeEnemy.h"
#include "DeathYourEnemy.h"
#include "PumpkinEnemy.h"
#include "Shot/Shot.h"
#include "Time.h"
#include "Back.h"
#include "Game.h"
#include "Rect.h"
#include "Pad.h"

#include <cassert>

SceneMain::SceneMain() :
	m_isSceneEnd(false),
	m_fadeAlpha(255)		// �s�����ŏ�����
{
	// �Q�[����ʕ`���̐���
	// ��ʃT�C�Y�Ɠ����傫���̃O���t�B�b�N�f�[�^���쐬����
	m_gameScreenHandle = MakeScreen(kScreenWidth, kScreenHeight, true);

	// �O���t�B�b�N�̃��[�h
	m_playerHandle = LoadGraph("data/Player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/Fairy.png");
	assert(m_enemyHandle != -1);
	m_backHandle = LoadGraph("data/Map/Back.png");
	assert(m_backHandle != -1);

	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Player�ɃO���t�B�b�N�̃n���h����n��

	// �w�i�̃������m��
	m_pBack = new Back;
	m_pBack->SetHandle(m_backHandle);

	// �������Ԃ̃������m��
	m_pTime = new Time;

	m_pMozueyeEnemy.resize(MozuMax);
	m_pDeathYourEnemy.resize(DeathMax);
	m_pPumpkinEnemy.resize(PumpMax);

	// ������Ԃł̓��������m�ۂ��Ă��Ȃ����Ƃ�������悤�ɂ��Ă���
	// ���g�p��Ԃɂ��� nullptr�����Ă���
	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		m_pMozueyeEnemy[i] = nullptr;
	}
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		m_pDeathYourEnemy[i] = nullptr;
	}
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		m_pPumpkinEnemy[i] = nullptr;
	}
}

SceneMain::~SceneMain()
{
	// MakeScreen�ō쐬������O���t�B�b�N���폜����
	DeleteGraph(m_gameScreenHandle);

	// ����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_backHandle);

	// �������̉��
	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pBack;
	m_pBack = nullptr;

	delete m_pTime;
	m_pTime = nullptr;

	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		if (m_pMozueyeEnemy[i] != nullptr)
		{
			delete m_pMozueyeEnemy[i];
			m_pMozueyeEnemy[i] = nullptr;
		}
	}
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (m_pDeathYourEnemy[i] != nullptr)
		{
			delete m_pDeathYourEnemy[i];
			m_pDeathYourEnemy[i] = nullptr;
		}
	}
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		if (m_pPumpkinEnemy[i] != nullptr)
		{
			delete m_pPumpkinEnemy[i];
			m_pPumpkinEnemy[i] = nullptr;
		}
	}
}

void SceneMain::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr	�̏ꍇ�~�܂�

	m_isSceneEnd = false;

	m_pPlayer->Init();
	m_pBack->Init();
	m_pTime->Init();

	CreateEnemyMozu();
	CreateEnemyDeath();
	CreateEnemyPump();

	m_fadeAlpha = 255;
}

void SceneMain::Update()
{
	if (m_pPlayer->PlayerDeath() || m_pTime->TimeUp())
	{
		// A�{�^���������ꂽ��Q�[���I�[�o�[��ʂ֑J�ڂ���
		if (Pad::IsTrigger(PAD_INPUT_4))	  // A�{�^���������ꂽ
		{
			m_isSceneEnd = true;

			// �t�F�[�h�A�E�g
			m_fadeAlpha += 8;
			if (m_fadeAlpha < 255)
			{
				m_fadeAlpha = 255;
			}
		}
		m_pPlayer->Update();
		m_pPlayer->Death();
		Death();

		return;
	}

	// �t�F�[�h�C��
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	m_pBack->Update();
	m_pPlayer->Update();
	m_pTime->Update();


	// �e�Ƃ̓����蔻��
	for (int j = 0; j < kShotMax; j++)
	{
		// nullptr�Ȃ珈���͍s��Ȃ�
		if (!m_pShot[j])	continue;

		m_pShot[j]->Update();
		// ��ʊO�ɏo���烁�������
		if (!m_pShot[j]->IsExist())
		{
			delete m_pShot[j];
			m_pShot[j] = nullptr;
		}
	}

	Rect playerRect = m_pPlayer->GetColRect();
	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		if (m_pMozueyeEnemy[i])
		{
			m_pMozueyeEnemy[i]->Update();
			m_pPlayer->SetMozu(m_pMozueyeEnemy[i]);

			// ���݂��Ă���G�ƃv���C���[�̓����蔻��
			if (m_pMozueyeEnemy[i]->isExist()) {
				Rect enemyRect = m_pMozueyeEnemy[i]->GetColRect();
				if (playerRect.IsCollsion(enemyRect))
				{
					m_pPlayer->OnDamage_Mozu();
					m_pMozueyeEnemy[i]->OnDamage();
				}

				// �e�Ƃ̓����蔻��
				for (int shotIndex = 0; shotIndex < kShotMax; shotIndex++)
				{
					// nullptr�Ȃ珈���͍s��Ȃ�
					if (!m_pShot[shotIndex])	continue;

					if (m_pShot[shotIndex]->IsExist()) {
						// ���݂��Ă���G�Ƃ̓����蔻��
						Rect shotRect = m_pShot[shotIndex]->GetColRect();
						if (shotRect.IsCollsion(enemyRect))
						{
							m_pMozueyeEnemy[i]->OnDamage();
							m_pShot[shotIndex]->colShot();
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (m_pDeathYourEnemy[i])
		{
			m_pDeathYourEnemy[i]->Update();
			m_pPlayer->SetDeath(m_pDeathYourEnemy[i]);

			// ���݂��Ă���G�ƃv���C���[�̓����蔻��
			if (m_pDeathYourEnemy[i]->isExist()) {
				Rect enemyRect = m_pDeathYourEnemy[i]->GetColRect();
				if (playerRect.IsCollsion(enemyRect))
				{
					m_pPlayer->OnDamage_Death();
					m_pDeathYourEnemy[i]->OnDamage();
				}

				// �e�Ƃ̓����蔻��
				for (int shotIndex = 0; shotIndex < kShotMax; shotIndex++)
				{
					// nullptr�Ȃ珈���͍s��Ȃ�
					if (!m_pShot[shotIndex])	continue;

					if (m_pShot[shotIndex]->IsExist()) {
						// ���݂��Ă���G�Ƃ̓����蔻��
						Rect shotRect = m_pShot[shotIndex]->GetColRect();
						if (shotRect.IsCollsion(enemyRect))
						{
							m_pDeathYourEnemy[i]->OnDamage();
							m_pShot[shotIndex]->colShot();
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		if (m_pPumpkinEnemy[i])
		{
			m_pPumpkinEnemy[i]->SetPlayer(m_pPlayer);

			m_pPumpkinEnemy[i]->Update();
			m_pPlayer->SetPump(m_pPumpkinEnemy[i]);

			// ���݂��Ă���G�ƃv���C���[�̓����蔻��
			if (m_pPumpkinEnemy[i]->isExist()) {
				Rect enemyRect = m_pPumpkinEnemy[i]->GetColRect();
				if (playerRect.IsCollsion(enemyRect))
				{
					m_pPlayer->OnDamage_Pump();
					m_pPumpkinEnemy[i]->OnDamage();
				}

				// �e�Ƃ̓����蔻��
				for (int shotIndex = 0; shotIndex < kShotMax; shotIndex++)
				{
					// nullptr�Ȃ珈���͍s��Ȃ�
					if (!m_pShot[shotIndex])	continue;

					if (m_pShot[shotIndex]->IsExist()) {
						// ���݂��Ă���G�Ƃ̓����蔻��
						Rect shotRect = m_pShot[shotIndex]->GetColRect();
						if (shotRect.IsCollsion(enemyRect))
						{
							m_pPumpkinEnemy[i]->OnDamage();
							m_pShot[shotIndex]->colShot();
						}
					}
				}
			}
		}
	}
}

void SceneMain::Draw()
{
	//// �����Ő��������O���t�B�b�N�f�[�^�ɑ΂��ď������݂��s��
	//SetDrawScreen(m_gameScreenHandle);

	//// �`���X�N���[�����N���A����
	//ClearDrawScreen();

	m_pBack->Draw();
	m_pPlayer->Draw();
	m_pPlayer->Death();
	m_pTime->Draw();

	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		if (m_pMozueyeEnemy[i]) {
			m_pMozueyeEnemy[i]->EnemyBase::Draw();
		}
	}
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (m_pDeathYourEnemy[i])
		{
			m_pDeathYourEnemy[i]->EnemyBase::Draw();
		}
	}
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		if (m_pPumpkinEnemy[i])
		{
			m_pPumpkinEnemy[i]->EnemyBase::Draw();
		}
	}

	// �e�`��
	for (int i = 0; i < kShotMax; i++)
	{
		// nullptr���ǂ������`�F�b�N����
		if (!m_pShot[i])	continue;// nullptr�Ȃ�ȍ~�̏����͍s��Ȃ�
		m_pShot[i]->Draw();
	}

	DrawGraph(0, 0, m_gameScreenHandle, true);

	// �o�b�N�o�b�t�@�ɏ������ސݒ�ɖ߂��Ă���
	//SetDrawScreen(DX_SCREEN_BACK);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneMain::Death()
{
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 128);

	SetFontSize(32);
	DrawString(kScreenWidth * 0.5 - 100, kScreenHeight * 0.5 - 100, "���񂶂����...", GetColor(255, 255, 255));
	SetFontSize(16);
	DrawString(kScreenWidth * 0.5 - 80, kScreenHeight * 0.5 - 65, "A�L�[�������Ă�������", GetColor(255, 255, 255));
}

void SceneMain::End()
{
}

bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

bool SceneMain::AddShot(Shot* pShot)
{
	// nullptr��n���ꂽ��~�܂�
	assert(pShot);

	for (int i = 0; i < kShotMax; i++)
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

void SceneMain::CreateEnemyMozu()
{
	// �G�̃������m��
	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		if (!m_pMozueyeEnemy[i])	// nullptr�ł��邱�Ƃ��`�F�b�N
		{
			m_pMozueyeEnemy[i] = new MozueyeEnemy;
			m_pMozueyeEnemy[i]->Init();
			m_pMozueyeEnemy[i]->Start();
			return;
		}
	}
}

void SceneMain::CreateEnemyDeath()
{
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (!m_pDeathYourEnemy[i])	// nullptr�ł��邱�Ƃ��`�F�b�N
		{
			m_pDeathYourEnemy[i] = new DeathYourEnemy;
			m_pDeathYourEnemy[i]->Init();
			m_pDeathYourEnemy[i]->Start();
			return;
		}
	}
}

void SceneMain::CreateEnemyPump()
{
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		m_pPumpkinEnemy[i] = new PumpkinEnemy;
		m_pPumpkinEnemy[i]->Init();
		m_pPumpkinEnemy[i]->Start();
		return;
	}
}
