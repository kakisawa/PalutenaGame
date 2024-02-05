#include "SceneExplanation.h"
#include "SoundManager.h"
#include "Player.h"
#include "DeathYourEnemy.h"
#include "Shot/Shot.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include <cassert>

namespace
{
	// �����̕\���ʒu
	constexpr int kSelectChirPosX = kScreenWidth * 0.4;
	constexpr int kSelectChirPosY = kScreenHeight * 0.8;

	// �X�N���[���ړ���
	constexpr float backGround_scale = 1.2f;
	// �w�i�̊g�嗦
	constexpr int kBgScale = 1;
}

SceneExplanation::SceneExplanation():
	m_isSceneEnd(false),
	m_fadeAlpha(255)
{
	// �Q�[����ʕ`���̐���
	// ��ʃT�C�Y�Ɠ����傫���̃O���t�B�b�N�f�[�^���쐬����
	m_gameScreenHandle = MakeScreen(kScreenWidth, kScreenHeight, true);

	// �������m��
	m_pSoundManager = new SoundManager;

	// �O���t�B�b�N�̃��[�h
	m_playerHandle = LoadGraph("data/Player.png");
	assert(m_playerHandle != -1);

	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Player�ɃO���t�B�b�N�̃n���h����n��

	m_pDeathYourEnemy.resize(DeathMax);
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		m_pDeathYourEnemy[i] = nullptr;
	}
}

SceneExplanation::~SceneExplanation()
{
	// MakeScreen�ō쐬������O���t�B�b�N���폜����
	DeleteGraph(m_gameScreenHandle);
	// ����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);


	// ���������
	delete m_pPlayer;
	m_pPlayer = nullptr;
	for (int i = 0; i < m_pDeathYourEnemy.size(); i++)
	{
		if (m_pDeathYourEnemy[i] != nullptr)
		{
			delete m_pDeathYourEnemy[i];
			m_pDeathYourEnemy[i] = nullptr;
		}
	}
	delete m_pSoundManager;
	m_pSoundManager = nullptr;
}

void SceneExplanation::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr	�̏ꍇ�~�܂�

	m_pPlayer->Init();
	//�T�E���h�}�l�[�W���[�̏�����
	m_pSoundManager->Init();

	Graph = LoadGraph("data/Explanation.png");
	BgGraph = LoadGraph("data/Map/patter2.png");
	m_isSceneEnd = false;
	m_fadeAlpha = 255;
}

void SceneExplanation::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		m_isSceneEnd = true;

		m_pSoundManager->SoundButton();
	}

	// �w�i�X�N���[��
	m_scrollX += backGround_scale;

	// �t�F�[�h�C��
	if (m_isSceneEnd)
	{
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}

	m_pPlayer->Update();

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
}

void SceneExplanation::Draw()
{
	DrawGraph(0, 0, m_gameScreenHandle, true);

	BackDraw();

	SetFontSize(64);
	DrawString(kSelectChirPosX, kSelectChirPosY, "A�{�^���Ń^�C�g���ɖ߂�", 0xffffff);

	// �t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);	// �������ŕ\���J�n
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����ɖ߂��Ă���
}

void SceneExplanation::BackDraw()
{
	Size bg1Size;
	GetGraphSize(BgGraph, &bg1Size.width, &bg1Size.height);

	// �X�N���[���ʂ��v�Z
	int scrollBg = static_cast<int>(m_scrollX) % static_cast<int>(bg1Size.width * kBgScale);

	for (int index = 0; index < 4; index++)
	{
		DrawRotaGraph2(-scrollBg + index * bg1Size.width * kBgScale,
			kScreenHeight - bg1Size.height * kBgScale,
			0, 0,
			kBgScale, 0.0f,
			BgGraph, true);
	}
}

void SceneExplanation::End()
{
	// �w�i������������폜
	DeleteGraph(Graph);

	m_pSoundManager->End();
}

bool SceneExplanation::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
