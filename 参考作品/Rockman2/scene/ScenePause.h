#pragma once
#include "Vec2.h"

class Player;

/// <summary>
/// ポーズシーンクラス
/// </summary>
class ScenePause
{
public:
	ScenePause(Player* pPlayer);
	~ScenePause();
	void Init();
	void Update();
	void Draw();
	// ポーズ画面が表示されているか取得する
	bool IsExist() const { return m_isExist; }

private:
	// 選択項目
	enum Select
	{
		kBuster,// バスター
		kMetal, // メタル
		kFire,	// ファイアー
		kLine,	// 2号
		kFullRecovery,	// E缶
		kSelectNum // 項目数
	};

	// 現在の選択状態
	int m_select;

private:
	// プレイヤーのポインタ
	Player* m_pPlayer;

	// ポーズ画面の表示位置
	Vec2 m_pos;
	// 選択中の四角の表示位置
	Vec2 m_selectPos;
	// ポーズ画面が表示されているか true:表示されている
	bool m_isExist;
};

