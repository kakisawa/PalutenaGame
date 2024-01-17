#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player;
class SceneMain;

/// <summary>
/// 回復アイテム基底クラス
/// </summary>
class RecoveryBase
{
public:
	RecoveryBase();
	virtual ~RecoveryBase();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	// アイテムの初期位置
	virtual void Start(Vec2 pos) = 0;

	// メンバ変数にアクセス
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }

	// アイテムが存在しているか
	bool IsExist() const { return m_isExist; }
	// 現在座標の取得
	Vec2 GetPos() const { return m_pos; }
	// 回復アイテムの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

protected:
	// メインシーンのポインタ
	SceneMain* m_pMain;
	// グラフィックのハンドル
	int m_handle;
	// 表示時間のフレーム
	int m_frame;
	// 画面内に存在しているか
	bool m_isExist;

	// 表示位置
	Vec2 m_pos;
	// 当たり判定用の矩形
	Rect m_colRect;
	// 移動量
	Vec2 m_vec;
};

