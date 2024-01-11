#include "SceneManager.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneMain.h"

SceneManager::SceneManager():
	m_runScene(kSceneKindTitle),
	m_pTitle(),			// クラスの初期化時は()の中にコンストラクタの引数を書く
	m_pMain()
{
	// メモリ確保
	m_pTitle = new SceneTitle;
	m_pMain = new SceneMain;
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
	default:
		break;
	}
}

void SceneManager::Update()
{
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

	//		m_runScene = kSceneKindResult;	// 次のフレーム以降、実行したいシーン
	//		m_result.Init();
		}
		break;
	}


	// 各シーンの更新
}

void SceneManager::Draw()
{
}

void SceneManager::End()
{
}
