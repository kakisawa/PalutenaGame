#pragma once

#include "Vec2.h"

// 矩形のデータ管理
class Rect
{
public:
	float top;
	float bottom;
	float left;
	float right;
public:
	Rect() :
		top(0),
		bottom(0),
		left(0),
		right(0)
	{
	}
	float getWidth() const { return right - left; }
	float getHeight() const { return bottom - top; }

	// 各座標取得
	Vec2 getCenter();

	// 当たり(重なり)判定
	bool isCol(Rect rect);

	// 座標が矩形内に含まれるかどうか判定


	// rectデータ設定

	/// <summary>
	/// 左上座標とサイズからRectデータを設定
	/// </summary>
	/// <param name="posTL">左上座標</param>
	/// <param name="size">サイズ</param>
	void set_TL_Size(Vec2 posTL, Vec2 size);
};

