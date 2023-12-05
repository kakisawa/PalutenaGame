#pragma once
#include "Rect.h"
#include "Vec2.h"

class Shot
{
public:
	// ショットの座標
	int X;
	int Y;

	// ショットの画像
	int Graph;

	// 弾が画面上に存在しているか保持する変数
	bool Flag;

	// ショットの画像サイズ
	int W;
	int H;

	// 弾の左方向フラグ
	bool LeftDir;
	// 弾の上方向フラグ
	bool TopDir;

public:
	// 当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }

	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;

public:

	Shot();
	~Shot();
	void Init();
	void Update(Player& player);
	void Draw(Player& player);
};