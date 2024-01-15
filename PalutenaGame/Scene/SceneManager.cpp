#include "SceneManager.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneGameOver.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneKindTitle),
	m_pTitle(),			// クラスの初期化時は()の中にコンストラクタの引数を書く
	m_pMain(),
	m_pGameOver()
{
	// メモリ確保
	m_pTitle = new SceneTitle;
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
	// 仮でタイトル画面とゲーム画面を行き来できるようにする
	Pad::Update();

	switch (m_runScene)
	{
	case kSceneKindTitle:
		// タイトル画面の終了をチェック
		if (m_pTitle->IsSceneEnd())
		{
			m_pTitle->End();

			// ゲームシーンへ遷移
			m_runScene = kSceneKindMain;	// 次のフレーム以降、実行したいシーン
			m_pMain->Init();		// 変更先シーンの初期化
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
		if(m_pGameOver->IsSceneEnd())
		{
			// シーンを切り替える
			m_pGameOver->End();	// 実行していたシーンの終了処理

			m_runScene = kSceneKindTitle;	// 次のフレーム以降、実行したいシーン
			m_pTitle->Init();
		}
	}

	// 各シーンの更新を行う
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_pTitle->Update();
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
	// 仮でタイトル画面とゲーム画面を行き来できるようにする

	// 各シーンの更新を行う
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_pTitle->Draw();
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
	case kSceneKindMain:
		m_pMain->End();
		break;
	case kSceneKindGameOver:
		m_pGameOver->End();
	default:
		break;
	}
}
