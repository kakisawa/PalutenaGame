#include "SceneManager.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneGameOver.h"
#include "SceneStageSelect.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneKindTitle),
	m_pTitle(),			// �N���X�̏���������()�̒��ɃR���X�g���N�^�̈���������
	m_pStageSelect(),
	m_pMain(),
	m_pGameOver()
{
	// �������m��
	m_pTitle = new SceneTitle;
	m_pStageSelect = new SceneStageSelect;
	m_pMain = new SceneMain;
	m_pGameOver = new SceneGameOver;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	// ����������
		// ���s�������V�[���̏��������s��
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_pTitle->Init();
		break;
	case kSceneStageSelect:
		m_pStageSelect->Init();
		break;
	case kSceneKindMain:
		m_pMain->Init();
		break;
	case kSceneKindGameOver:
		m_pGameOver->Init();
	default:
		break;
	}
}

void SceneManager::Update()
{
	Pad::Update();

	switch (m_runScene)
	{
	case kSceneKindTitle:
		// �^�C�g����ʂ̏I�����`�F�b�N
		if (m_pTitle->IsSceneEnd())
		{
			m_pTitle->End();

			m_runScene = kSceneStageSelect;
			m_pStageSelect->Init();
		}
		break;
	case kSceneStageSelect:
		if (m_pStageSelect->IsSceneEnd())
		{
			m_runScene = kSceneKindMain;	// ���̃t���[���ȍ~�A���s�������V�[��
			m_pMain->Init();		// �ύX��V�[���̏�����
		}
		else if (m_pStageSelect->IsSceneEnd2()) {
			//	m_runScene = kSceneKindMain;	// ���̃t���[���ȍ~�A���s�������V�[��
			//	m_pMain->Init();		// �ύX��V�[���̏�����
			//}
		}
		else if (m_pStageSelect->IsSceneEnd3()) {
			m_runScene = kSceneKindTitle;	// ���̃t���[���ȍ~�A���s�������V�[��
			m_pTitle->Init();
		}
		break;
	case kSceneKindMain:
		// �I�����Ă�����SceneResult�ɐ؂�ւ���
		if (m_pMain->IsSceneEnd())
		{
			// �V�[����؂�ւ���
			m_pMain->End();	// ���s���Ă����V�[���̏I������

			m_runScene = kSceneKindGameOver;	// ���̃t���[���ȍ~�A���s�������V�[��
			m_pGameOver->Init();
		}
		break;
	case kSceneKindGameOver:
		if (m_pGameOver->IsSceneEnd())
		{
			// �V�[����؂�ւ���
			m_pGameOver->End();	// ���s���Ă����V�[���̏I������

			m_runScene = kSceneKindTitle;	// ���̃t���[���ȍ~�A���s�������V�[��
			m_pTitle->Init();
		}
		break;
	default:
		break;
	}

	// �e�V�[���̍X�V���s��
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_pTitle->Update();
		break;
	case kSceneStageSelect:
		m_pStageSelect->Update();
		break;
	case kSceneKindMain:
		m_pMain->Update();
		break;
	case kSceneKindGameOver:
		m_pGameOver->Update();
	default:
		break;
	}
}

void SceneManager::Draw()
{
	// �e�V�[���̍X�V���s��
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_pTitle->Draw();
		break;
	case kSceneStageSelect:
		m_pStageSelect->Draw();
		break;
	case kSceneKindMain:
		m_pMain->Draw();
		break;
	case kSceneKindGameOver:
		m_pGameOver->Draw();
	default:
		break;
	}
}

void SceneManager::End()
{
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_pTitle->End();
		break;
	case kSceneStageSelect:
		m_pStageSelect->End();
		break;
	case kSceneKindMain:
		m_pMain->End();
		break;
	case kSceneKindGameOver:
		m_pGameOver->End();
	default:
		break;
	}
}
