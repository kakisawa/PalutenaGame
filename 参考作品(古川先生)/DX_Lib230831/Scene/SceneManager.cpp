#include "SceneManager.h"
#include "SceneMain.h"
#include "SceneMapEdit.h"
#include "Pad.h"

SceneManager::SceneManager()
{
	// クラスのメモリを確保する
	m_pMain = new SceneMain;
	m_pMapEdit = new SceneMapEdit;
}

SceneManager::~SceneManager()
{
	// クラスのメモリを開放する
	delete m_pMain;
	m_pMain = nullptr;

	delete m_pMapEdit;
	m_pMapEdit = nullptr;
}

void SceneManager::Init()
{
	m_pMain->Init();
	//m_pMapEdit->Init();
}

void SceneManager::End()
{
	m_pMain->End();
//	m_pMapEdit->End();
}

void SceneManager::Update()
{
	Pad::Update();


	m_pMain->Update();
//	m_pMapEdit->Update();
}

void SceneManager::Draw()
{
	m_pMain->Draw();
//	m_pMapEdit->Draw();
}
