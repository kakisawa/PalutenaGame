#pragma once
#include "Vec2.h"
#include "Rect.h"

// 敵の基底となるクラス
// 継承元となるクラスを基底クラスと呼ぶ
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase ();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	bool IsExist() const { return m_isExist; }

	// 位置の取得
	Vec2 GetPos() const { return m_pos; }

	// 当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }

	// 敵キャラクターをスタートさせる
	virtual void Start() = 0;

protected:
	// m_posを左上に,m_handleのグラフィックサイズを幅高さにした
	// 当たり判定を設定する
	virtual void UpdateCollision();

//private:	// メンバ変数は必ずprivate	// 継承先からも参照できない
protected:	// 継承先から参照できる
	int m_handle;	// グラフィックのハンドル

	bool m_isExist;	// 存在するかフラグ(使用中かどうか)

	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
	// 移動量	1フレーム当たりの移動量を入れる
	Vec2 m_vec;
};

