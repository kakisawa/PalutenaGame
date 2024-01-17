#pragma once

/// <summary>
/// ゲームオーバーのクラス
/// </summary>
class SceneGameOver
{
public:
	SceneGameOver();
	~SceneGameOver();

	void Init();
	void Update();
	void Draw();
	void End();

	// シーンを終了させるか
	bool IsSceneSelect() const { return m_isSceneSelect; }

private:
	// シーン選択のフラグ true:シーンに移動
	bool m_isSceneSelect;
};

