#pragma once
#include "Vec2.h"

/// <summary>
/// ステージ選択クラス
/// </summary>
class SceneStageSelect
{
public:
	SceneStageSelect();
	~SceneStageSelect();

	void Init();
	void Update();
	void Draw();
	void End();

	// シーンを終了させるか
	bool IsSceneEnd() const { return m_isSceneEnd; }

private:
	// 選択項目
	enum Select
	{
		kStage1,	// ステージ1
		kStage2,	// ステージ2
		kStage3,	// ステージ3
		kBackTitle,	// タイトルに戻る
		kSelectNum	// 項目数
	};

	// 現在の選択状態
	int m_select;

private:
	// シーン選択のフラグ true:シーンに移動
	bool m_isSceneEnd;

	// タイトルロゴ
	int m_logoHandle;
	// 選択中の四角の表示位置
	Vec2 m_selectPos;
};

