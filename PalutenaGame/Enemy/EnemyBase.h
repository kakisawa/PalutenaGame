#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player;
class EnemyBase
{
public:

	EnemyBase();			
	virtual ~EnemyBase(){}

	virtual void Init(Player* pPlayer);
	virtual void Update();
	virtual void Draw(){}

	// 敵がダメージを受けた時の処理
	virtual void OnDamage();	
	// 死んだときの処理
	void Death();
	// 位置の取得
	Vec2 GetPos() const { return m_pos; }
	// 当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }	
	// 敵の攻撃力,HP,スコアを渡す
	int GetEnemyAtk() const { return m_atk; }
	int GetEnemyHP() const { return m_hp; }
	// 敵が存在するかどうかのフラグを渡す
	bool isExist() const { return m_isExist; }

	// 敵キャラクターをスタートさせる
	virtual void Start(float x, float y) = 0;
	
protected:	// 派生クラスからアクセスできるように
	int m_graph;		// 敵画像
	int m_expGraph;		// 敵死亡時爆破画像
	int m_w, m_h;		// 敵画像サイズ
	int m_hp;			// 敵HP
	int m_atk;			// 敵攻撃力	
	int m_score;		// 敵所持スコア
	int m_damageFrame;	// ダメージを受けてからのフレーム数

	float m_enemyAnim;		// 敵アニメーション
	float m_enemyDeathAnim;	// 敵死亡アニメーション
	float m_gravity;		// 重力
	
	bool m_isExist;		// 存在するかフラグ(使用中かどうか)
	bool m_isTurn;		// 左右どちらを向いているか
	bool m_isDeathAnim;	// 敵死亡アニメーションフラグ
	bool m_isDeath;		// 死亡フラグ
	bool m_isScore;		// スコア加算フラグ
	
	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
	// 移動量	1フレーム当たりの移動量を入れる
	Vec2 m_vec;

	Player* m_pPlayer;
};