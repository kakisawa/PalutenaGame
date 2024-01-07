#pragma once
#include "Vec2.h"
#include "Rect.h"

class EnemyBase {
public:

	EnemyBase() {}			// コンストラクタ
	virtual ~EnemyBase() {}	// デストラクタ

	virtual void Init();
	virtual void Update();
	virtual void Draw();

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
	int W, H;	// 敵画像サイズ
	int HP;		// 敵HP
	int Atk;	// 敵攻撃力	
	int isTurn;	// 左右どちらを向いているか

	enum Item	// アイテムの種類
	{
		kHeart,		// ハート
		kHalfHeart,	// ハーフハート
		kBigHeart,	// ビッグハート
		kHammer,	// トンカチ
	};

	Item Drop;		// ドロップアイテム

	// エネミーアニメーション
	float EnemyAnim;
	// 重力
	float Gravity;


	bool isDeath = false; //死んだかどうか、falseで初期化しておく
	//	Player* player;	// プレイヤー
};