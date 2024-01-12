#pragma once
#include <memory>
#include "Rect.h"

class Player;
class Map
{
public:
	Map(){}
	virtual ~Map(){}

	// プレイヤーのポインタを設定する
	void setPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	void Update();
	void Draw();

	// プレイヤーの位置からスクロール量を取得する
	int GetScrollX();
	int GetScrollY();

	// プレイヤーと当たっているか判定
	bool IsColPlayer();		// bool型を返す変数だから先頭にIsを付ける

	// 指定した矩形と当たっているか判定
	// 参照を使用してぶつかったマップチップの矩形情報を取得する
	bool IsCol(Rect rect, Rect& chipRect);
	

private:
	// スクロール量を決定するためにプレイヤーの位置情報が必要
	std::shared_ptr<Player> m_pPlayer;
};