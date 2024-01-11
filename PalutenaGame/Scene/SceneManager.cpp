#include "SceneManager.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"

SceneManager::SceneManager():
	m_runScene(kSceneKindTitle),
	m_pTitle(),			// �N���X�̏���������()�̒��ɃR���X�g���N�^�̈���������
	m_pMain()
{
	// �������m��
	m_pTitle = new SceneTitle;
	m_pMain = new SceneMain;
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
	case kSceneKindMain:
		m_pMain->Init();
		break;
	default:
		break;
	}
}

void SceneManager::Update()
{
	switch (m_runScene)
	{
	case kSceneKindTitle:
		// �^�C�g����ʂ̏I�����`�F�b�N
		if (m_pTitle->IsSceneEnd())
		{
			m_pTitle->End();

			// �Q�[���V�[���֑J��
			m_runScene = kSceneKindMain;	// ���̃t���[���ȍ~�A���s�������V�[��
			m_pMain->Init();		// �ύX��V�[���̏�����
		}
		break;
	case kSceneKindMain:
		// �I�����Ă�����SceneResult�ɐ؂�ւ���
		if (m_pMain->IsSceneEnd())
		{
			// �V�[����؂�ւ���
			m_pMain->End();	// ���s���Ă����V�[���̏I������

	//		m_runScene = kSceneKindResult;	// ���̃t���[���ȍ~�A���s�������V�[��
	//		m_result.Init();
		}
		break;
	}


	// �e�V�[���̍X�V
}

void SceneManager::Draw()
{
}

void SceneManager::End()
{
}
