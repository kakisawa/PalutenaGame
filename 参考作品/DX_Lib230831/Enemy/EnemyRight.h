#pragma once
#include "Vec2.h"
#include "EnemyBase.h"

// 右から登場する敵のクラス
class EnemyRight : public EnemyBase
{
public:
	EnemyRight();
	virtual ~EnemyRight();

	virtual void Update() override;

	// 敵キャラクターをスタートさせる
	virtual void Start() override;

	/*
	void Init();

	
	void Draw();

	 メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	bool IsExist() const { return m_isExist; }



private:	// メンバ変数は必ずprivate
	int m_handle;	// グラフィックのハンドル

	bool m_isExist;	// 存在するかフラグ(使用中かどうか)

	// 表示位置
	Vec2 m_pos;
	// 移動量	1フレーム当たりの移動量を入れる
	Vec2 m_vec;
*/
};

