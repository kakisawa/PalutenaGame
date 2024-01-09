#pragma once
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void Update();
	void Draw();

	void End();

	// シーンを終了させたいか
	bool IsSceneEnd() const;

private:

	bool m_isSceneEnd;	// シーン終了フラグ
					// true:タイトルを終了してゲームへ

	// BGMのハンドル
	int m_bgmHandle;

	// 効果音のハンドル
	int m_decideSe;

		// フェードイン、アウト
	int m_fadeAlpha;
};

