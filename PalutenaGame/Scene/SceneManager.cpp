#include "SceneManager.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneExplanation.h"
#include "SceneMain.h"
#include "SceneGameOver.h"
#include "SceneStageSelect.h"
#include "SceneGameClear.h"
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
	m_pGameClear = new SceneGameClear;
	m_pExplanation = new SceneExplanation;
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
		m_pTitle->Init();			// タイトル画面の初期化
		break;
	case kSceneKindExplanation:
		m_pExplanation->Init();		// 操作説明画面の初期化
		break;
	case kSceneKindStageSelect:
		m_pStageSelect->Init();		// ステージセレクト画面の初期化
		break;
	case kSceneKindMain:
		m_pMain->Init();			// ステージ1画面の初期化
		break;
	case kSceneKindGameOver:
		m_pGameOver->Init();		// ゲームオーバー画面の初期化
		break;
	case kSceneKindGameClear:
		m_pGameClear->Init();		// ゲームクリア画面の初期化
		break;
	}
}

void SceneManager::Update()
{
	Pad::Update();

	switch (m_runScene)
	{
	case kSceneKindTitle:
		if (m_pTitle->IsSceneEnd())					// タイトル画面の終了をチェック
		{
			m_pTitle->End();						// タイトル画面の終了処理

			if (m_pTitle->ToExplanation()) {		
				m_runScene = kSceneKindExplanation;	// 説明画面へ行く
				m_pExplanation->Init();
			}
			else if(m_pTitle->ToStage())			
				m_runScene = kSceneKindStageSelect;	// ステージセレクト画面へ行く
			m_pStageSelect->Init();
		}
		break;
	case kSceneKindExplanation:
		if (m_pExplanation->IsSceneEnd())			// 操作説明画面の終了処理
		{
			m_runScene = kSceneKindTitle;			// タイトル画面に戻る
			m_pTitle->Init();
		}
		break;
	case kSceneKindStageSelect:
		if (m_pStageSelect->IsSceneEnd())			// ステージセレクト画面の終了をチェック
		{
			m_pStageSelect->End();					// ステージセレクト画面の終了処理

			if (m_pStageSelect->ToStage1()) {		
				m_runScene = kSceneKindMain;		// ステージ1画面へ行く
				m_pMain->Init();
			}
			else if (m_pStageSelect->ToStage2())	// ステージ2画面へ行く
			{
				break;
			}
			else if(m_pStageSelect->ToBackTitke())	
			{
				m_runScene = kSceneKindTitle;		// タイトル画面に戻る
				m_pTitle->Init();
			}
		}
		break;
	case kSceneKindMain:
		if (m_pMain->IsSceneEnd())					// ステージ1画面の終了をチェック
		{
			m_pMain->End();							// ステージ1画面の終了処理

			if (m_pMain->ToGameOver())
			{
				m_runScene = kSceneKindGameOver;	// ゲームオーバー画面へ行く
				m_pGameOver->Init();
			}
			else if (m_pMain->ToGameClear())		
			{
				m_runScene = kSceneKindGameClear;	// ゲームクリア画面へ行く
				m_pGameClear->Init();
			}
		}
		break;
	case kSceneKindGameOver:
		if (m_pGameOver->IsSceneEnd())
		{
			m_pGameOver->End();						// ゲームオーバー画面の終了処理

			if (m_pGameOver->AgainStage1())
			{
				m_runScene = kSceneKindMain;		// ステージ1画面へ行く
				m_pMain->Init();
			}
			//else if(m_pMainTwo->AgainStage2())
			//{
			//	m_runScene=kSceneKindSecond;		// ステージ2画面へ行く
			//  m_pSecond->Init(); 
			//}
			else if(!m_pGameOver->AgainStage1()||!m_pGameOver->AgainStage2()){
				m_runScene = kSceneKindTitle;		// タイトル画面へ行く
				m_pTitle->Init();
			}
		}
		break;
	case kSceneKindGameClear:
		if (m_pGameClear->IsSceneEnd())
		{
			m_pGameClear->End();					// ゲームクリア画面の終了処理

			if (m_pGameOver->AgainStage1())
			{
				m_runScene = kSceneKindMain;		// ステージ1画面へ行く
				m_pMain->Init();
			}
			//else if(m_pMainTwo->AgainStage2())
			// {
			//	m_runScene=kSceneKindSecond;		// ステージ2画面へ行く
			//  m_pSecond->Init();  
			// }
			else if (!m_pGameOver->AgainStage1() || !m_pGameOver->AgainStage2()) {
				m_runScene = kSceneKindTitle;		// タイトル画面へ行く
				m_pTitle->Init();
			}
		}
		break;
	}

	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_pTitle->Update();			// タイトル画面の更新
		break;
	case kSceneKindExplanation:
		m_pExplanation->Update();	// 操作説明画面の更新
		break;
	case kSceneKindStageSelect:
		m_pStageSelect->Update();	// ステージセレクト画面の更新
		break;
	case kSceneKindMain:
		m_pMain->Update();			// ステージ1画面の更新
		break;
	case kSceneKindGameOver:
		m_pGameOver->Update();		// ゲームオーバー画面の更新
		break;
	case kSceneKindGameClear:
		m_pGameClear->Update();		// ゲームクリア画面の更新
		break;
	}
}

void SceneManager::Draw()
{
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_pTitle->Draw();			// タイトル画面の描画
		break;
	case kSceneKindExplanation:
		m_pExplanation->Draw();		// 操作説明画面の描画
		break;
	case kSceneKindStageSelect:
		m_pStageSelect->Draw();		// ステージセレクト画面の描画
		break;
	case kSceneKindMain:
		m_pMain->Draw();			// ステージ1画面の描画
		break;
	case kSceneKindGameOver:
		m_pGameOver->Draw();		// ゲームオーバー画面の描画
		break;
	case kSceneKindGameClear:
		m_pGameClear->Draw();		// ゲームクリア画面の描画
		break;
	}
}

void SceneManager::End()
{
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_pTitle->End();			// タイトル画面の終了
		break;
	case kSceneKindExplanation:
		m_pExplanation->End();		// 操作説明画面の終了
		break;
	case kSceneKindStageSelect:
		m_pStageSelect->End();		// ステージセレクト画面の終了
		break;
	case kSceneKindMain:
		m_pMain->End();				// ステージ1画面の終了
		break;
	case kSceneKindGameOver:
		m_pGameOver->End();			// ゲームオーバー画面の終了
		break;
	case kSceneKindGameClear:
		m_pGameClear->End();		// ゲームクリア画面の終了
		break;
	}
}
