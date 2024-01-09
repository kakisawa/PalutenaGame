#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Player
{
public:

	// 向いている方向
	enum Dir
	{
		kDirDown,	// 下	= 0
		kDirLeft,	// 左	= 1
		kDirRight,	// 右	= 2
		kDirUp,		// 上	= 3
	};

public:
	Player(SceneMain* pMain);
	~Player();

	void Init();
	void Update();
	void Draw();

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	// プレイヤーの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }
	// プレイヤーの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

	// プレイヤーがダメージを受けた
	void OnDamage();

private:	// メンバ変数は必ずprivate

	SceneMain* m_pMain;

	int m_handle;	// グラフィックのハンドル
	// 表示位置
	Vec2 m_pos;
	// 当たり判定用の矩形
	Rect m_colRect;
	// 向いている方向
	Dir m_dir;				// direction = 方向
	// 歩きアニメーション
	int m_walkAnimFrame;

	// 魔法の杖の発射フレームカウント
	int m_magicWandFrame;

	// ダメージを受けてからのフレーム数
	// 普段は0
	// 当たった時にフレーム数を設定して
	// 以降毎フレーム減らしていく
	int m_damageFrame;
};

