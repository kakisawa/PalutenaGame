#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneStageSelect.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneGameOver.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneTitle)
{
	// �N���X�̃��������m�ۂ���
	m_pTitle = new SceneTitle;
	m_pStageSelect = new SceneStageSelect;
	m_pMain = new SceneMain;
	m_pClear = new SceneClear;
	m_pGameOver = new SceneGameOver;
}

SceneManager::~SceneManager()
{
	// �N���X�̃��������������
	delete m_pTitle;
	m_pTitle = nullptr;

	delete m_pStageSelect;
	m_pStageSelect = nullptr;

	delete m_pMain;
	m_pMain = nullptr;

	delete m_pClear;
	m_pClear = nullptr;

	delete m_pGameOver;
	m_pGameOver = nullptr;
}

void SceneManager::Init()
{
	// ���s����V�[���̏��������s��
	switch (m_runScene)
	{
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Init();
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		m_pStageSelect->Init();
		break;
		// �Q�[���V�[��
	case kSceneMain:
		m_pMain->Init();
		break;
		// �Q�[���N���A
	case kSceneClear:
		m_pClear->Init();
		break;
		// �Q�[���I�[�o�[
	case kSceneGameOver:
		m_pGameOver->Init();
		break;

	default:
		break;
	}
}

void SceneManager::End()
{
	// ���s����V�[�����I������
	switch (m_runScene)
	{
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->End();
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect: 
		m_pStageSelect->End();
		break;
		// �Q�[���V�[��
	case kSceneMain:
		m_pMain->End();
		break;
		// �Q�[���N���A
	case kSceneClear:
		m_pClear->End();
		break;
		// �Q�[���I�[�o�[
	case kSceneGameOver:
		m_pGameOver->End();
		break;

	default:
		break;
	}
}

void SceneManager::Update()
{
	Pad::Update();

	// ���s����V�[���̐؂�ւ����s��
	switch (m_runScene)
	{
		// �^�C�g���V�[��
	case kSceneTitle:
		if (m_pTitle->IsSceneEnd())
		{
			m_pTitle->End();
			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
		}
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		if (m_pStageSelect->IsSceneEnd())
		{
			m_pStageSelect->End();
			m_runScene = kSceneMain;
			m_pMain->Init();
		}
		break;
		// �Q�[���V�[��
	case kSceneMain:
		if (m_pMain->IsSceneGameOver())
		{
			m_pMain->End();
			m_runScene = kSceneGameOver;
			m_pGameOver->Init();
		}
		else if (m_pMain->IsSceneClear())
		{
			m_pMain->End();
			m_runScene = kSceneClear;
			m_pClear->Init();
		}
		break;
		// �Q�[���N���A
	case kSceneClear:
		if (m_pClear->IsSceneStageSelect())
		{
			m_pClear->End();
			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
		}
		break;
		// �Q�[���I�[�o�[�V�[��
	case kSceneGameOver:
		if (m_pGameOver->IsSceneSelect())
		{
			m_pGameOver->End();
			m_runScene = kSceneStageSelect;
			m_pTitle->Init();
		}
		break;
	}

	// ���s����V�[���̍X�V���s��
	switch (m_runScene)
	{
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Update();
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		m_pStageSelect->Update();
		break;
		// �Q�[���V�[��
	case kSceneMain:
		m_pMain->Update();
		break;
		// �Q�[���N���A
	case kSceneClear:
		m_pClear->Update();
		break;
		// �Q�[���I�[�o�[
	case kSceneGameOver:
		m_pGameOver->Update();
		break;
	default:
		break;
	}
}

void SceneManager::Draw()
{
	// ���s����V�[���̕`����s��
	switch (m_runScene)
	{
		// �^�C�g���V�[��
	case kSceneTitle:
		m_pTitle->Draw();
		break;
		// �X�e�[�W�I���V�[��
	case kSceneStageSelect:
		m_pStageSelect->Draw();
		break;
		// �Q�[���V�[��
	case kSceneMain:
		m_pMain->Draw();
		break;
		// �Q�[���N���A
	case kSceneClear:
		m_pClear->Draw();
		break;
		// �Q�[���I�[�o�[
	case kSceneGameOver:
		m_pGameOver->Draw();
		break;
	default:
		break;
	}
}
