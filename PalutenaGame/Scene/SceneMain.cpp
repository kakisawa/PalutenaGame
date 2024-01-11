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

SceneMain::SceneMain()
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

	m_mozueyeEnemy = LoadGraph("data/Fairy.png");
	assert(m_mozueyeEnemy != -1);
	m_deathYourEnemyGraph = LoadGraph("data/Fairy2.png");
	assert(m_deathYourEnemyGraph != -1);
	m_pumpkinEnemyGraph = LoadGraph("data/Fairy3.png");
	assert(m_pumpkinEnemyGraph != -1);


	// �v���C���[�̃������m��
	m_pPlayer = new Player{ this };
	m_pPlayer->SetHandle(m_playerHandle);	// Player�ɃO���t�B�b�N�̃n���h����n��

	// �w�i�̃������m��
	m_pBack = new Back;
	m_pBack->SetHandle(m_backHandle);

	// �G�̃������m��
	m_pMozueyeEnemy = new MozueyeEnemy;
	m_pMozueyeEnemy->SetHandle(m_mozueyeEnemy);
	m_pDeathYourEnemy = new DeathYourEnemy;
	m_pDeathYourEnemy->SetHandle(m_deathYourEnemyGraph);
	m_pPumpkinEnemy = new PumpkinEnemy;
	m_pPumpkinEnemy->SetHandle(m_pumpkinEnemyGraph);


}

SceneMain::~SceneMain()
{
	// MakeScreen�ō쐬������O���t�B�b�N���폜����
	DeleteGraph(m_gameScreenHandle);

	// ����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_backHandle);

	DeleteGraph(m_mozueyeEnemy);
	DeleteGraph(m_deathYourEnemyGraph);
	DeleteGraph(m_pumpkinEnemyGraph);

	// �������̉��
	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pBack;
	m_pBack = nullptr;

	delete m_pMozueyeEnemy;
	m_pMozueyeEnemy = nullptr;
	delete m_pDeathYourEnemy;
	m_pDeathYourEnemy = nullptr;
	delete m_pPumpkinEnemy;
	m_pPumpkinEnemy = nullptr;
}

void SceneMain::Init()
{
	assert(m_pPlayer);	// m_pPlayer == nullptr	�̏ꍇ�~�܂�

	m_pPlayer->Init();
	m_pBack->Init();

	m_pMozueyeEnemy->Init();
	m_pDeathYourEnemy->Init();
	m_pPumpkinEnemy->Init();
}

void SceneMain::Update()
{
	Pad::Update();

	m_pBack->Update();
	m_pPlayer->Update();

	m_pMozueyeEnemy->Update();
	m_pDeathYourEnemy->Update();
	m_pPumpkinEnemy->Update();

}

void SceneMain::Draw()
{
	// �����Ő��������O���t�B�b�N�f�[�^�ɑ΂��ď������݂��s��
	SetDrawScreen(m_gameScreenHandle);

	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	m_pBack->Draw();
	m_pPlayer->Draw();

	m_pMozueyeEnemy->Draw();
	m_pDeathYourEnemy->Draw();
	m_pPumpkinEnemy->Draw();

	// �o�b�N�o�b�t�@�ɏ������ސݒ�ɖ߂��Ă���
	SetDrawScreen(DX_SCREEN_BACK);

	DrawGraph(0, 0, m_gameScreenHandle, true);
}

void SceneMain::End()
{
}

bool SceneMain::IsSceneEnd() const
{
	
}
