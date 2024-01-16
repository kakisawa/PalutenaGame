#include "DxLib.h"
#include "SceneMain.h"
#include "Player.h"
#include "MozueyeEnemy.h"
#include "DeathYourEnemy.h"
#include "PumpkinEnemy.h"
#include "Back.h"
#include "Game.h"
#include "Rect.h"
#include "Pad.h"

#include <cassert>

SceneMain::SceneMain() :
	m_isSceneEnd(false)
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

	// �G�̃������m��
	for (int i = 0; i < MozuMax; i++)
	{
		m_pMozueyeEnemy[i] = new MozueyeEnemy;
	}
	for (int i = 0; i < DeathMax; i++)
	{
		m_pDeathYourEnemy[i] = new DeathYourEnemy;
	}
	for (int i = 0; i < PumpMax; i++)
	{
		m_pPumpkinEnemy[i] = new PumpkinEnemy;
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
	for (int i = 0; i < MozuMax; i++)
	{
		delete m_pMozueyeEnemy;
		m_pMozueyeEnemy[i] = nullptr;
	}

	for (int i = 0; i < DeathMax; i++)
	{
		delete m_pDeathYourEnemy;
		m_pDeathYourEnemy[i] = nullptr;
	}

	for (int i = 0; i < PumpMax; i++)
	{
		delete m_pPumpkinEnemy;
		m_pPumpkinEnemy[i] = nullptr;
	}
}

void SceneMain::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr	�̏ꍇ�~�܂�

	m_isSceneEnd = false;

	m_pPlayer->Init();
	m_pBack->Init();

	for (int i = 0; i < MozuMax; i++)
	{
		m_pMozueyeEnemy[i]->Init();
	}
	for (int i = 0; i < DeathMax; i++)
	{
		m_pDeathYourEnemy[i]->Init();
	}
	for (int i = 0; i < PumpMax; i++)
	{
		m_pPumpkinEnemy[i]->Init();
	}
}

void SceneMain::Update()
{
	if (m_pPlayer->PlayerDeath())
	{
		// A�{�^���������ꂽ��Q�[���I�[�o�[��ʂ֑J�ڂ���
		if (Pad::IsTrigger(PAD_INPUT_4))	  // A�{�^���������ꂽ
		{
			m_isSceneEnd = true;
		}
		m_pPlayer->Update();
		m_pPlayer->Death();

		return;
	}

	m_pPlayer->Update();
	m_pBack->Update();


	Rect playerRect = m_pPlayer->GetColRect();
	for (int i = 0; i < MozuMax; i++)
	{
		m_pMozueyeEnemy[i]->Update();

		// ���݂��Ă���G�ƃv���C���[�̓����蔻��
		Rect enemyRect = m_pMozueyeEnemy[i]->GetColRect();
		if (playerRect.IsCollsion(enemyRect))
		{
			m_pPlayer->OnDamage();
		}
	}

	for (int i = 0; i < DeathMax; i++)
	{
		m_pDeathYourEnemy[i]->Update();

		// ���݂��Ă���G�ƃv���C���[�̓����蔻��
		Rect enemyRect = m_pDeathYourEnemy[i]->GetColRect();
		if (playerRect.IsCollsion(enemyRect))
		{
			m_pPlayer->OnDamage();
		}
	}
	for (int i = 0; i < PumpMax; i++)
	{
		m_pPumpkinEnemy[i]->Update();

		// ���݂��Ă���G�ƃv���C���[�̓����蔻��
		Rect enemyRect = m_pPumpkinEnemy[i]->GetColRect();
		if (playerRect.IsCollsion(enemyRect))
		{
			m_pPlayer->OnDamage();
		}
	}
	return;
}

void SceneMain::Draw()
{
	// �����Ő��������O���t�B�b�N�f�[�^�ɑ΂��ď������݂��s��
	SetDrawScreen(m_gameScreenHandle);

	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	m_pBack->Draw();
	m_pPlayer->Draw();
	m_pPlayer->Death();

	for (int i = 0; i < MozuMax; i++)
	{
		m_pMozueyeEnemy[i]->EnemyBase::Draw();
	}
	for (int i = 0; i < DeathMax; i++)
	{
		m_pDeathYourEnemy[i]->EnemyBase::Draw();
	}
	for (int i = 0; i < PumpMax; i++)
	{
		m_pPumpkinEnemy[i]->EnemyBase::Draw();
	}

	// �o�b�N�o�b�t�@�ɏ������ސݒ�ɖ߂��Ă���
	SetDrawScreen(DX_SCREEN_BACK);

	DrawGraph(0, 0, m_gameScreenHandle, true);
}

void SceneMain::End()
{
}

bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd;
}
