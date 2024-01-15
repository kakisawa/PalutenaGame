#pragma once
#include "Vec2.h"
#include "Rect.h"

class EnemyBase {
public:

	EnemyBase();			// コンストラクタ
	virtual ~EnemyBase(){}	// デストラクタ

	virtual void Init(){}
	virtual void Update();
	virtual void Draw();

	// メンバー変数にアクセスする
	void SetHandle(int handle) { EGraph = handle; }

	// 攻撃を受ける処理(純粋仮想関数にし、派生クラスで実装)
	virtual void Damage(int damage) = 0;

	// 死んだときの処理
	void Death()
	{
		isDeath = true;		// 死死亡フラグをオンにする
	}
	// 死んでいるかどうか
	bool GetisDeath()
	{
		return isDeath;		// 死亡フラグを返す
	}

	// 位置の取得
	Vec2 GetPos() const { return m_pos; }

	// 当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }


protected:		// 派生クラスからアクセスできるように

	int EGraph;	// 敵画像
	int W, H;	// 敵画像サイズ
	int HP;		// 敵HP
	int Atk;	// 敵攻撃力	
	int isTurn;	// 左右どちらを向いているか

	bool m_isExist;	// 存在するかフラグ(使用中かどうか)

	// エネミーアニメーション
	float EnemyAnim;
	// 重力
	float Gravity;

	// m_posを左上に,m_handleのグラフィックサイズを幅高さにした
	// 当たり判定を設定する
	virtual void UpdateCollision();

	enum Item	// アイテムの種類
	{
		kHeart,		// ハート
		kHalfHeart,	// ハーフハート
		kBigHeart,	// ビッグハート
		kHammer,	// トンカチ
	};
	Item Drop;		// ドロップアイテム

	bool isDeath; // 死亡フラグ

	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
	// 移動量	1フレーム当たりの移動量を入れる
	Vec2 m_vec;
};