#pragma once
#include "Vec2.h"
#include "Rect.h"

class EnemyBase{
public:

	EnemyBase() {}			// コンストラクタ
	virtual ~EnemyBase() {}	// デストラクタ

	// 攻撃を受ける処理(純粋仮想関数にし、派生クラスで実装)
	virtual void Damage(int damage) = 0;
	// 死んだときの処理
	void Death()
	{
		isDeath = true;		// 死んだフラグをオンにする
	}
	// 死んでいるかどうか
	bool GetisDeath()
	{
		return isDeath;
	}
protected:		// 派生クラスからアクセスできるように

	int EGraph;	// 敵画像
	int W,H;	// 敵画像サイズ
	int HP;		// 敵HP
	int Atk;	// 敵攻撃力
	int Item;	// ドロップアイテム
	int isTurn;	// 左右どちらを向いているか

	// 表示位置
	Vec2 enemy;
	// エネミーアニメーション
	float EnemyAnim;
	// 重力
	float Gravity;

	// 当たり判定用の矩形
	Rect m_colRect;

	bool isDeath = false; //死んだかどうか、falseで初期化しておく
//	Player* player;	// プレイヤー
};