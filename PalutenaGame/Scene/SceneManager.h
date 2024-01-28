#pragma once
class SceneTitle;
class SceneExplanation;
class SceneStageSelect;
class SceneMain;
class SceneGameOver;
class SceneGameClear;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void End();

private:

	// シーンの種類
	enum SceneKind
	{
		kSceneKindTitle,		// タイトルシーン
		kSceneKindExplanation,	// 操作説明シーン
		kSceneKindStageSelect,	// ステージセレクト
		kSceneKindMain,			// ゲーム１シーン
		kSceneKindGameOver,		// ゲームオーバーシーン
		kSceneKindGameClear,	// ゲームクリアシーン
	};

	// 現在実行中のシーン
	SceneKind   m_runScene;

	// SceneManagerで管理する各シーン
	SceneTitle*  m_pTitle;
	SceneStageSelect* m_pStageSelect;
	SceneMain*   m_pMain;
	SceneGameOver* m_pGameOver;
	SceneGameClear* m_pGameClear;
	SceneExplanation* m_pExplanation;
};

