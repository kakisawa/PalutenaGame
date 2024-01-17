#pragma once
#include "Vec2.h"

/// <summary>
/// クリアシーンクラス
/// </summary>
class SceneClear
{
public:
	SceneClear();
	~SceneClear();
	void Init();
	void End();
	void Update();
	void Draw();

	// シーンを終了させるか
	bool IsSceneStageSelect() const { return m_isSceneSelectStage; }

private:
	// 選択項目
	enum Select
	{
		kSelectStage, // ステージ選択
		kTitle,		  // タイトル
		kSelectNum	  // 項目数
	};

	// 現在の選択状態
	int m_select;

private:
	// シーン選択のフラグ true:シーンに移動
	bool m_isSceneSelectStage;

	// 選択中の四角の表示位置
	Vec2 m_selectPos;
};

