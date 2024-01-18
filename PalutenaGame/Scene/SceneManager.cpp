#include "SceneManager.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneGameOver.h"
#include "SceneStageSelect.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneKindTitle),
	m_pTitle(),			// クラスの初期化時は()の中にコンストラクタの引数を書く
	m_pStageSelect(),
	m_pMain(),
	m_pGameOver()
{
	// メモリ確保
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
	// 初期化処理
		// 実行したいシーンの初期化を行う
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
		// タイトル画面の終了をチェック
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
			m_runScene = kSceneKindMain;	// 次のフレーム以降、実行したいシーン
			m_pMain->Init();		// 変更先シーンの初期化
		}
		else if (m_pStageSelect->IsSceneEnd2()) {
			//	m_runScene = kSceneKindMain;	// 次のフレーム以降、実行したいシーン
			//	m_pMain->Init();		// 変更先シーンの初期化
			//}
		}
		else if (m_pStageSelect->IsSceneEnd3()) {
			m_runScene = kSceneKindTitle;	// 次のフレーム以降、実行したいシーン
			m_pTitle->Init();
		}
		break;
	case kSceneKindMain:
		// 終了していたらSceneResultに切り替える
		if (m_pMain->IsSceneEnd())
		{
			// シーンを切り替える
			m_pMain->End();	// 実行していたシーンの終了処理

			m_runScene = kSceneKindGameOver;	// 次のフレーム以降、実行したいシーン
			m_pGameOver->Init();
		}
		break;
	case kSceneKindGameOver:
		if (m_pGameOver->IsSceneEnd())
		{
			// シーンを切り替える
			m_pGameOver->End();	// 実行していたシーンの終了処理

			m_runScene = kSceneKindTitle;	// 次のフレーム以降、実行したいシーン
			m_pTitle->Init();
		}
		break;
	default:
		break;
	}

	// 各シーンの更新を行う
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
	// 各シーンの更新を行う
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
