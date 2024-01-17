#pragma once
#include "Vec2.h"

/// <summary>
///  タイトルシーンのクラス
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

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
		kStart,	 // スタート
		kOption, // オプション
		kExit,	 // ゲーム終了
		kSelectNum // 項目数
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

