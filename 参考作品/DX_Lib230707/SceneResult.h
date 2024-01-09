#pragma once
class SceneResult
{
public:
	SceneResult();
	~SceneResult();

	void Init();
	void Update();
	void Draw();
	void End();

	// シーンを終了させたいか
	bool IsSceneEnd() const { return m_isSceneEnd; }

private:
	// 画像のハンドル
	int m_gameoverHandle;

	bool m_isSceneEnd;	// シーン終了フラグ
};

