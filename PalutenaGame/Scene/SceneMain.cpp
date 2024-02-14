#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "MozueyeEnemy.h"
#include "DeathYourEnemy.h"
#include "PumpkinEnemy.h"
#include "Shot/Shot.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "ColorManager.h"
#include "Pause.h"
#include "Time.h"
#include "Back.h"
#include "Game.h"
#include "Rect.h"
#include "Pad.h"

#include <cassert>

namespace {
	constexpr int ExplanationX = kScreenWidth * 0.07f;
	constexpr int ExplanationY = kScreenHeight * 0.07f;
}

SceneMain::SceneMain() :
	m_isSceneEnd(false),
	isToGameClear(false),
	isToGameOver(false),
	m_fadeAlpha(255),		// �s�����ŏ�����
	m_enemyInterval(0),
	m_startCount(180),
	m_isStartFlag(false),
	m_isStartCountFlag(false)
{
	// �Q�[����ʕ`���̐���
	// ��ʃT�C�Y�Ɠ����傫���̃O���t�B�b�N�f�[�^���쐬����
	m_gameScreenHandle = MakeScreen(kScreenWidth, kScreenHeight, true);

	// �O���t�B�b�N�̃��[�h
	m_playerHandle = LoadGraph("data/Player.png");
	assert(m_playerHandle != -1);
	m_backHandle = LoadGraph("data/Map/Back1.png");
	assert(m_backHandle != -1);
	m_backHandle2 = LoadGraph("data/Map/Ground.png");
	assert(m_backHandle2 != -1);
	m_explanation = LoadGraph("data/explanation2.png");
	assert(m_explanation != -1);
	m_key_A = LoadGraph("data/pxkb_a.png");
	assert(m_key_A != -1);
	m_count1= LoadGraph("data/Count1.png");
	assert(m_count1 != -1);
	m_count2 = LoadGraph("data/Count2.png");
	assert(m_count2 != -1);
	m_count3 = LoadGraph("data/Count3.png");
	assert(m_count3 != -1);

	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Player�ɃO���t�B�b�N�̃n���h����n��

	// �w�i�̃������m��
	m_pBack = new Back;
	m_pBack->SetHandle(m_backHandle);
	m_pBack->SetHandle2(m_backHandle2);

	// �������Ԃ̃������m��
	m_pTime = new Time;
	// SE/BGM�������m��
	m_pSoundManager = new SoundManager;
	// �F�������m��
	m_pColorManager = new ColorManager;
	// �|�[�Y
	m_pPause = new Pause(m_pSoundManager);

	m_pMozueyeEnemy.resize(MozuMax);
	m_pDeathYourEnemy.resize(DeathMax);
	m_pPumpkinEnemy.resize(PumpMax);

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
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
	// �F���������
	delete m_pColorManager;
	m_pColorManager = nullptr;
	// �|�[�Y
	delete m_pPause;
	m_pPause = nullptr;

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

	isToGameClear = false;
	isToGameOver = false;
	m_isSceneEnd = false;
	m_isStartFlag = false;
	m_isStartCountFlag = false;

	m_pPlayer->Init();
	m_pBack->Init();
	m_pTime->Init();
	m_pSoundManager->Init();

	m_fadeAlpha = 255;
	m_enemyInterval = 0;
	m_startCount = 180;

	m_pSoundManager->BGMButtle();
	m_pPause->Init();
}

void SceneMain::Update()
{
	m_pBack->Update();
	m_pPause->Update();
	m_pSoundManager->SetBgmVolume();
	m_pSoundManager->SetSeVolume();

	// �t�F�[�h�C��
	m_fadeAlpha -= 8;
	if (m_fadeAlpha < 0)
	{
		m_fadeAlpha = 0;
	}

	if (m_isStartFlag == true)
	{
		if (m_startCount <= 0)
		{
			m_isStartCountFlag = true;
			m_startCount = 0;
		}
		m_startCount--;
	}

	if (m_isStartFlag == false)
	{
		if (Pad::IsTrigger(PAD_INPUT_4)) {

			m_isStartFlag = true;
		}
	}
	else if (m_isStartCountFlag)
	{
		if (!m_pPause->GetPauseFlag())
		{
			// �v���C���[�����S������(�Q�[���I�[�o�[)
			if (m_pPlayer->PlayerDeath())
			{
				Death();
				m_pPlayer->Death();
			}
			else {
				// �������Ԃ��I�������(�Q�[���N���A)
				if (m_pTime->TimeUp()) {
					Clear();
				}

				m_pPlayer->Update();
				m_pTime->Update();

				Rect playerRect = m_pPlayer->GetColRect();

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
				// ���Y�A�C�����蔻�蓙
				for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
				{
					if (m_pMozueyeEnemy[i])
					{
						m_pMozueyeEnemy[i]->Update();
						m_pPlayer->SetMozu(m_pMozueyeEnemy[i]);

						// �g�p�ς݂̓G���폜
						if (!m_pMozueyeEnemy[i]->isExist())
						{
							delete m_pMozueyeEnemy[i];
							m_pMozueyeEnemy[i] = nullptr;
						}
						else {			// ���݂��Ă���G�ƃv���C���[�̓����蔻��
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
				// �������蔻�蓙
				for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
				{
					if (m_pDeathYourEnemy[i])
					{
						m_pDeathYourEnemy[i]->Update();
						m_pPlayer->SetDeath(m_pDeathYourEnemy[i]);

						// �g�p�ς݂̓G���폜
						if (!m_pDeathYourEnemy[i]->isExist())
						{
							delete m_pDeathYourEnemy[i];
							m_pDeathYourEnemy[i] = nullptr;
						}
						else {			// ���݂��Ă���G�ƃv���C���[�̓����蔻��
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
				// �p���v�L�������蔻�蓙
				for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
				{

					if (m_pPumpkinEnemy[i])
					{
						//m_pPumpkinEnemy[i]->SetPlayer(m_pPlayer);
						m_pPumpkinEnemy[i]->Update();
						m_pPlayer->SetPump(m_pPumpkinEnemy[i]);

						// �g�p�ς݂̓G���폜
						if (!m_pPumpkinEnemy[i]->isExist())
						{
							delete m_pPumpkinEnemy[i];
							m_pPumpkinEnemy[i] = nullptr;
						}
						else
						{		// ���݂��Ă���G�ƃv���C���[�̓����蔻��
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

				//�G�L�����N�^�[�̓o��
				m_enemyInterval++;
				if (m_enemyInterval >= kEnemyInterval)
				{
					m_enemyInterval = 0;
					// �����_���ɐ�������G��I��
					switch (GetRand(2))
					{
					case 0:
						CreateEnemyMozu();
						break;
					case 1:
						CreateEnemyDeath();
						break;
					case 2:
						CreateEnemyPump();
						break;
					}
				}
			}
		}
	}
}


void SceneMain::Draw()
{
	DrawGraph(0, 0, m_gameScreenHandle, true);

	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	m_pBack->DrawBg();			// �w�i�`��
	m_pTime->Draw();			// �������ԕ`��
	m_pBack->DrawGround();		// �w�i�n�ʕ`��
	CharactorDraw();			// �v���C���[�E�G�l�~�[�`��

	// �e�`��
	for (int i = 0; i < kShotMax; i++)
	{
		if (!m_pShot[i])	continue;
		m_pShot[i]->Draw();
	}

	
	m_pPause->Draw();			// �|�[�Y��ʕ`��

	CoundownDraw();				// �Q�[���J�n�O�̃J�E���g�_�E���`��
	StartDraw();				// �Q�[���J�n�O�̐����`��

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight,
		m_pColorManager->GetColorBlack(), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneMain::End()
{
	// �v���C���[���l�������X�R�A�𑼂̃V�[���ɓ����
	SceneManager::s_ResultScore = m_pPlayer->GetScore();

	// �e�Ƃ̓����蔻��
	for (int j = 0; j < kShotMax; j++)
	{
		delete m_pShot[j];
		m_pShot[j] = nullptr;
	}

	// �G�l�~�[�̉��
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

	// �T�E���h�̉��
	m_pSoundManager->End();
}

void SceneMain::CharactorDraw()
{
	// �v���C���[�̕`��
	if (m_pPlayer->PlayerDeath())
	{
		m_pPlayer->Death();
		Death();
	}
	if (m_pTime->TimeUp())
	{
		Clear();
	}
	m_pPlayer->Draw();

	// �G�l�~�[�̕`��
	for (int i = 0; i < m_pMozueyeEnemy.size(); i++)
	{
		if (m_pMozueyeEnemy[i]) {
			m_pMozueyeEnemy[i]->Draw();
		}
	}
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (m_pDeathYourEnemy[i])
		{
			m_pDeathYourEnemy[i]->Draw();
		}
	}
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		if (m_pPumpkinEnemy[i])
		{
			m_pPumpkinEnemy[i]->Draw();
		}
	}
}

void SceneMain::StartDraw()
{
	if (m_isStartFlag == false)
	{
		DrawExtendGraph(ExplanationX, ExplanationY,
			ExplanationX + kScreenWidth * 0.85f, ExplanationY + kScreenHeight * 0.85f,
			m_explanation, false);
		DrawExtendGraph((ExplanationX + kScreenWidth * 0.8f) - 65, (ExplanationY + kScreenHeight * 0.8f) - 75,
			ExplanationX + kScreenWidth * 0.83f, ExplanationY + kScreenHeight * 0.83f,
			m_key_A, true);
	}
}

void SceneMain::CoundownDraw()
{
	if(m_startCount>=121)
	{
		DrawExtendGraph(kScreenWidth * 0.5f - 100, kScreenHeight * 0.5f - 100,
			kScreenWidth * 0.5f+100, kScreenHeight * 0.5f+100,
			m_count3, true);
	}
	else if (m_startCount <= 120 && m_startCount >= 61)
	{
		DrawExtendGraph(kScreenWidth * 0.5f - 100, kScreenHeight * 0.5f - 100,
			kScreenWidth * 0.5f+100, kScreenHeight * 0.5f+100,
			m_count2, true);
	}
	else if (m_startCount <= 60 && m_startCount >= 1)
	{
		DrawExtendGraph(kScreenWidth * 0.5f - 100, kScreenHeight * 0.5f - 100,
			kScreenWidth * 0.5f+100, kScreenHeight * 0.5f+100,
			m_count1, true);
	}
}

void SceneMain::Clear()
{
	StopSoundMem(m_pSoundManager->m_bgmButtle);

	m_isSceneEnd = true;
	isToGameClear = true;

	// �t�F�[�h�A�E�g
	m_fadeAlpha += 1;
	if (m_fadeAlpha < 255)
	{
		m_fadeAlpha = 255;
	}
}

void SceneMain::Death()
{
	m_isSceneEnd = true;
	isToGameOver = true;

	// �t�F�[�h�A�E�g
	m_fadeAlpha += 8;
	if (m_fadeAlpha < 255)
	{
		m_fadeAlpha = 255;
	}
}

bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

bool SceneMain::ToGameOver() const
{
	return isToGameOver;
}

bool SceneMain::ToGameClear() const
{
	return isToGameClear;
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
			m_pMozueyeEnemy[i]->Init(m_pPlayer);
			m_pMozueyeEnemy[i]->Start(kScreenWidth * 0.3, Ground - 32 * 0.5);
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
			m_pDeathYourEnemy[i]->Init(m_pPlayer);
			m_pDeathYourEnemy[i]->Start(kScreenWidth * 0.5f, kScreenHeight * 0.5f);
			return;
		}
	}
}

void SceneMain::CreateEnemyPump()
{
	for (int i = 0; i < m_pPumpkinEnemy.size(); i++)
	{
		if (!m_pPumpkinEnemy[i])
		{
			m_pPumpkinEnemy[i] = new PumpkinEnemy;
			m_pPumpkinEnemy[i]->Init(m_pPlayer);

			int EnemyX = kScreenWidth * 0.3f;
			/*switch (GetRand(2))
			{
			case 0:
				EnemyX = kScreenWidth * 0.1;
				break;
			case 1:
				EnemyX = kScreenWidth * 0.9;
				break;
			case 2:
				EnemyX = kScreenWidth * 0.5;
				break;
			}*/
			//m_pPumpkinEnemy[i]->Start(EnemyX, kScreenHeight * 0.5f);
			m_pPumpkinEnemy[i]->Start(EnemyX, kScreenHeight * 0.7f);
			return;
		}
	}
}
