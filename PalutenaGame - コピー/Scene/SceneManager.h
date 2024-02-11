#pragma once
class SceneTitle;
class SceneExplanation;
class SceneStageSelect;
class SceneMain;
class SceneSecond;
class SceneGameOver;
class SceneGameClear;

class SoundManager;
class Player;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void End();


	static int s_ResultScore;


private:

	// シーンの種類
	enum SceneKind
	{
		kSceneKindTitle,		// タイトルシーン
		kSceneKindExplanation,	// 操作説明シーン
		kSceneKindStageSelect,	// ステージセレクト
		kSceneKindMain,			// ゲーム1シーン
		kSceneKindSecond,		// ゲーム2シーン
		kSceneKindGameOver,		// ゲームオーバーシーン
		kSceneKindGameClear,	// ゲームクリアシーン
	};

	// 現在実行中のシーン
	SceneKind   m_runScene;

	// SceneManagerで管理する各シーン
	SceneTitle*  m_pTitle;
	SceneStageSelect* m_pStageSelect;
	SceneMain*   m_pMain;
	SceneSecond* m_pSecond;
	SceneGameOver* m_pGameOver;
	SceneGameClear* m_pGameClear;
	SceneExplanation* m_pExplanation;

	SoundManager* m_pSoundManager;
	Player* m_pPlayer;
};