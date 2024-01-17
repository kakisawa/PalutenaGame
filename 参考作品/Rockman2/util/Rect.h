#pragma once
#include "Vec2.h"

// 矩形の座標を管理するためのクラス
class Rect
{
public:
	Rect();
	virtual ~Rect();

	// 四角形の描画
	void Draw(unsigned int Color, bool isFill);

	// 左上座標と幅高さを指定
	void SetLT(float left, float top, float width, float height);
	// 中心座標と幅高さを指定
	void SetCenter(float x, float y, float width, float height);

	// 必要な情報を取得する
	float GetWidth() const;		// 矩形の幅
	float GetHeight() const;	// 矩形の高さ
	Vec2 GetCenter() const;		// 矩形の中心座標
	float GetLeft() const { return m_left; } // 矩形の左上のX座標
	float GetTop() const { return m_top; }  // 矩形の左上のY座標
	float GetRight() const { return m_right; }  // 矩形の右下のX座標
	float GetBottom() const { return m_bottom; }  // 矩形の右下のY座標

	// 矩形同士の当たり判定
	bool IsCollision(const Rect& rect);

public:
	float m_left;	// 左上のX座標
	float m_top;	// 左上のY座標
	float m_right;	// 右下のX座標
	float m_bottom;	// 右下のY座標
};

