#pragma once
#include "Vec2.h"
#include "EnemyBase.h"

class Player;
// 発生位置から発生した時のプレイヤーの位置に向かって移動する
class EnemyToPlayer : public EnemyBase
{
public:
	EnemyToPlayer();
	virtual~EnemyToPlayer();

	virtual void Update() override;

	// メンバー変数にアクセスする
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	// 敵キャラクターをスタートさせる
	virtual void Start()override;

private:
	Player* m_pPlayer;

/*	void Draw();
	void SetHandle(int handle) { m_handle = handle; }
	bool IsExist() const { return m_isExist; }

private:	// メンバ変数は必ずprivate
	int m_handle;	// グラフィックのハンドル
	bool m_isExist;	// 存在するかフラグ(使用中かどうか)

	Player* m_pPlayer;


	// 表示位置
	Vec2 m_pos;
	// 移動量	1フレーム当たりの移動量を入れる
	Vec2 m_vec;
	*/
};

