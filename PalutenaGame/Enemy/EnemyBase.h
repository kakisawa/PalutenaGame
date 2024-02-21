#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player;

class EnemyBase {
public:

	EnemyBase();			
	virtual ~EnemyBase(){}

	virtual void Init(Player* pPlayer);
	virtual void Update();
	virtual void Draw(){}

	virtual void OnDamage();	// 敵がダメージを受けた時の処理
	void Death();				// 死んだときの処理

	Vec2 GetPos() const { return m_pos; }			// 位置の取得
	Rect GetColRect() const { return m_colRect; }	// 当たり判定の矩形を取得する

	// 敵の攻撃力,HP,スコアを渡す
	int GetEnemyAtk() const { return m_atk; }
	int GetEnemyHP() const { return m_hp; }

	bool isExist() const { return m_isExist; }

	// 敵キャラクターをスタートさせる
	virtual void Start(float x, float y) = 0;
	
protected:		// 派生クラスからアクセスできるように
	int EGraph;	// 敵画像
	int m_w, m_h;	// 敵画像サイズ
	int m_hp;		// 敵HP
	int m_atk;	// 敵攻撃力	
	int Score;	// 敵を倒した際に得られるスコア
	int m_isTurn;	// 左右どちらを向いているか

	float EnemyAnim;	// エネミーアニメーション
	float m_gravity;		// 重力
	int m_damageFrame;	// ダメージを受けてからのフレーム数
							// 普段は0で、当たった時にフレーム数を設定して
							// 以降毎フレーム減らしていく

	bool isScore;		// スコア加算フラグ

	bool m_isExist;		// 存在するかフラグ(使用中かどうか)
	bool m_isDeath;		// 死亡フラグ


	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
	// 移動量	1フレーム当たりの移動量を入れる
	Vec2 m_vec;

	Player* m_pPlayer;
};