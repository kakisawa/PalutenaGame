#pragma once
class SceneTitle;
class SceneStageSelect;
class SceneMain;
class SceneGameOver;

enum Stage
{
	kStage1,
	kStage2,

	kBack
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void End();

public:
	// ステージの種類
	Stage PlayedStage() const { return m_runStage; }
	// プレイ中/ゲームオーバー時ステージ
	Stage m_runStage;


private:

	// シーンの種類
	enum SceneKind
	{
		kSceneKindTitle,	// タイトルシーン
		kSceneStageSelect,	// ステージセレクト
		kSceneKindMain,		// ゲーム１シーン
		kSceneKindGameOver,	// ゲームオーバーシーン
	};

	// 現在実行中のシーン
	SceneKind   m_runScene;

	// SceneManagerで管理する各シーン
	SceneTitle*  m_pTitle;
	SceneStageSelect* m_pStageSelect;
	SceneMain*   m_pMain;
	SceneGameOver* m_pGameOver;
};

